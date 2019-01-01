#include "MeshRender.hpp"

#include <GL/glew.h>

MeshRender::MeshRender(GameObject& game_object)
    : Component(game_object)
    , color(1.0f)
{
    create_render_data();
}

MeshRender::~MeshRender()
{
    glDeleteVertexArrays(1, &m_vertex_array_object);
    glDeleteBuffers(1, &m_buffer_object_vertex);
    glDeleteBuffers(1, &m_buffer_object_indices);
}

void MeshRender::create_render_data()
{
    const unsigned int vertices_size = 4 * 3;
    const float vertices[vertices_size] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    const unsigned int indices_size = 2 * 3;
    const unsigned int indices[indices_size] = {
        0, 1, 2,
        1, 2, 3,
    };

    glGenVertexArrays(1, &m_vertex_array_object);
    glBindVertexArray(m_vertex_array_object);

    glGenBuffers(1, &m_buffer_object_vertex);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object_vertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_size, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_buffer_object_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_object_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_size, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}
