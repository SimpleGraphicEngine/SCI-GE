#ifndef MESH_RENDER_HPP
#define MESH_RENDER_HPP

#include <sci/Components/Component.hpp>
#include <glm/glm.hpp>

class MeshRender final
    : public Component
{
public:
    MeshRender(GameObject& game_object);
    virtual ~MeshRender();

    COMPONENT_STATIC_GET_TYPE(ComponentType::MeshRender)

    unsigned int m_vertex_array_object;
    glm::vec4 color;

protected:
    void create_render_data();

private:
    unsigned int m_buffer_object_vertex;
    unsigned int m_buffer_object_indices;
};

#endif // !RENDER_HPP
