#include "Mesh.h"

Mesh::Mesh(const char* obj_location)
{
    this->vertex_positions = std::make_unique<std::vector<std::shared_ptr<Vector3f>>>();
    this->vertex_texcoords = std::make_unique<std::vector<std::shared_ptr<Vector3f>>>();
    this->vertex_normals = std::make_unique<std::vector<std::shared_ptr<Vector3f>>>();

	verticies = std::make_unique <std::vector<std::shared_ptr<Vertex>>>();
	vertex_position_indicies = std::vector<GLint>();
	vertex_texcoord_indicies = std::vector<GLint>();
	vertex_normal_indicies = std::vector<GLint>();
    //load_file(obj_location);
	loadOBJ(obj_location);
}

bool Mesh::load_file(const char* obj_location)
{
    return true;
}

void Mesh::loadOBJ(const char* file_name)
{
	//Vertex array
	std::vector<Vertex> vertices;

	std::stringstream ss;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	std::shared_ptr<Vector3f> temp_vec3 = std::make_shared<Vector3f>();
	std::shared_ptr<Vector3f> temp_vec2 = std::make_shared<Vector3f>();
	GLint temp_glint = 0;

	//File open error check
	if (!in_file.is_open())
	{
		throw "ERROR::OBJLOADER::Could not open file.";
	}

	//Read one line at a time
	while (std::getline(in_file, line))
	{
		//Get the prefix of the line
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#")
		{

		}
		else if (prefix == "o")
		{

		}
		else if (prefix == "s")
		{

		}
		else if (prefix == "use_mtl")
		{

		}
		else if (prefix == "v") //Vertex position
		{
			std::shared_ptr<Vector3f> vec = std::make_shared<Vector3f>();
			ss >> vec->x >> vec->y >> vec->z;
			vertex_positions->push_back(vec);
		}
		else if (prefix == "vt")
		{
			std::shared_ptr<Vector3f> vec = std::make_shared<Vector3f>();
			ss >> vec->x >> vec->y >> vec->z;
			vertex_texcoords->push_back(vec);
		}
		else if (prefix == "vn")
		{
			std::shared_ptr<Vector3f> vec = std::make_shared<Vector3f>();
			ss >> vec->x >> vec->y >> vec->z;
			vertex_normals->push_back(vec);
		}
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> temp_glint)
			{
				//Pushing indices into correct arrays
				if (counter == 0)
					vertex_position_indicies.push_back(temp_glint);
				else if (counter == 1)
					vertex_texcoord_indicies.push_back(temp_glint);
				else if (counter == 2)
					vertex_normal_indicies.push_back(temp_glint);

				//Handling characters
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				//Reset the counter
				if (counter > 2)
					counter = 0;
			}
		}
		else
		{

		}
	}

	//Load in all indices
	for (size_t i = 0; i < vertex_position_indicies.size(); ++i)
	{
		verticies->push_back(std::make_shared<Vertex>());
		verticies->at(i)->position = vertex_positions.get()->at(vertex_position_indicies[i] - 1);
		verticies->at(i)->texcoord = vertex_texcoords.get()->at(vertex_texcoord_indicies[i] - 1);
		verticies->at(i)->normal = vertex_normals.get()->at(vertex_normal_indicies[i] - 1);
		verticies->at(i)->color->x = 0; 
		verticies->at(i)->color->y = 0; 
		verticies->at(i)->color->z = 0;
	}

	//DEBUG
	std::cout << "Nr of vertices: " << vertex_position_indicies.size() << "\n";

	//Loaded success
	std::cout << "OBJ file loaded!" << "\n";
}

bool Mesh::read_file()
{
    return true;
}
