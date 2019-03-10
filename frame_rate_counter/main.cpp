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


    /* glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);
    */
  
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

  const char* vertex_shader =
    "#version 410\n"
    "in vec3 vp;"
    "void main () {"
    " gl_Position = vec4(vp, 1.0); "
    "}";

  const char* fragment_shader =
  "#version 410\n"
  "out vec4 frag_colour;"
  "void main () {"
    "frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
    "}";

  GLfloat points[] = {
0.0f,0.5f,0.0f,
0.5f, -0.5f,0.0f,
0.5f, -0.5f,0.0f
};

  //VBO
  GLuint vbo = 0;
/* tell GL to only draw onto a pixel if the shape is closer to the viewer*/
	glEnable( GL_DEPTH_TEST ); /* enable depth-testing */
	glDepthFunc( GL_LESS );		 /* depth-testing interprets a smaller value as
																"closer" */

	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
glBufferData (GL_ARRAY_BUFFER, sizeof (points), points, GL_STATIC_DRAW);


  //VAO

 

  // GLuint vao = 0;
  // glGenVertexArrays(1, &vao);
  // glBindVertexArray(vao);
  // glEnableVertexAttribArray(0);
  // glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  

  //   GLuint vs = glCreateShader (GL_VERTEX_SHADER);
  // glShaderSource(vs, 1, &vertex_shader, NULL);
  // glCompileShader(vs);
  // GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
  // glShaderSource (fs, 1, &fragment_shader, NULL);
  // glCompileShader(fs);

  // // Combine the shaders into a single, executable GPU shader programme
  // GLuint shader_programme = glCreateProgram();
  // glAttachShader (shader_programme, fs);
  // glAttachShader (shader_programme, vs);
  // glLinkProgram(shader_programme);

  // while(!glfwWindowShouldClose(window)){
  //   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //   glUseProgram(shader_programme);
  //   glBindVertexArray(vao);
  //   glDrawArrays(GL_TRIANGLES,0, 3);
  //   glfwPollEvents();
  //   glfwSwapBuffers(window);
  // }


   
  return 0;
}
