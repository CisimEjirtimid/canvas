#pragma once

namespace cisim::canvas::dx::shader
{
    class Cache : public Singleton<Cache>
    {
        std::map<std::string, d3d::VertexShaderPtr>     _vs;
        std::map<std::string, d3d::HullShaderPtr>       _hs;
        std::map<std::string, d3d::DomainShaderPtr>     _ds;
        std::map<std::string, d3d::GeometryShaderPtr>   _gs;
        std::map<std::string, d3d::PixelShaderPtr>      _ps;
        std::map<std::string, d3d::ComputeShaderPtr>    _cs;

        template <typename T>
            requires IsShader<T>
        std::map<std::string, T>& map()
        {
            if constexpr (IsVertexShader<T>)
                return _vs;
            else if constexpr (IsHullShader<T>)
                return _hs;
            else if constexpr (IsDomainShader<T>)
                return _ds;
            else if constexpr (IsGeometryShader<T>)
                return _gs;
            else if constexpr (IsPixelShader<T>)
                return _ps;
            else if constexpr (IsComputeShader<T>)
                return _cs;
            else
                throw std::runtime_error{ "Wrong Shader Type Provided!" };
        }

    public:
        Cache(token) {};

        template <typename T>
            requires IsShader<T>
        T insert(const std::string& id, const T& shader)
        {
            auto& corresponding_map = map<T>();

            corresponding_map[id] = shader;

            return shader;
        }

        template <typename T>
            requires IsShader<T>
        T get(const std::string& id)
        {
            auto& corresponding_map = map<T>();

            if (corresponding_map.contains(id))
                return corresponding_map[id];

            return nullptr;
        }
    };
}
