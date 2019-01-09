#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <sci/Components/Transform.hpp>
#include <sci/GameObject.hpp>

Camera::Camera(GameObject & game_object)
    : Component(game_object)
    , field_of_view(60.0f)
{
}

Camera::~Camera()
{
}

void Camera::calculate_matrix_projection(float ratio)
{
    projection = glm::perspective(glm::radians(field_of_view), ratio, 0.1f, 1000.0f);
}

void Camera::calculate_matrix_view()
{
    auto transform = get_owner().get_component<Transform>();
    auto& pos = transform->get_position();
    auto rot = transform->get_rotation();

    m_dir.x = glm::cos(glm::radians(rot.y)) * glm::cos(glm::radians(rot.x));
    m_dir.y = glm::sin(glm::radians(rot.x));
    m_dir.z = glm::sin(glm::radians(rot.y )) * glm::cos(glm::radians(rot.x));
    m_dir = glm::normalize(m_dir);

    glm::vec3 up(glm::cos(glm::radians(rot.z)), glm::sin(glm::radians(rot.z)), 0.0f);

    view = glm::lookAt(glm::vec3(pos.x, pos.y, pos.z), pos + m_dir, up);
}

void Camera::set_fov(float value)
{
    field_of_view = value;
}

const glm::mat4x4& Camera::get_matrix_projection() const
{
    return projection;
}

const glm::mat4x4& Camera::get_matrix_view() const
{
    return view;
}
