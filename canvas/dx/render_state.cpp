#include "pch.h"

namespace cisim::canvas::dx
{
    RenderState& RenderState::set(const parameters::PrimitiveTopology& topology)
    {
        _primitive_topology = topology;

        return *this;
    }

    RenderState& RenderState::set(const parameters::InputLayout& parameters)
    {
        auto& state = dx::DeviceState::instance();

        auto descriptor = parameters.to_descriptor();

        // temporary shader blob, for input layout verification, generated from input layout
        // this effectively decouples InputLayout creation from Vertex Shader creation
        auto signature = parameters.to_input_signature();
        auto blob = state.compile_shader<d3d::VertexShaderPtr>({ signature, "main" });

        winrt::check_hresult(state.device->CreateInputLayout(
            descriptor.data(), uint(descriptor.size()),
            blob->GetBufferPointer(), blob->GetBufferSize(),
            _input_layout.put()));

        return *this;
    }

    RenderState& RenderState::set(const parameters::BlendState& parameters)
    {
        auto descriptor = parameters.to_descriptor();
        winrt::check_hresult(dx::DeviceState::instance().device->CreateBlendState(&descriptor, _blend.put()));

        return *this;
    }

    RenderState& RenderState::set(const parameters::RasterizerState& parameters)
    {
        auto descriptor = parameters.to_descriptor();
        winrt::check_hresult(dx::DeviceState::instance().device->CreateRasterizerState(&descriptor, _rasterizer.put()));

        return *this;
    }

    RenderState& RenderState::set(const parameters::DepthStencilState& parameters)
    {
        auto descriptor = parameters.to_descriptor();
        winrt::check_hresult(dx::DeviceState::instance().device->CreateDepthStencilState(&descriptor, _depth_stencil_state.put()));

        return *this;
    }

    RenderState& RenderState::set(const parameters::Scissor& scissor)
    {
        _scissor = scissor;

        return *this;
    }
    RenderState& RenderState::set(const parameters::Viewport& viewport)
    {
        _viewport = viewport;

        return *this;
    }

    parameters::PrimitiveTopology RenderState::primitive_topology() const
    {
        return _primitive_topology;
    }

    d3d::InputLayoutPtr RenderState::input_layout() const
    {
        return _input_layout;
    }

    d3d::BlendStatePtr RenderState::blend() const
    {
        return _blend;
    }

    d3d::RasterizerStatePtr RenderState::rasterizer() const
    {
        return _rasterizer;
    }

    d3d::DepthStencilStatePtr RenderState::depth_stencil() const
    {
        return _depth_stencil_state;
    }

    parameters::Scissor RenderState::scissor() const
    {
        return _scissor;
    }

    parameters::Viewport RenderState::viewport() const
    {
        return _viewport;
    }
}
