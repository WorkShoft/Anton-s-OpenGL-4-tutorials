/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 27 Jan 2014                                                    |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries separate legal notices                              |
|******************************************************************************|
| Particle Systems                                                             |
\******************************************************************************/

#include "gl_utils.h"
#include "maths_funcs.h"
#include <GL/glew.h>		// include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdlib.h>
#define MESH_FILE "../resources/Mario2.dae"
#define GL_LOG_FILE "gl.log"
#define VERTEX_SHADER_FILE "test_vs.glsl"
#define FRAGMENT_SHADER_FILE "test_fs.glsl"
#define MAX_BONES 32

int g_gl_width = 1000;
int g_gl_height = 600;

GLFWwindow *g_window = NULL;


mat4 convert_assimp_matrix(aiMatrix4x4 m){
  return mat4 (
	       1.0f, 0.0f, 0.0f, 0.0f,
	       0.0f, 1.0f, 0.0f, 0.0f,
	       0.0f, 0.0f, 1.0f, 0.0f,
	       m.a4, m.b4, m.c4, m.d4
	       );
}


bool load_mesh(const char* file_name, GLuint* vao, int* point_count, mat4* bone_offset_mats, int* bone_count){
  const aiScene* scene = aiImportFile(file_name, aiProcess_Triangulate);
  if(!scene){
    fprintf(stderr, "ERROR: reading mesh %s\n", file_name);
    return false;
}
printf (" %i animations\n", scene->mNumAnimations);
printf (" %i cameras\n", scene->mNumCameras);
printf (" %i lights\n", scene->mNumLights);
printf (" %i materials\n", scene->mNumMaterials);
printf (" %i meshes\n", scene->mNumMeshes);
printf (" %i textures\n", scene->mNumTextures);
 
  printf(" %i vertices\n", scene->mNumTextures);

  const aiMesh* mesh = scene->mMeshes[2];
  printf(" %i vertices in mesh[0]\n", mesh->mNumVertices);
  
  *point_count = mesh->mNumVertices;

  glGenVertexArrays(1, vao);
  glBindVertexArray(*vao);

  GLfloat* points = NULL;
  GLfloat* normals =  NULL;
  GLfloat* texcoords = NULL;
  GLint* bone_ids = NULL;

      
  if(mesh -> HasPositions()){
    points = (GLfloat*)malloc (*point_count * 3 * sizeof (GLfloat));
    for(int i = 0; i < *point_count; i++){
      const aiVector3D* vp = &(mesh -> mVertices[i]);
      points[i * 3] = (GLfloat)vp -> x;
      points[i * 3 + 1] = (GLfloat)vp -> y;
      points[i * 3 + 2] = (GLfloat)vp -> z;
    }
  }
  if (mesh->HasNormals ()){
    normals = (GLfloat*)malloc (*point_count * 3 * sizeof (GLfloat));
    for(int i = 0; i < *point_count; i++){
      const aiVector3D* vn = &(mesh -> mNormals[i]);
      normals[i * 3] = (GLfloat)vn -> x;
      normals[i * 3 + 1] = (GLfloat)vn -> y;
      normals[i * 3 + 2] = (GLfloat)vn -> z;
    }
  }
  if (mesh->HasTextureCoords (0)){
    texcoords = (GLfloat*)malloc (*point_count * 2 * sizeof (GLfloat));
    for(int i = 0; i < *point_count; i++){
      const aiVector3D* vt = &(mesh -> mTextureCoords[0][i]);
      texcoords[i * 2] = (GLfloat)vt -> x;
      texcoords[i * 2 + 1] = (GLfloat)vt -> y;
    }
  }

  /* copy mesh data into VBOs */
  if(mesh -> HasPositions()){
    GLuint vbo;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (
		  GL_ARRAY_BUFFER,
		    3 * *point_count * sizeof (GLfloat),
		  points,
		  GL_STATIC_DRAW
		  );
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray (0);
    free(points);
  }

  if(mesh -> HasNormals ()){
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (
		  GL_ARRAY_BUFFER,
		  3 * *point_count * sizeof (GLfloat),
		  normals,
		  GL_STATIC_DRAW
		  );
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    free(normals);
  }
  if(mesh -> HasTextureCoords (0)){
    GLuint vbo;
    
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData(
		 GL_ARRAY_BUFFER,
		 2* *point_count * sizeof (GLfloat),
		 texcoords,
		 GL_STATIC_DRAW
		 );
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);
    free (texcoords);
  }

  if( mesh -> HasTangentsAndBitangents ()){
    /* TODO */
  }

  /* skinning code */

  if(mesh->HasBones()){
    std::cout << "Mesh has bones!" << std::endl;
    *bone_count = (int)mesh->mNumBones;

    char bone_names[256][64];
  
    for(int b_i=0; b_i < *bone_count; b_i++){
      std::cout << b_i << std::endl;
      const aiBone* bone = mesh->mBones[b_i];
      strcpy (bone_names[b_i], bone->mName.data);
      printf("bone_names[%i]=%s\n", b_i, bone_names[b_i]);
      bone_offset_mats[b_i] = convert_assimp_matrix( bone -> mOffsetMatrix);
      bone_ids = (int*)malloc(*point_count * sizeof (int));

      /* bone weights */
      int num_weights = (int)bone->mNumWeights;

      for (int w_i = 0; w_i < num_weights; w_i++){
	aiVertexWeight weight = bone->mWeights[w_i];
	int vertex_id = (int)weight.mVertexId;
	// ignore weight if less than 0.5 factor
	// if(weight.mWeight >= 0.5f){
	//   bone_ids[vertex_id] = b_i;
	// }
      }
    }

    /* bone vbo */

    GLuint vbo;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData(
		 GL_ARRAY_BUFFER,
		 *point_count * sizeof (GLint),
		 bone_ids,
		 GL_STATIC_DRAW
		 );
    glVertexAttribIPointer(3, 1, GL_INT, 0, NULL);
    glEnableVertexAttribArray (3);
    free (bone_ids);
  } else {
    std::cout << "No bones detected" << std::endl;
  }
  
 
  aiReleaseImport(scene);
  printf("mesh loaded\n");
  return true;
}


