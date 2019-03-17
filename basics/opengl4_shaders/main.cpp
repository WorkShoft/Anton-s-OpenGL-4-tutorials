#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include "shader_read.h"


int g_win_width = 640;
int g_win_height = 480;
int g_fb_width = 640;
int g_fb_height = 480;

void glfw_window_size_callback(GLFWwindow *window, int width, int height){
  int g_win_width = width;
  int g_win_height = height;
}

void glfw_framebuffer_resize_callback (GLFWwindow* window, int width, int height){
  g_fb_width = width;
  g_fb_height = height;
}

bool is_valid(GLuint programme){
  glValidateProgram(programme);
  int params = -1;
  glGetProgramiv(programme, GL_VALIDATE_STATUS, &params);
  printf("program %i GL_VALIDATE_STATUS = %i\n", programme, params);
  if(GL_TRUE != params){
    return false;
  }
  return true;
}

int main() {  
  if (!glfwInit()){
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  glfwWindowHint (GLFW_SAMPLES, 4); // Antialiasing
  
  /*FULLSCREEN
    GLFWmonitor* mon = glfwGetPrimaryMonitor ();
    const GLFWvidmode* vmode = glfwGetVideoMode (mon);
    GLFWwindow* window = glfwCreateWindow (vmode->width, vmode->height, "OpenGL4 Shaders", mon, NULL);
  */

  GLFWwindow* window = glfwCreateWindow (640, 480, "OpenGL4 Shaders", NULL, NULL);
 
  if(!window){
    fprintf(stderr, "ERROR: could not open window GLFW3\n");
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent (window);
  glewExperimental = GL_TRUE;
  glewInit();

  const GLubyte* renderer = glGetString (GL_RENDERER);
  const GLubyte* version = glGetString (GL_VERSION);
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

    GLfloat points[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
  };

  char* vertex_shader = get_shader("../opengl4_shaders.vs");
  char* fragment_shader = get_shader("../opengl4_shaders.fs");

  printf("%s ", vertex_shader);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  GLuint vbo = 0;
  glGenBuffers (1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);   //Generate a vertex array object (vao)
  glBindVertexArray(vao);       //Bind vao to the current context (make it accessible)
  glEnableVertexAttribArray(0); // Enable the first attribute of the vao
  glBindBuffer(GL_ARRAY_BUFFER, vbo); //Bind vbo to the current context 
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // Define the properties of vao's first attribute
  
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource (vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  
  int params = -1;
  glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
  if(GL_TRUE != params){
    fprintf (stderr, "ERROR: GL shader index %i did not compile\n", vs);
    return false;   
  }
  
  GLuint fs  = glCreateShader (GL_FRAGMENT_SHADER);
  glShaderSource (fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  GLuint shader_programme = glCreateProgram();
  glAttachShader (shader_programme, fs);
  glAttachShader (shader_programme, vs);
  glLinkProgram (shader_programme);

  // check if link was successful
  params = -1;
  glGetProgramiv(shader_programme, GL_LINK_STATUS, &params);
  if(GL_TRUE != params){
    fprintf(stderr, "ERROR: could not link shader programme GL index %u\n", shader_programme);
    return false;    
  }

  glm::vec4 colour = glm::vec4(0.5f, 0.5f, 0.5f, 0.5f);
 
  GLint input_colour = glGetUniformLocation(shader_programme, "inputColour");
  glUseProgram(shader_programme);    
  glUniform4f(input_colour, colour[0], colour[1], colour[2], colour[3]);

  int editColourIndex = 0; // start editing red

  // free char buffer once the shader programme has been compiled
  //free(vertex_shader);
  //free(fragment_shader);

  while(!glfwWindowShouldClose(window)){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, g_fb_width, g_fb_height);
    glUseProgram(shader_programme);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)){
      glfwSetWindowShouldClose(window, 1);
    }    
    
    else if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_1)){
      editColourIndex = 0;
    }

    else if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_2)){
      editColourIndex = 1;
    }

    else if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_3)){
      editColourIndex = 2;
    }

    else if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_4)){
      editColourIndex = 3;
    }
    
    else if(GLFW_PRESS == (glfwGetKey(window, GLFW_KEY_UP) or glfwGetKey(window, GLFW_KEY_DOWN))){
      if(GLFW_PRESS == (glfwGetKey(window, GLFW_KEY_UP))){
	colour[editColourIndex] += 0.01f;
      }

      else if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_DOWN)){
	colour[editColourIndex] -= 0.01f;
      }

      glUseProgram(shader_programme);    
      glUniform4f(input_colour, colour[0], colour[1], colour[2], colour[3]);
    }


    
  }
  

  glfwTerminate();
  return 0;    
}
