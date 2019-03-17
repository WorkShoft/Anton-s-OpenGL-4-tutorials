#include <GL/glew.h>
#include <GLFW/glfw3.h>
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

int main() {  
  if (!glfwInit()){
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  glfwWindowHint (GLFW_SAMPLES, 4); // Antialiasing
  
  /*FULLSCREEN
    GLFWmonitor* mon = glfwGetPrimaryMonitor ();
    const GLFWvidmode* vmode = glfwGetVideoMode (mon);
    GLFWwindow* window = glfwCreateWindow (vmode->width, vmode->height, "Extended Initialisation", mon, NULL);
  */

  GLFWwindow* window = glfwCreateWindow (640, 480, "Extended Initialisation", NULL, NULL);
 
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

  char* vertex_shader = get_shader("../extended_initialisation.vs");
  char* fragment_shader = get_shader("../extended_initialisation.fs");

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
  GLuint fs  = glCreateShader (GL_FRAGMENT_SHADER);
  glShaderSource (fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  GLuint shader_programme = glCreateProgram();
  glAttachShader (shader_programme, fs);
  glAttachShader (shader_programme, vs);
  glLinkProgram (shader_programme);

  // free char buffer once the shader programme has been compiled
  free(vertex_shader);
  free(fragment_shader);

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

    

  }

  glfwTerminate();
  return 0;    
}
