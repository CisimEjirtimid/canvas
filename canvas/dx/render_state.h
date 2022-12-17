#pragma once

namespace cisim::canvas::dx
{
    class RenderState
    {
        parameters::PrimitiveTopology _primitive_topology =  parameters::PrimitiveTopology::Enum::Undefined;

        d3d::InputLayoutPtr _input_layout = nullptr;
        d3d::BlendStatePtr _blend = nullptr;
        d3d::RasterizerStatePtr _rasterizer = nullptr;
        d3d::DepthStencilStatePtr _depth_stencil_state = nullptr;

        parameters::Scissor _scissor;
        parameters::Viewport _viewport;

    public:
        RenderState& set(const parameters::PrimitiveTopology& topology);
        RenderState& set(const parameters::InputLayout& parameters);
        RenderState& set(const parameters::BlendState& parameters);
        RenderState& set(const parameters::RasterizerState& parameters);
        RenderState& set(const parameters::DepthStencilState& parameters);
        RenderState& set(const parameters::Scissor& scissor);
        RenderState& set(const parameters::Viewport& viewport);

        parameters::PrimitiveTopology primitive_topology() const;
        d3d::InputLayoutPtr input_layout() const;
        d3d::BlendStatePtr blend() const;
        d3d::RasterizerStatePtr rasterizer() const;
        d3d::DepthStencilStatePtr depth_stencil() const;
        parameters::Scissor scissor() const;
        parameters::Viewport viewport() const;
    };
}
