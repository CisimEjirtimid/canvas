#include "pch.h"

namespace cisim::canvas::dx::shader
{
    namespace
    {
        static constexpr auto one = "1";
    }

    std::vector<D3D_SHADER_MACRO> Macros::raw() const
    {
        std::vector<D3D_SHADER_MACRO> result;

        for (auto& define : *this)
            result.push_back(D3D_SHADER_MACRO{ define.data(), one });

        result.push_back(D3D_SHADER_MACRO{ nullptr, nullptr });

        return result;
    }
}
