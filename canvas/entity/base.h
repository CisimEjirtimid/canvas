#pragma once

namespace cisim::canvas::entity
{
    class Base
    {
    public:
        using Ptr = std::unique_ptr<Base>;

        virtual ~Base() = default;

        virtual dx::DrawState get_draw_state() = 0;
    };
}
