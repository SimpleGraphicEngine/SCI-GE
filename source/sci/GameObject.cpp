#include "GameObject.hpp"

GameObject::GameObject()
{
    m_components[ComponentType::Transform] = new Transform(*this);
}

GameObject::~GameObject()
{
}
