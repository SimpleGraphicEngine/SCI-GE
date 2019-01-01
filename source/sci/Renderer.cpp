#include "Renderer.hpp"

#include <string>
#include <GL/glew.h>

#include <sci/Application.hpp>
#include <sci/Logger.hpp>
#include <sci/Timer.hpp>

Renderer::Renderer(Application& application)
    : Manager(application)
    , m_window(nullptr)
{
}

Renderer::~Renderer()
{
}

void Renderer::set_gl_viewport(const glm::uvec2 & min, const glm::uvec2& max)
{
    glViewport(min.x, min.y, max.x, max.y);
}

void Renderer::clear()
{
    glClearColor(0.66f, 0.66f, 0.66f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::swap_buffers()
{
    SDL_GL_SwapWindow(m_window);
}

void Renderer::render()
{
    m_default_shader->use();
    glBindVertexArray(m_vertex_array_object);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::on_initialize()
{
    initialize_sdl();
    initialize_open_gl();

    set_gl_viewport(glm::uvec2(0, 0), glm::uvec2(m_window_data.width, m_window_data.height));

    m_default_shader = new Shader(g_default_vertex_shader_source, g_default_fragment_shader_source);
    create_render_data();
}

void Renderer::on_terminate()
{
    clean_up();
    terminate_open_gl();
    terminate_sdl();
}

void Renderer::initialize_sdl()
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    m_window = SDL_CreateWindow(m_window_data.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_window_data.width, m_window_data.height, m_window_data.flags);
}

void Renderer::terminate_sdl()
{
    SDL_DestroyWindow(m_window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void Renderer::initialize_open_gl()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    m_gl_context = SDL_GL_CreateContext(m_window);
    glewInit();

    SDL_GL_SetSwapInterval(m_window_data.vertical_synchronization);

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
}

void Renderer::terminate_open_gl()
{
    SDL_GL_DeleteContext(m_gl_context);
}

void Renderer::create_render_data()
{
    const unsigned int vertices_size = 9;
    const float vertices[vertices_size] = {
        -0.5f, -0.25f, 0.0f,
        0.0f, 0.75f, 0.0f,
        0.5f, -0.25f, 0.0f,
    };

    const unsigned int indices_size = 3;
    const unsigned int indices[indices_size] = {
        0, 1, 2,
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

void Renderer::clean_up()
{
    glDeleteVertexArrays(1, &m_vertex_array_object);
    glDeleteBuffers(1, &m_buffer_object_vertex);
    glDeleteBuffers(1, &m_buffer_object_indices);
}