int main() {
	restart_gl_log();
	// use GLFW and GLEW to start GL context. see gl_utils.cpp for details
	start_gl();

	glEnable( GL_CULL_FACE );	// cull face
	glCullFace( GL_BACK );		 // cull back face
	glFrontFace( GL_CCW );		 // GL_CCW for counter clock-wise
	glDepthFunc( GL_LESS );		 // depth-testing interprets a smaller value as "closer"
	glEnable( GL_DEPTH_TEST ); // enable depth-testing
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glClearColor( 0.2, 0.2, 0.2, 1.0 );

	GLuint monkey_vao;
	mat4 monkey_bone_offset_matrices[MAX_BONES];	
	int monkey_point_count = 0;
	int monkey_bone_count;
	
	assert(load_mesh(MESH_FILE,
			 &monkey_vao,
			 &monkey_point_count,
			 monkey_bone_offset_matrices,
			 &monkey_bone_count));

	GLuint shader_programme =
	  create_programme_from_files( VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE );

	#define ONE_DEG_IN_RAD ( 2.0 * M_PI ) / 360.0 // 0.017444444
	// input variables
	float near = 0.1f;									// clipping plane
	float far = 100.0f;									// clipping plane
	float fov = 67.0f * ONE_DEG_IN_RAD; // convert 67 degrees to radians
	float aspect = (float)g_gl_width / (float)g_gl_height; // aspect ratio
	// matrix components
	float range = tan( fov * 0.5f ) * near;
	float Sx = ( 2.0f * near ) / ( range * aspect + range * aspect );
	float Sy = near / range;
	float Sz = -( far + near ) / ( far - near );
	float Pz = -( 2.0f * far * near ) / ( far - near );
	GLfloat proj_mat[] = { Sx,	 0.0f, 0.0f, 0.0f,	0.0f, Sy,		0.0f, 0.0f,
												 0.0f, 0.0f, Sz,	 -1.0f, 0.0f, 0.0f, Pz,		0.0f };

	float cam_speed = 1.0f;			 // 1 unit per second
	float cam_yaw_speed = 10.0f; // 10 degrees per second
	float cam_pos[] = { 0.0f, -1.0f, 5.0f }; // don't start at zero, or we will be too close
	float cam_yaw = 5.0f;				// y-rotation in degrees
	mat4 T =
	  translate( identity_mat4(), vec3(-cam_pos[0], -cam_pos[1], -cam_pos[2] ) );

	mat4 R = rotate_y_deg( identity_mat4(), -cam_yaw );

	mat4 view_mat = R * T;


	int view_mat_location = glGetUniformLocation( shader_programme, "view" );
	glUseProgram( shader_programme );
	glUniformMatrix4fv( view_mat_location, 1, GL_FALSE, view_mat.m );
	int proj_mat_location = glGetUniformLocation( shader_programme, "proj" );
	glUseProgram( shader_programme );
	glUniformMatrix4fv( proj_mat_location, 1, GL_FALSE, proj_mat );


	//load textures
	int tex_a_location = glGetUniformLocation( shader_programme, "texture1" );	
	glUniform1i( tex_a_location, 0 );

        GLuint tex_a;
        glActiveTexture( GL_TEXTURE0 );
        ( load_texture( "../resources/mario_main.png.001.png", &tex_a ) );
        glBindTexture( GL_TEXTURE_2D, tex_a );

	int bone_matrices_locations[MAX_BONES];
	float identity[] = {
	1.0f, 0.0f, 0.0f, 0.0f, // first column
	  0.0f, 1.0f, 0.0f, 0.0f, // second column
	  0.0f, 0.0f, 1.0f, 0.0f, // third column
	  0.0f, 0.0f, 0.0f, 1.0f // fourth column
	};
	// reset all the bone matrices
	glUseProgram(shader_programme);
	char name[64];

	for (int i = 0; i < MAX_BONES; i++){
	  sprintf (name, "bone_matrices[%i]", i);
	  bone_matrices_locations[i] = glGetUniformLocation (shader_programme, name);
	  glUniformMatrix4fv (bone_matrices_locations[i], 1, GL_FALSE, identity);

	}

	float theta = 0.0f;
	float rot_speed = 50.0f;
	mat4 left_ear_mat = identity_mat4();

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
	unsigned int transformLoc = glGetUniformLocation(shader_programme, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


	while ( !glfwWindowShouldClose( g_window ) ) {
		static double previous_seconds = glfwGetTime();
		double current_seconds = glfwGetTime();
		double elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;
		_update_fps_counter( g_window );

		// wipe the drawing surface clear
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		glUseProgram(shader_programme);
		glBindVertexArray(monkey_vao);
		glDrawArrays( GL_TRIANGLES, 0, monkey_point_count);
		
		//glViewport( 0, 0, g_gl_width, g_gl_height );
	     		
		// update other events like input handling
		glfwPollEvents();

		// put the stuff we've been drawing onto the display
		glfwSwapBuffers( g_window );

				// control keys
		bool cam_moved = false;
		if ( glfwGetKey( g_window, GLFW_KEY_A ) ) {
			cam_pos[0] -= cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if ( glfwGetKey( g_window, GLFW_KEY_D ) ) {
			cam_pos[0] += cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if ( glfwGetKey( g_window, GLFW_KEY_PAGE_UP ) ) {
			cam_pos[1] += cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if ( glfwGetKey( g_window, GLFW_KEY_PAGE_DOWN ) ) {
			cam_pos[1] -= cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if ( glfwGetKey( g_window, GLFW_KEY_W ) ) {
			cam_pos[2] -= cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if ( glfwGetKey( g_window, GLFW_KEY_S ) ) {
			cam_pos[2] += cam_speed * elapsed_seconds;
			cam_moved = true;
		}
		if ( glfwGetKey( g_window, GLFW_KEY_LEFT ) ) {
			cam_yaw += cam_yaw_speed * elapsed_seconds;
			cam_moved = true;
		}
		if ( glfwGetKey( g_window, GLFW_KEY_RIGHT ) ) {
			cam_yaw -= cam_yaw_speed * elapsed_seconds;
			cam_moved = true;
			
		}
		if(glfwGetKey(g_window, GLFW_KEY_SPACE)){
		  theta += rot_speed * elapsed_seconds;
		  left_ear_mat = rotate_z_deg (identity_mat4(), theta);
		  glUseProgram (shader_programme);
		  glUniformMatrix4fv (bone_matrices_locations[8], 1, GL_FALSE, left_ear_mat.m);
		  //std::cout << "Pressed space" << std::endl;
		}
				
		// update view matrix
		if ( cam_moved ) {
		  mat4 T = translate( identity_mat4(), vec3( -cam_pos[0], -cam_pos[1],																								 -cam_pos[2] ) ); // cam translation
			mat4 R = rotate_y_deg( identity_mat4(), -cam_yaw );		    
			mat4 view_mat =  R * T;
			
			glUniformMatrix4fv( view_mat_location, 1, GL_FALSE, view_mat.m );
		}


		if ( GLFW_PRESS == glfwGetKey( g_window, GLFW_KEY_ESCAPE ) ) {
		  glfwSetWindowShouldClose( g_window, 1 );
		}
	}

	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}
