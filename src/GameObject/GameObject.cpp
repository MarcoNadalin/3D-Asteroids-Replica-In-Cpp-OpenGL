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

GameObject::GameObject(const char* obj_file_location, float x, float y, float z)
{
    /* initialise the vector at position (x,y,z) */
    this->transform = std::make_shared<Transform>(x, y, z);
    this->tag = tag;
    this->mesh = std::make_unique<Mesh>(obj_file_location);
}

void GameObject::Update(float dt)
{

}

void GameObject::RenderGameObject()
{  
    glPushMatrix();  

    if (this->load_identity_before_render) {
        glLoadIdentity();
    }    
    /* Translate before rotation so it rotates around the pivot point */
    glTranslatef(transform->pivot_position->x, transform->pivot_position->y, transform->pivot_position->z);
    glRotatef(transform->euler_angles->x, 1, 0, 0);
    glRotatef(transform->euler_angles->y, 0, 1, 0);
    glRotatef(transform->euler_angles->z, 0, 0, 1);
    glScalef(scale, scale, scale);
    
    Render();

    glPopMatrix();
    
}

void GameObject::CreateVerticies()
{

}

void GameObject::CreateVerticies(std::vector<Vertex*> verticies)
{
    for (auto& vertex : verticies) {
        glVertex3f(vertex->x, vertex->y, vertex->z);
    }
}

void GameObject::RenderVerticies(GLenum render_mode)
{   
    glEnable(GL_TEXTURE_2D);

    if (this->texture != NULL) {        
        glBindTexture(GL_TEXTURE_2D, this->texture);
    }

    glBegin(render_mode);
    for (auto& vertex : *this->mesh->getVerticies()) {
        glTexCoord2f(vertex->texcoord->x, vertex->texcoord->y);
        glNormal3f(vertex->normal->x, vertex->normal->y, vertex->normal->z);
        glTexCoord2f(vertex->texcoord->x, vertex->texcoord->y);
        glVertex3f(vertex->position->x, vertex->position->y, vertex->position->z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
}

void GameObject::AddVertex(float x, float y, float z)
{
}

void GameObject::AddVertex(std::vector<Vertex*> verticies, float x, float y, float z)
{

}

void GameObject::AddVertex(float x, float y, float z, int r, int g, int b)
{

}

void GameObject::Move(const Vector3f& velocity)
{
    this->transform->pivot_position->x += velocity.x;
    this->transform->pivot_position->y += velocity.y;
    this->transform->pivot_position->z += velocity.z;
}

Vector3f& GameObject::Forward(const float& x, const float& y, const float& z)
{
    return Vector3f(x, y, z).RotateZ(this->transform->euler_angles->z);
}

void GameObject::ChangeColour(int r, int g, int b)
{

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

CircleCollider* GameObject::GetCollider()
{
    return new CircleCollider(*this->transform, 75);
}