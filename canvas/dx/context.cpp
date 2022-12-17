#include "pch.h"

namespace cisim::canvas::dx
{
    void Context::apply(d3d::DeviceContextPtr& context, const RenderState& state)
    {
        D3D11_PRIMITIVE_TOPOLOGY primitive_topology_current;
        context->IAGetPrimitiveTopology(&primitive_topology_current);
        if (primitive_topology_current != state.primitive_topology().underlying())
            context->IASetPrimitiveTopology(state.primitive_topology().underlying());

        d3d::InputLayoutPtr input_layout_current;
        context->IAGetInputLayout(input_layout_current.put());
        if (input_layout_current != state.input_layout())
            context->IASetInputLayout(state.input_layout().get());

        d3d::BlendStatePtr blend_current;
        std::array<float, 4> blend_factor; uint sample_mask;
        context->OMGetBlendState(blend_current.put(), blend_factor.data(), &sample_mask);
        if (blend_current != state.blend())
            context->OMSetBlendState(state.blend().get(), blend_factor.data(), sample_mask);

        d3d::RasterizerStatePtr rasterizer_current;
        context->RSGetState(rasterizer_current.put());
        if (rasterizer_current != state.rasterizer())
            context->RSSetState(state.rasterizer().get());

        d3d::DepthStencilStatePtr depth_stencil_current;
        uint stencil_ref;
        context->OMGetDepthStencilState(depth_stencil_current.put(), &stencil_ref);
        if (depth_stencil_current != state.depth_stencil())
            context->OMSetDepthStencilState(state.depth_stencil().get(), stencil_ref);

        state.viewport().apply(context);
        state.scissor().apply(context);
    }

    void Context::apply(d3d::DeviceContextPtr& context, const std::map<std::string, Constant>& constants)
    {
        for (auto& [_, constant] : constants)
        {
            auto& [stage, slot, buffer] = constant;
            auto& set = _constant_buffers_setters[stage];

            ID3D11Buffer* buffers[] = { buffer.get() };
            (context.get()->*set)(slot, 1, buffers);
        }
    }

    void Context::apply(d3d::DeviceContextPtr& context, const Vertices& vertices)
    {
        ID3D11Buffer* buffers[] = { vertices.buffer.get() };
        context->IASetVertexBuffers(0, 1, buffers, &vertices.stride, &vertices.offset);
    }

    void Context::apply(d3d::DeviceContextPtr& context, const d3d::Shaders& shaders)
    {
        apply(context, shaders, std::make_index_sequence<shader_types::size>());
    }

    void Context::draw(const DrawState& state)
    {
        auto& ctx = dx::DeviceState::instance().context;

        apply(ctx, state.render_state);
        apply(ctx, state.constants);
        apply(ctx, state.vertices);
        apply(ctx, state.shaders());

        // TODO: draw indexed, draw instanced, with different size, offset
        ctx->Draw(state.vertices.size, 0);
    }
}
