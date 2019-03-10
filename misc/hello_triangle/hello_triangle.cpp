/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 27 Jan 2014                                                    |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries for separate legal notices                          |
|******************************************************************************|
| "Hello Triangle". Just the basics.                                           |
| If you're on Apple un-comment the version number code at the beginning. It   |
| will give you the latest, even if you say 3.2!                               |
| This uses the libraries GLEW and GLFW3 to start GL. Download and compile     |
| these first. Linking them might be a pain, but you'll need to master this.   |
\******************************************************************************/

/* NOTE(Anton) for OS X Mojave users:
I updated this .c file and Makefile.osx to compile and run on Mojave
The older compiled libraries in this repository will not link, so I modified the Makefile to
link against dynamic libraries installed on the system.
I suggest you:
1. Download and install Homebrew
2. brew install glfw and brew install glew
- I also had to delete and reinstall XCode to update the c build tools.
- Note that you may get a black screen until the window is moved or resized. I understand both GLFW
and SDL libraries have this problem since Mojave and may require a patch to access the context in a
different order than previous versions of OS X.
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main(){
  if (!glfwInit ()){
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  GLFWwindow* window = glfwCreateWindow (640, 480, "Hello Triangle", NULL, NULL);
  if(!window){
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  glewInit();

  const GLubyte* renderer = glGetString (GL_RENDERER);
  const GLubyte* version = glGetString (GL_VERSION);
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  glEnable (GL_DEPTH_TEST);
  glDepthFunc (GL_LESS);

  glfwTerminate();
  return 0;
}
