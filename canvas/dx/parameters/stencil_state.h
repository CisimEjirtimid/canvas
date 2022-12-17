#pragma once

namespace cisim::canvas::dx::parameters
{
    enum class StencilOperation
    {
        Keep = D3D11_STENCIL_OP_KEEP,
        Zero = D3D11_STENCIL_OP_ZERO,
        Replace = D3D11_STENCIL_OP_REPLACE,
        IncrementSaturated = D3D11_STENCIL_OP_INCR_SAT,
        DecrementSaturated = D3D11_STENCIL_OP_DECR_SAT,
        Invert = D3D11_STENCIL_OP_INVERT,
        IncrementWrap = D3D11_STENCIL_OP_INCR,
        DecrementWrap = D3D11_STENCIL_OP_DECR
    };

    struct StencilFace
    {
        StencilOperation stencil_fail_op;
        StencilOperation stencil_pass_depth_fail_op;
        StencilOperation stencil_pass_depth_pass_op;
        ComparisonFunction function;

        inline D3D11_DEPTH_STENCILOP_DESC to_descriptor() const
        {
            return D3D11_DEPTH_STENCILOP_DESC{
                .StencilFailOp = D3D11_STENCIL_OP(stencil_fail_op),
                .StencilDepthFailOp = D3D11_STENCIL_OP(stencil_pass_depth_fail_op),
                .StencilPassOp = D3D11_STENCIL_OP(stencil_pass_depth_pass_op),
                .StencilFunc = D3D11_COMPARISON_FUNC(function)
            };
        }
    };

    struct StencilState
    {
        bool enabled;
        uint8_t read_mask;
        uint8_t write_mask;

        StencilFace front;
        StencilFace back;
    };
}
