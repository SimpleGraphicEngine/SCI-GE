#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <sci/Manager.hpp>
#include <sci/Shader.hpp>

#include <vector>
#include <map>
#include <sci/GameObject.hpp>

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

    //////
    float timer = 0.0f;
    glm::mat4x4 projection;
    glm::mat4x4 view;
    //////

    Shader* m_default_shader;

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
        };
    } cube_helper;

    std::vector<GameObject*> m_game_objects;
};

#endif // !RENDERER_HPP
