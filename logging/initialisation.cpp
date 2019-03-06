#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <logging.h>

int width = 640;
int height = 480;

void glfw_error_callback (int error, const char* description) {
  gl_log_err ("GLFW ERROR: code %i msg: %s\n", error, description);
}


int main (){
  // start GL context and O/S window using the GLFW helper library
  if (!restart_gl_log ()){}
    //fprintf(stderr, "ERROR: could not start GLFW3\n");
    gl_log("starting GLFW\n%s\n", glfwGetVersionString());
    
    glfwSetErrorCallback(glfw_error_callback);


    if( !glfwInit ()){
      fprintf(stderr, "ERROR: could not start GLFW3\n");
          return 1;
    }


    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  
GLFWmonitor* mon = glfwGetPrimaryMonitor ();

GLFWwindow* window = glfwCreateWindow (640, 480, "Extended GL Init", NULL, NULL);

  
  if (!window) {
    fprintf (stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent (window);

  glewExperimental = GL_TRUE;
  glewInit;

  log_gl_params ();
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
