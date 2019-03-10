#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main (){
  // start GL context and O/S window using the GLFW helper library
  if (!glfwInit()){
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }


  GLFWwindow* window = glfwCreateWindow (640, 480, "Hello Triangle", NULL, NULL);
  if (!window) {
    fprintf (stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent (window);

  glewExperimental = GL_TRUE;
  glewInit;

  const GLubyte* renderer = glGetString (GL_RENDERER);
  const GLubyte* version =   glGetString (GL_VERSION);

  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

    //// OTHER STUFF GOES HERE NEXT ////

    glfwTerminate();
  return 0;
}
