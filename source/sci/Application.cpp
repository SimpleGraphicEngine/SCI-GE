#include "Application.hpp"

#include <sci/Logger.hpp>
#include <sci/Timer.hpp>
#include <sci/Renderer.hpp>

Application::Application()
    : m_status(MainLoopStatus::SUCCESS)
{
    m_managers[ManagerType::Logger] = new Logger(*this);
    m_managers[ManagerType::Timer] = new Timer(*this);
    m_managers[ManagerType::Renderer] = new Renderer(*this);

    for (auto manager : m_managers) {
        manager->initialize();
    }
}

Application::~Application()
{
    for (auto& manager : m_managers) {
        manager->terminate();
        delete manager;
        manager = nullptr;
    }
}

MainLoopStatus::Enum Application::main_loop()
{
    auto& renderer = get_manager<Renderer>();
    auto& timer = get_manager<Timer>();
    while (MainLoopStatus::SUCCESS == m_status) {
        float deltaTime = timer.get_delta_time();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            renderer.on_event(event, deltaTime);

            switch (event.type) {
            case SDL_QUIT:
                m_status = MainLoopStatus::CLOSE;
                break;

            case SDL_WINDOWEVENT:
                if (SDL_WINDOWEVENT_RESIZED == event.window.event) {
                    renderer.set_gl_viewport(glm::uvec2(0, 0), glm::uvec2(event.window.data1, event.window.data2));
                }
                break;
            default:
                break;
            }
        }

        renderer.clear();
        renderer.render();
        renderer.swap_buffers();
    }

    return m_status;
}
