#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <array>
#include <sci/Components/Component.hpp>
#include <sci/Components/Transform.hpp>
#include <sci/Components/MeshRender.hpp>

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    template<typename T>
    T* get_component();

    template<typename T>
    T* add_component();

    std::array<Component*, ComponentType::__MAX> m_components;
protected:
private:
};

template<typename T>
inline T* GameObject::get_component()
{
    return static_cast<T*>(m_components[T::get_type()]);
}

template<typename T>
inline T * GameObject::add_component()
{
    T* component = new T(*this);
    m_components[T::get_type()] = component;
    return component;
}

#endif // !GAMEOBJECT_HPP
