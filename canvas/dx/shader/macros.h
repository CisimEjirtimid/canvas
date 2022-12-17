#pragma once

namespace cisim::canvas::dx::shader
{
    class Macros
        : public std::set<std::string_view>
    {
    public:
        std::vector<D3D_SHADER_MACRO> raw() const;
    };
}
