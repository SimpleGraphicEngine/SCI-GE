#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <sci/Components/Component.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Transform final
    : public Component
{
public:
    Transform(GameObject& game_object);
    virtual ~Transform();

    COMPONENT_STATIC_GET_TYPE(ComponentType::Transform)

    const glm::vec3& get_position() const;
    void set_position(const glm::vec3& value);

    const glm::vec3& get_rotation() const;
    void set_rotation(const glm::vec3& value);

    const glm::vec3& get_scale() const;
    void set_scale(const glm::vec3& value);

    const glm::mat4x4& get_matrix() const;

protected:
    void calculate_matrix();

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

    glm::mat4x4 m_matrix;
};

#endif // !TRANSFORM_HPP
