#pragma once

namespace cisim::canvas::dx::parameters
{
    enum class FillMode
    {
        Wireframe = D3D11_FILL_WIREFRAME,
        Solid = D3D11_FILL_SOLID
    };

    enum class CullMode
    {
        None = D3D11_CULL_NONE,
        Front = D3D11_CULL_FRONT,
        Back = D3D11_CULL_BACK
    };

    struct RasterizerState
    {
        FillMode fill;
        CullMode cull;

        bool front_counter_clockwise;
        bool multisample;
        bool antialiased_line;
        bool scissor;

        inline D3D11_RASTERIZER_DESC to_descriptor() const
        {
            D3D11_RASTERIZER_DESC result;
            std::memset(&result, 0, sizeof(D3D11_RASTERIZER_DESC));

            result.FillMode = D3D11_FILL_MODE(fill);
            result.CullMode = D3D11_CULL_MODE(cull);
            result.FrontCounterClockwise = front_counter_clockwise;
            result.MultisampleEnable = multisample;
            result.AntialiasedLineEnable = antialiased_line;
            result.ScissorEnable = scissor;

            return result;
        }
    };
}
