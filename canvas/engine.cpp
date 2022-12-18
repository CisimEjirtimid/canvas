#include "pch.h"

namespace cisim::canvas
{
    State::State(Channel<Message>& o)
        : output(o)
    {}

    void Engine::onStart(State& state)
    {
        try
        {
            dx::DeviceState::instance().init();
        }
        catch (const winrt::hresult_error& error)
        {
            auto message = std::format(
                "HRESULT Error {:#x}: {}",
                uint32_t(error.code()),
                winrt::to_string(error.message()));

            state.output.send(Error{ "INIT", message });
        }
    }

    void Engine::tick(State& state)
    {
        auto& device = dx::DeviceState::instance();

        device.clear({ 0.5f, 1.0f, 0.7f, 1.0f });

        // TODO: sort draw states, draw sorted
        for (auto& entity : state.entities)
            state.context.draw(entity->get_draw_state());

        device.present();
    }

    void Engine::execute([[maybe_unused]] State& state, [[maybe_unused]] Noop& cmd)
    {
        // NOOP
    }

    void Engine::execute(State& state, GetSwapChain& cmd)
    {
        state.output.send(SwapChain{ dx::DeviceState::instance().swap_chain });
    }

    void Engine::execute([[maybe_unused]] State& state, Resize& cmd)
    {
        dx::DeviceState::instance().framebuffer_resize(cmd.size);
    }

    void Engine::execute(State& state, Insert& cmd)
    {
        // TEST
        auto line = std::make_unique<entity::Line>();

        line->insert({
            float3{ 0.f, 0.f },
            float3{ 0.5f, 0.5f },
            float3{ 0.5f, -0.5f },
            float3{ -0.5f, -0.5f },
            float3{ -0.5f, 0.5f },
            float3{ -0.01f, 0.f },
            float3{ 0.49f, 0.5f },
            float3{ -0.49f, 0.5f }
        });
        line->compile();

        state.entities.push_back(std::move(line));
    }

    void Engine::execute(State& state, Delete& cmd)
    {
    }
}
