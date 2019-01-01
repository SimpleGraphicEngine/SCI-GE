#include "Transform.hpp"

Transform::Transform(GameObject& game_object)
    : Component(game_object)
    , m_position(glm::vec3(0.0f))
    , m_rotation(glm::vec3(0.0f))
    , m_scale(glm::vec3(1.0f))
{
    calculate_matrix();
}

Transform::~Transform()
{
}

const glm::vec3& Transform::get_position() const
{
    return m_position;
}

void Transform::set_position(const glm::vec3 & value)
{
    m_position = value;
    calculate_matrix();
}

const glm::vec3& Transform::get_rotation() const
{
    return m_rotation;
}

void Transform::set_rotation(const glm::vec3& value)
{
    m_rotation = value;
    calculate_matrix();
}

const glm::vec3& Transform::get_scale() const
{
    return m_scale;
}

void Transform::set_scale(const glm::vec3& value)
{
    m_scale = value;
    calculate_matrix();
}

void Transform::calculate_matrix()
{
    m_matrix = glm::mat4x4(1.0f);
    m_matrix = glm::translate(m_matrix, m_position);
    m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_matrix = glm::scale(m_matrix, m_scale);
}

const glm::mat4x4 & Transform::get_matrix() const
{
    return m_matrix;
}
