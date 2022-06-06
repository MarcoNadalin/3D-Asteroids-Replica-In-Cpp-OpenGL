#ifndef MESH_H
#define MESH_H

#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

#include <memory>
#include <vector>

#include "Vertex.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class Mesh
{
private:
	
	std::unique_ptr<std::vector<std::shared_ptr<Vector3f>>> vertex_positions;
	std::unique_ptr<std::vector<std::shared_ptr<Vector3f>>> vertex_texcoords;
	std::unique_ptr<std::vector<std::shared_ptr<Vector3f>>> vertex_normals;

	//Vertex portions
	//std::vector<Vector3f> vertex_positions;
	//std::vector<Vector3f> vertex_texcoords;
	//std::vector<Vector3f> vertex_normals;

	//Face vectors
	std::vector<GLint> vertex_position_indicies;
	std::vector<GLint> vertex_texcoord_indicies;
	std::vector<GLint> vertex_normal_indicies;

	//Vertex array
	std::unique_ptr<std::vector<std::shared_ptr<Vertex>>> verticies;

	std::fstream file;

	bool load_file(const char* obj_location);
	void loadOBJ(const char* file_name);
	bool read_file();

public:
	Mesh(const char* obj_location);

	std::vector<std::shared_ptr<Vertex>>* getVerticies() { return verticies.get(); }

	std::vector<std::shared_ptr<Vector3f>>* getvertPos() { return vertex_positions.get(); }
};

#endif