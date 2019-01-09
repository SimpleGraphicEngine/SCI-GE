#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <sci/Components/Component.hpp>
#include <glm/glm.hpp>

class Camera final
    : public Component
{
public:
    Camera(GameObject& game_object);
    virtual ~Camera();

    COMPONENT_STATIC_GET_TYPE(ComponentType::Camera)

    void calculate_matrix_projection(float ratio);
    void calculate_matrix_view();

    void set_fov(float value);

    const glm::mat4x4& get_matrix_projection() const;
    const glm::mat4x4& get_matrix_view() const;

    const glm::vec3& get_forward() const { return m_dir; }

private:
    float field_of_view;
    glm::mat4x4 projection;
    glm::mat4x4 view;


    glm::vec3 m_dir;
};

#endif // !CAMERA_HPP
