#include "pch.h"

namespace cisim::canvas::dx::parameters
{
    inline D3D11_VIEWPORT Viewport::to_descriptor() const
    {
        auto [height, width] = dx::DeviceState::instance().framebuffer_size<float>();

        return D3D11_VIEWPORT{
            .TopLeftX = width * top_left.x,
            .TopLeftY = height * top_left.y,
            .Width = width * (bottom_right.x - top_left.x),
            .Height = height * (bottom_right.y - top_left.y),
            .MinDepth = depth.from,
            .MaxDepth = depth.to
        };
    }

    Viewport Viewport::from_descriptor(D3D11_VIEWPORT viewport)
    {
        auto [height, width] = dx::DeviceState::instance().framebuffer_size<float>();

        return Viewport{
            .top_left = float2{
                viewport.TopLeftX / width,
                viewport.TopLeftY / height
            },
            .bottom_right = float2{
                (viewport.Width - viewport.TopLeftX) / width,
                (viewport.Height - viewport.TopLeftY) / height
            },
            .depth = Rangef{
                viewport.MinDepth,
                viewport.MaxDepth
            }
        };
    }

    void Viewport::apply(d3d::DeviceContextPtr& context) const
    {
        D3D11_VIEWPORT temp; uint num = 1;
        context->RSGetViewports(&num, &temp);
        Viewport current = from_descriptor(temp);

        if (current != *this)
        {
            auto descriptor = to_descriptor();
            context->RSSetViewports(1, &descriptor);
        }
    }

    inline bool Viewport::operator==(const Viewport& other) const
    {
        return std::tie(top_left, bottom_right, depth)
            == std::tie(other.top_left, other.bottom_right, other.depth);
    }
}
