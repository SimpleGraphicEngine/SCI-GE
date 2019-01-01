#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <sci/Enums.hpp>
#include <sci/Macros.hpp>

class GameObject;

class Component
{
public:
    Component(GameObject& game_object);
    virtual ~Component();

protected:
    GameObject& get_owner() const;

private:
    GameObject& m_game_object;
};

#endif // !COMPONENT_HPP
