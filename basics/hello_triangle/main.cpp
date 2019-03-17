#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "shader_read.h"

int main() {  
  if (!glfwInit()){
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  GLFWwindow* window = glfwCreateWindow (640, 480, "Hello Triangle", NULL, NULL);

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

  //char* vertex_shader = get_shader("hello_triangle.vs");
  //char* fragment_shader = get_shader("hello_triangle.fs");
  const char* vertex_shader =
"#version 410\n"
"in vec3 vp;"
"void main () {"
"gl_Position = vec4 (vp, 1.0);"
"}";

  const char* fragment_shader =
    "#version 410\n"
    "out vec4 frag_colour;"
    "void main () {"
    "frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
    "}";
  
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


  while(!glfwWindowShouldClose(window)){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_programme);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;    
}
