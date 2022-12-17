#pragma once

namespace cisim::canvas::dx::parameters
{
    struct Scissor
    {
        float2 top_left;
        float2 bottom_right;

        inline D3D11_RECT to_descriptor() const;

        static Scissor from_descriptor(D3D11_RECT scissor);

        void apply(d3d::DeviceContextPtr& context) const;

        inline bool operator==(const Scissor& other) const;
    };
}
