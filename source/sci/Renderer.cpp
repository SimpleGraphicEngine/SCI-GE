#include "Renderer.hpp"

#include <string>
#include <GL/glew.h>

#include <sci/Application.hpp>
#include <sci/Logger.hpp>
#include <sci/Timer.hpp>

#include <glm/gtc/matrix_transform.hpp>

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
    projection = glm::perspective(glm::radians(60.0f), (float)max.x / (float)max.y, 0.1f, 1000.0f);
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
void Renderer::render()
{
    /////////
    timer += get_application().get_manager<Timer>().get_delta_time();
    float radius = 10.0f;
    float camX = sin(timer) * radius;
    float camY = sin(timer) * 5.0f;
    float camZ = cos(timer) * radius;
    view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    /////////

    m_default_shader->use();
    for (const auto& go : m_game_objects) {
        const MeshRender* mr = go->get_component<MeshRender>();
        Transform* tf = go->get_component<Transform>();

        m_default_shader->set_mat4("transform", projection * view * tf->get_matrix());
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


    for (const auto& map_entry : cube_helper.data) {
        auto go = new GameObject();
        const auto& data = map_entry.second;

        go->get_component<MeshRender>()->color = data.color;
        go->get_component<Transform>()->set_position(data.position);
        go->get_component<Transform>()->set_rotation(data.rotation);
        go->get_component<Transform>()->set_scale(data.scale);

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
