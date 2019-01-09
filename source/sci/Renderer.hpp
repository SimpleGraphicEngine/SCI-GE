#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <sci/Manager.hpp>
#include <sci/Shader.hpp>

#include <vector>
#include <map>
#include <sci/GameObject.hpp>

#include <sci/Components/Camera.hpp>

struct WindowData
{
    const char* title = "SCI GE";
    unsigned int width = 1280;
    unsigned int height = 720;
    unsigned int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
    bool vertical_synchronization = true;
};

class Renderer final
    : public Manager
{
public:
    Renderer(Application& application);
    virtual ~Renderer();

    MANAGER_STATIC_GET_TYPE(ManagerType::Renderer)

    void set_gl_viewport(const glm::uvec2& min, const glm::uvec2& max);
    void clear();
    void swap_buffers();

    void on_event(const SDL_Event& event, float deltaTime);
    void render();

protected:
    virtual void on_initialize() override;
    virtual void on_terminate() override;

    void initialize_sdl();
    void terminate_sdl();

    void initialize_open_gl();
    void terminate_open_gl();

private:
    WindowData m_window_data;
    SDL_Window* m_window;
    SDL_GLContext m_gl_context;

    Shader* m_default_shader;

    GameObject m_camera;
    Camera* m_camera_component;

    struct cube {

        struct data {
            glm::vec4 color;
            glm::vec3 position;
            glm::vec3 rotation;
            glm::vec3 scale = glm::vec3(1.0f);
        };

        enum side {
            TOP,
            BOTTOM,
            LEFT,
            RIGHT,
            FORWARD,
            BACK,
        };

        const std::map<side, data> data {
            {
                side::TOP, {glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)}
            },
            {
                side::BOTTOM, {glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)}
            },
            {
                side::LEFT, {glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f)}
            },
            {
                side::RIGHT, {glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f)}
            },
            {
                side::FORWARD, {glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.5f)}
            },
            {
                side::BACK, {glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -0.5f)}
            },
        };
    } cube_helper;

    std::vector<GameObject*> m_game_objects;
};

#endif // !RENDERER_HPP
