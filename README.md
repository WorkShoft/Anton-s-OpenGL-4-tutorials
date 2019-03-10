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

Table of contents:
Basics
  "Hello Triangle" - OpenGL 4 Up and Running
  Extended Initialisation
  OpenGL 4 Shaders
  Vertex Buffer Objects
Transformation
  Vectors and Matrices
  Virtual Camera
  Quaternion Quick-Start
  Ray-Based Picking
Lighting and Texture Maps
  Phong Lighting
  Texture Maps
Tips and Tricks
  Screen Capture
  Video Capture
  Debugging Shaders
  Gamma Correction
  Extension Checks and the Debug Callback
  Uniform Buffer Objects and Mapping Buffers
Mesh Files
  Importing a Mesh File
More Advanced Lighting and Texture Effects
  Multi-Texturing
  Using Textures for Lighting Coefficients
  Fragment Rejection
  Alpha Blending for Transparency
  Spotlights and Directional Lights
  Distance Fog
  Normal Mapping
  Cube Maps: Sky Boxes and Environment Mapping
New Shader Stages
  Geometry Shaders
  Tessellation Shaders
2d Rendering
  2d GUI Panels
  Sprite Sheets and 2d Animation
  Bitmap Fonts
  Making a Font Atlas Generator Tool
Animation
  Particle Systems
  Hardware Skinning Part 1: Bones
  Hardware Skinning Part 2: Skeleton Hierarchies
  Hardware Skinning Part 3: Key-Frame Animation
Multi-Pass Rendering
  Switching Framebuffer
  Image Processing with a Kernel
  Colour-Based Picking
  Deferred Shading
  Texture Projection Shadows


Early project drafts can be found at misc. Only some of those programs work but the ones that don't should be easily fixable.
