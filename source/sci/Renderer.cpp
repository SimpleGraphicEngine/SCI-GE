#include "Renderer.hpp"

#include <string>
#include <GL/glew.h>

#include <sci/Application.hpp>
#include <sci/Logger.hpp>
#include <sci/Timer.hpp>

Renderer::Renderer(Application& application)
    : Manager(application)
    , m_window(nullptr)
    , m_default_shader(nullptr)
    , m_camera_component(nullptr)
{
}

Renderer::~Renderer()
{
}

void Renderer::set_gl_viewport(const glm::uvec2 & min, const glm::uvec2& max)
{
    if (nullptr != m_camera_component) {
        m_camera_component->calculate_matrix_projection((float)max.x / (float)max.y);
    }
    glViewport(min.x, min.y, max.x, max.y);
}

void Renderer::clear()
{
    glClearColor(0.66f, 0.66f, 0.66f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::swap_buffers()
{
    SDL_GL_SwapWindow(m_window);
}

#include <sci/Timer.hpp>
#include <sci/Application.hpp>

void Renderer::on_event(const SDL_Event & event, float deltaTime)
{
    float pos_speed = 3.5f * deltaTime;
    float rot_speed = 150.0f * deltaTime;
    Transform* tf = m_camera.get_component<Transform>();

}

void Renderer::render()
{
    m_camera_component->calculate_matrix_view();

    m_default_shader->use();
    for (const auto& go : m_game_objects) {
        const MeshRender* mr = go->get_component<MeshRender>();
        Transform* tf = go->get_component<Transform>();

        auto tmp = m_camera_component->get_matrix_projection() * m_camera_component->get_matrix_view() * tf->get_matrix();
        m_default_shader->set_mat4("transform", tmp);
        m_default_shader->set_vec4("color", mr->color);

        glBindVertexArray(mr->m_vertex_array_object);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void Renderer::on_initialize()
{
    initialize_sdl();
    initialize_open_gl();

    set_gl_viewport(glm::uvec2(0, 0), glm::uvec2(m_window_data.width, m_window_data.height));

    m_default_shader = new Shader(g_default_vertex_shader_source, g_default_fragment_shader_source);

    ///////
    m_camera_component = m_camera.add_component<Camera>();
    m_camera_component->calculate_matrix_projection((float)m_window_data.width / (float)m_window_data.height);
    auto trans = m_camera.get_component<Transform>();
    trans->set_position(glm::vec3(0.0f, 2.0f, 10.0f));
    trans->set_rotation(glm::vec3(0.0f, -90.0f, 90.0f));
    ///////

    for (const auto& map_entry : cube_helper.data) {
        const auto& data = map_entry.second;

        auto go = new GameObject();
        auto mr = go->add_component<MeshRender>();
        mr->color = data.color;

        auto transform = go->get_component<Transform>();
        transform->set_position(data.position);
        transform->set_rotation(data.rotation);
        transform->set_scale(data.scale);

        m_game_objects.push_back(go);
    }
}

void Renderer::on_terminate()
{
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

    glEnable(GL_DEPTH_TEST);
}

void Renderer::terminate_open_gl()
{
    SDL_GL_DeleteContext(m_gl_context);
}
