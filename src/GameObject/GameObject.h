#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

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

# include <windows.h>
# include <GL/gl.h>
#include <cmath>

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "./Components/Transform.h"
#include "../GameObject/Components/CircleCollider.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Vertex.h"


/**
* The parent class that all objects within the game inherit. All objects on the screen are GameObjects
*/
class GameObject
{
private:
	float scale = 1;

protected:
	std::string tag = "GameObject";

public:

	std::shared_ptr<Transform> transform;
	std::shared_ptr<Mesh> mesh;

	float rotation = 0;
	float rotationDelta = 75;

	GameObject();
	GameObject(float x, float y, float z);
	GameObject(const char* obj_file_location, float x, float y, float z);
	/**
	* The update method for each game object. must be implemented in child classes
	* 
	* @param dt DeltaTime
	*/
	virtual void Update(float dt) = 0;

	/**
	* A default rendering method that renders all vertexes as white, using GL_POLYGON.
	* This method is called in the Render() method.
	*/
	virtual void RenderGameObject();

	/**
	* The render method for each game object. Must be implemented in child classes.
	*/
	virtual void Render() = 0;

	/**
	* Returns the GameObjects circle collider
	* 
	* @return the CircleCollider pointer of the game object
	*/
	CircleCollider* GetCollider();

	/**
	* Calls glVertex3f() for each vertex in the verticies vector
	*/
	void CreateVerticies();

	/**
	* Calls glVertex3f() for each vertex in the verticies vector
	*/
	void CreateVerticies(std::vector<Vertex*> verticies);

	void RenderVerticies(GLenum render_mode);

	/**
	* Adds a vertex to the verticies vector
	* 
	* @param x the x value of the vertex
	* @param y the y value of the vertex
	* @param z the z value of the vertex
	*/
	void AddVertex(float x, float y, float z);

	/**
	* Adds a vertex to the verticies vector
	*
	* @param x the x value of the vertex
	* @param y the y value of the vertex
	* @param z the z value of the vertex
	*/
	void AddVertex(std::vector<Vertex*> verticies, float x, float y, float z);

	/**
	* Adds a vertex to the verticies vector, with the rgb value of the vertex
	*
	* @param x the x value of the vertex
	* @param y the y value of the vertex
	* @param z the z value of the vertex
	* @param r the red value of the vertex
	* @param g the green value of the vertex
	* @param b the blue value of the vertex
	*/
	void AddVertex(float x, float y, float z, int r, int g, int b);

	/**
	* Moves the current GameObject by a vector
	* 
	* @param velocity the vector containing the gameobjects velocity
	*/
	void Move(const Vector3f& velocity);

	/**
	* Returns a vector which faces the same direction as the player
	* 
	* @return a vector pointer which faces the same direction as the player
	*/
	Vector3f& Forward(const float& x, const float& y, const float& z);

	/**
	* Changes the rendering colour of the game object
	* 
	* @param r 
	* @param g
	* @param b
	*/
	void ChangeColour(int r, int g, int b);

	float GetScale();
	void SetScale(float scale);


	std::string GetTag();
};

#endif


