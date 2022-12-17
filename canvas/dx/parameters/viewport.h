#pragma once

namespace cisim::canvas::dx::parameters
{
    struct Viewport
    {
        float2 top_left;
        float2 bottom_right;
        Rangef depth;

        inline D3D11_VIEWPORT to_descriptor() const;

        static Viewport from_descriptor(D3D11_VIEWPORT viewport);

        void apply(d3d::DeviceContextPtr& context) const;

        inline bool operator==(const Viewport& other) const;
    };
}
