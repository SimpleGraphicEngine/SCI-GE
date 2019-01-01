#include "GameObject.hpp"

GameObject::GameObject()
{
    m_components[ComponentType::Transform] = new Transform(*this);
    m_components[ComponentType::MeshRender] = new MeshRender(*this);
}

GameObject::~GameObject()
{
}
