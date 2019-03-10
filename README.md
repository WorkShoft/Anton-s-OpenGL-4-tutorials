Code based on Anton Gerdelan's OpenGL 4 book.

Each chapter in the book has its own folder. Inside the chapter there is a folder for each section, which contains its program.

root->
       chapter->
                 section/program

To compile an example:
1) Move to its folder
2) mkdir build && cd build
3) cmake ..
4) make

Requirements:	
GLFW  
GLEW
GLM

This project is developed in a Ubuntu 18.04 environment and built with CMake. It should work on most modern Linux distributions once the required libraries are installed.

To install these libraries on Ubuntu run sudo apt install libglfw3 libglew-dev libglm

Table of contents:<br/>
Basics<br/>
  "Hello Triangle" - OpenGL 4 Up and Running<br/>
  Extended Initialisation<br/>
  OpenGL 4 Shaders<br/>
  Vertex Buffer Objects<br/>
Transformation<br/>
  Vectors and Matrices<br/>
  Virtual Camera<br/>
  Quaternion Quick-Start<br/>
  Ray-Based Picking<br/>
Lighting and Texture Maps<br/>
  Phong Lighting<br/>
  Texture Maps<br/>
Tips and Tricks<br/>
  Screen Capture<br/>
  Video Capture<br/>
  Debugging Shaders<br/>
  Gamma Correction<br/>
  Extension Checks and the Debug Callback<br/>
  Uniform Buffer Objects and Mapping Buffers<br/>
Mesh Files<br/>
  Importing a Mesh File<br/>
More Advanced Lighting and Texture Effects
  Multi-Texturing<br/>
  Using Textures for Lighting Coefficients<br/>
  Fragment Rejection<br/>
  Alpha Blending for Transparency<br/>
  Spotlights and Directional Lights<br/>
  Distance Fog<br/>
  Normal Mapping<br/>
  Cube Maps: Sky Boxes and Environment Mapping<br/>
New Shader Stages<br/>
  Geometry Shaders<br/>
  Tessellation Shaders<br/>
2d Rendering<br/>
  2d GUI Panels<br/>
  Sprite Sheets and 2d Animation<br/>
  Bitmap Fonts<br/>
  Making a Font Atlas Generator Tool<br/>
Animation<br/>
  Particle Systems<br/>
  Hardware Skinning Part 1: Bones<br/>
  Hardware Skinning Part 2: Skeleton Hierarchies<br/>
  Hardware Skinning Part 3: Key-Frame Animation<br/>
Multi-Pass Rendering<br/>
  Switching Framebuffer<br/>
  Image Processing with a Kernel<br/>
  Colour-Based Picking<br/>
  Deferred Shading<br/>
  Texture Projection Shadows<br/>


Early project drafts can be found at misc. Only some of those programs work but the ones that don't should be easily fixable.
