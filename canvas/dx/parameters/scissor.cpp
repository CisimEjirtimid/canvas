#include "pch.h"

namespace cisim::canvas::dx::parameters
{
    inline D3D11_RECT Scissor::to_descriptor() const
    {
        auto [height, width] = dx::DeviceState::instance().framebuffer_size<float>();

        return D3D11_RECT{
            .left = long(width * top_left.x),
            .top = long(height * top_left.y),
            .right = long(width * bottom_right.x),
            .bottom = long(height * bottom_right.y)
        };
    }

    Scissor Scissor::from_descriptor(D3D11_RECT scissor)
    {
        auto [height, width] = dx::DeviceState::instance().framebuffer_size<float>();

        return Scissor{
            .top_left = float2{
                float(scissor.left) / width,
                float(scissor.top) / height
            },
            .bottom_right = float2{
                float(scissor.right) / width,
                float(scissor.bottom) / height
            }
        };
    };

    void Scissor::apply(d3d::DeviceContextPtr& context) const
    {
        D3D11_RECT temp; uint num = 1;
        context->RSGetScissorRects(&num, &temp);
        Scissor current = from_descriptor(temp);

        if (current != *this)
        {
            auto descriptor = to_descriptor();
            context->RSSetScissorRects(1, &descriptor);
        }
    }

    inline bool Scissor::operator==(const Scissor& other) const
    {
        return std::tie(top_left, bottom_right)
            == std::tie(other.top_left, other.bottom_right);
    }
}
