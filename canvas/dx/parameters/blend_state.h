#pragma once

namespace cisim::canvas::dx::parameters
{
    enum class BlendingFactor
    {
        Zero = D3D11_BLEND_ZERO,
        One = D3D11_BLEND_ONE,
        SourceColor = D3D11_BLEND_SRC_COLOR,
        InverseSourceColor = D3D11_BLEND_INV_SRC_COLOR,
        SourceAlpha = D3D11_BLEND_SRC_ALPHA,
        InverseSourceAlpha = D3D11_BLEND_INV_SRC_ALPHA,
        DestinationAlpha = D3D11_BLEND_DEST_ALPHA,
        InverseDestinationAlpha = D3D11_BLEND_INV_DEST_ALPHA,
        DestinationColor = D3D11_BLEND_DEST_COLOR,
        InverseDestinationColor = D3D11_BLEND_INV_DEST_COLOR,
        SourceAlphaSaturated = D3D11_BLEND_SRC_ALPHA_SAT,
        BlendFactor = D3D11_BLEND_BLEND_FACTOR,
        InverseBlendFactor = D3D11_BLEND_INV_BLEND_FACTOR,
        DualSourceColor = D3D11_BLEND_SRC1_COLOR,
        InverseDualSourceColor = D3D11_BLEND_INV_SRC1_COLOR,
        DualSourceAlpha = D3D11_BLEND_SRC1_ALPHA,
        InverseDualSourceAlpha = D3D11_BLEND_INV_SRC1_ALPHA
    };

    enum class BlendingOperation
    {
        Add = D3D11_BLEND_OP_ADD,
        Subtract = D3D11_BLEND_OP_SUBTRACT,
        ReverseSubtract = D3D11_BLEND_OP_REV_SUBTRACT,
        Minimum = D3D11_BLEND_OP_MIN,
        Maximum = D3D11_BLEND_OP_MAX
    };

    struct BlendParameters
    {
        BlendingFactor source;
        BlendingFactor destination;
        BlendingOperation operation;
    };

    enum class ColorWriteEnable
    {
        Red = D3D11_COLOR_WRITE_ENABLE_RED,
        Green = D3D11_COLOR_WRITE_ENABLE_GREEN,
        Blue = D3D11_COLOR_WRITE_ENABLE_BLUE,
        Alpha = D3D11_COLOR_WRITE_ENABLE_ALPHA,
        All = D3D11_COLOR_WRITE_ENABLE_ALL
    };

    struct BlendState
    {
        bool enabled;
        BlendParameters color_blend;
        BlendParameters alpha_blend;
        ColorWriteEnable write_mask;

        inline D3D11_BLEND_DESC to_descriptor() const
        {
            D3D11_BLEND_DESC result;
            std::memset(&result, 0, sizeof(D3D11_BLEND_DESC));

            result.RenderTarget[0] = {
                .BlendEnable = enabled,
                .SrcBlend = D3D11_BLEND(color_blend.source),
                .DestBlend = D3D11_BLEND(color_blend.destination),
                .BlendOp = D3D11_BLEND_OP(color_blend.operation),
                .SrcBlendAlpha = D3D11_BLEND(alpha_blend.source),
                .DestBlendAlpha = D3D11_BLEND(alpha_blend.destination),
                .BlendOpAlpha = D3D11_BLEND_OP(alpha_blend.operation),
                .RenderTargetWriteMask = uchar(write_mask)
            };

            return result;
        }
    };
}
