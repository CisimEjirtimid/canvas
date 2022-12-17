#pragma once

namespace cisim::canvas::dx
{
    #undef DrawState

    struct Constant
    {
        PipelineStage stage = PipelineStage::Unknown;
        uint slot = 0;
        d3d::BufferPtr buffer;
    };

    struct Vertices
    {
        PipelineStage stage = PipelineStage::Unknown;
        uint size = 0;
        uint stride = 0;
        uint offset = 0;
        d3d::BufferPtr buffer;
    };

    class DrawState
    {
        d3d::VertexShaderPtr    _vs;
        d3d::HullShaderPtr      _hs;    //
        d3d::DomainShaderPtr    _ds;    // these two shaders comprise tesselation stage
        d3d::GeometryShaderPtr  _gs;
        d3d::PixelShaderPtr     _ps;

        d3d::ComputeShaderPtr   _cs;

    public:
        template <typename T>
            requires IsShader<T>
        T& shader()
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

        d3d::Shaders shaders() const
        {
            return std::make_tuple(
                _vs, _hs, _ds, _gs, _ps, _cs
            );
        }

        RenderState render_state;

        std::map<std::string, Constant> constants;

        Vertices vertices;

        std::optional<d3d::BufferPtr> indices;
    };
}
