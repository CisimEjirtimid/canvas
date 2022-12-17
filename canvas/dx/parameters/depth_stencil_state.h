#pragma once

namespace cisim::canvas::dx::parameters
{
    struct DepthStencilState
    {
        DepthState depth;
        StencilState stencil;

        inline D3D11_DEPTH_STENCIL_DESC to_descriptor() const
        {
            return D3D11_DEPTH_STENCIL_DESC{
                .DepthEnable = depth.enabled,
                .DepthWriteMask = D3D11_DEPTH_WRITE_MASK(depth.write_mask),
                .DepthFunc = D3D11_COMPARISON_FUNC(depth.function),

                .StencilEnable = stencil.enabled,
                .StencilReadMask = stencil.read_mask,
                .StencilWriteMask = stencil.write_mask,

                .FrontFace = stencil.front.to_descriptor(),
                .BackFace = stencil.back.to_descriptor()
            };
        }
    };
}
