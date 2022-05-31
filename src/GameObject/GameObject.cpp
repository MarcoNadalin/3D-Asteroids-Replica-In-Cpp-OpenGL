#include "GameObject.h"

GameObject::GameObject() {
	/* initialise the vector at position (0,0,0) */
	this->transform = std::make_shared<Transform>();
}

GameObject::GameObject(float x, float y, float z) {
    /* initialise the vector at position (x,y,z) */
    this->transform = std::make_shared<Transform>(x, y, z);
    this->tag = tag;
}

void GameObject::Update(float dt)
{

}

void GameObject::RenderGameObject()
{  
    glPushMatrix();
    glLoadIdentity();    

    /* Translate before rotation so it rotates around the pivot point */
    glTranslatef(transform->pivot_position->x, transform->pivot_position->y, transform->pivot_position->z);
    glRotatef(transform->euler_angles->z, 0, 0, 1);
    glScalef(scale, scale, scale);

    Render();

    glPopMatrix();
    
}

void GameObject::CreateVerticies()
{
    for (auto& vertex : this->verticies) {
        glColor3f(vertex->r, vertex->g, vertex->b);
        glVertex3f(vertex->x, vertex->y, vertex->z);
    }
}

void GameObject::CreateVerticies(std::vector<Vertex*> verticies)
{
    for (auto& vertex : verticies) {
        glColor3f(vertex->r, vertex->g, vertex->b);
        glVertex3f(vertex->x, vertex->y, vertex->z);
    }
}

void GameObject::RenderVerticies(GLenum render_mode)
{
    glBegin(render_mode);
    for (auto& vertex : this->verticies) {

        glColor3f(vertex->r, vertex->g, vertex->b);
        glVertex3f(vertex->x, vertex->y, vertex->z);
    }
    glEnd();
}

void GameObject::AddVertex(float x, float y, float z)
{
    struct Vertex* vertex = new Vertex;
    vertex->x = x;
    vertex->y = y;
    vertex->z = z;
    this->verticies.push_back(vertex);
}

void GameObject::AddVertex(std::vector<Vertex*> verticies, float x, float y, float z)
{
    struct Vertex* vertex = new Vertex;
    vertex->x = x;
    vertex->y = y;
    vertex->z = z;
    verticies.push_back(vertex);
}

void GameObject::AddVertex(float x, float y, float z, int r, int g, int b)
{
    struct Vertex* vertex = new Vertex;
    vertex->x = x;
    vertex->y = y;
    vertex->z = z;
    vertex->r = r;
    vertex->g = g;
    vertex->b = b;
    this->verticies.push_back(vertex);
}

void GameObject::Move(const Vector3f& velocity)
{
    this->transform->pivot_position->x += velocity.x;
    this->transform->pivot_position->y += velocity.y;
}

Vector3f& GameObject::Forward(const float& x, const float& y, const float& z)
{
    return Vector3f(x, y, z).RotateZ(this->transform->euler_angles->z);
}

void GameObject::ChangeColour(int r, int g, int b)
{
    for (auto& vertex : this->verticies) {
        vertex->r = r;
        vertex->g = g;
        vertex->b = b;
    }
}

float GameObject::GetScale()
{
    return this->scale;
}

void GameObject::SetScale(float scale)
{
    this->scale = scale;
}

std::string GameObject::GetTag()
{
    return this->tag;
}

std::vector<Vertex*> GameObject::GetVerticies()
{
    return verticies;
}

CircleCollider* GameObject::GetCollider()
{
    return new CircleCollider(*this->transform, 75);
}