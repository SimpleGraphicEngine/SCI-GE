#include "Component.hpp"

Component::Component(GameObject& game_object)
    : m_game_object(game_object)
{
}

Component::~Component()
{
}

GameObject& Component::get_owner() const
{
    return m_game_object;
}
