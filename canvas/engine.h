#pragma once

namespace cisim::canvas
{
    using Noop = std::monostate;

    struct Success
    {
        std::string id;
    };

    struct Error
    {
        std::string id;
        std::string what;
    };

    struct SwapChain
    {
        dx::dxgi::SwapChain1Ptr swap_chain;
    };

    using Message = std::variant<Noop, Success, Error, SwapChain>;

    struct GetSwapChain : public Awaitable
    {
    };

    struct Resize
    {
        SizeU size;
    };

    struct Insert
    {
        std::filesystem::path mesh;
    };

    struct Delete
    {
        std::string id;
    };

    using Commands = std::variant<Noop, GetSwapChain, Resize, Insert, Delete>;

    struct State
    {
        Channel<Message>& output;

        dx::Context context;
        std::vector<entity::Base::Ptr> entities;

        State(Channel<Message>& o);
    };

    struct Engine : public Thread<State, Commands>
    {
        void onStart(State& state);

        void tick(State& state);

        void execute([[maybe_unused]] State& state, [[maybe_unused]] Noop& cmd);
        void execute(State& state, GetSwapChain& cmd);
        void execute([[maybe_unused]] State& state, Resize& cmd);
        void execute(State& state, Insert& cmd);
        void execute(State& state, Delete& cmd);
    };
}

/*
namespace cisim::test
{
    struct ThreadTest : public async::Thread
    {
        void tick()
        {
            std::cout << "Tick called" << std::endl;
        }
   };
}*/

