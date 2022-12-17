#pragma once

namespace cisim::canvas::dx::parameters
{
    enum class DepthWriteMask
    {
        Zero = D3D11_DEPTH_WRITE_MASK_ZERO,
        All = D3D11_DEPTH_WRITE_MASK_ALL
    };

    struct DepthState
    {
        bool enabled;
        DepthWriteMask write_mask;
        ComparisonFunction function;
    };
}
