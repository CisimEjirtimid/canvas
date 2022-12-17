#pragma once

namespace cisim::canvas::dx
{
    class Context
    {
        #pragma region SetConstantBuffers
        using SetConstantBuffers = void(ID3D11DeviceContext::*)(UINT, UINT, ID3D11Buffer* const*);

        std::map<PipelineStage, SetConstantBuffers> _constant_buffers_setters{
            { PipelineStage::Vertex,    &ID3D11DeviceContext::VSSetConstantBuffers },
            { PipelineStage::Hull,      &ID3D11DeviceContext::HSSetConstantBuffers },
            { PipelineStage::Domain,    &ID3D11DeviceContext::DSSetConstantBuffers },
            { PipelineStage::Geometry,  &ID3D11DeviceContext::GSSetConstantBuffers },
            { PipelineStage::Pixel,     &ID3D11DeviceContext::PSSetConstantBuffers },
            { PipelineStage::Compute,   &ID3D11DeviceContext::CSSetConstantBuffers }
        };
        #pragma endregion
        #pragma region SetShaderResources
        using SetShaderResources = void(ID3D11DeviceContext::*)(UINT, UINT, ID3D11ShaderResourceView* const*);

        std::map<PipelineStage, SetShaderResources> _shader_resources_setters{
            { PipelineStage::Vertex,    &ID3D11DeviceContext::VSSetShaderResources },
            { PipelineStage::Hull,      &ID3D11DeviceContext::HSSetShaderResources },
            { PipelineStage::Domain,    &ID3D11DeviceContext::DSSetShaderResources },
            { PipelineStage::Geometry,  &ID3D11DeviceContext::GSSetShaderResources },
            { PipelineStage::Pixel,     &ID3D11DeviceContext::PSSetShaderResources },
            { PipelineStage::Compute,   &ID3D11DeviceContext::CSSetShaderResources }
        };
        #pragma endregion
        #pragma region SetShader
        template <typename T>
        using SetShader = void(ID3D11DeviceContext::*)(T*, ID3D11ClassInstance* const*, UINT);

        template <typename T, typename UnderlyingT>
        SetShader<UnderlyingT> shader_setter()
        {
            if constexpr (IsVertexShader<T>)
                return &ID3D11DeviceContext::VSSetShader;
            else if constexpr (IsHullShader<T>)
                return &ID3D11DeviceContext::HSSetShader;
            else if constexpr (IsDomainShader<T>)
                return &ID3D11DeviceContext::DSSetShader;
            else if constexpr (IsGeometryShader<T>)
                return &ID3D11DeviceContext::GSSetShader;
            else if constexpr (IsPixelShader<T>)
                return &ID3D11DeviceContext::PSSetShader;
            else if constexpr (IsComputeShader<T>)
                return &ID3D11DeviceContext::CSSetShader;
            else
                throw std::runtime_error{ "Wrong Shader Type Provided!" };
        }

        using shader_types = TypeTuple<
            d3d::VertexShaderPtr,
            d3d::HullShaderPtr,
            d3d::DomainShaderPtr,
            d3d::GeometryShaderPtr,
            d3d::PixelShaderPtr,
            d3d::ComputeShaderPtr>;

        template <typename T>
            requires IsShader<T>
        void apply(d3d::DeviceContextPtr& context, const T& shader)
        {
            if (!shader)
                return;

            auto set = shader_setter<T, T::template type>();

            (context.get()->*set)(shader.get(), nullptr, 0);
        }

        template <size_t... Is>
        void apply(d3d::DeviceContextPtr& context, const d3d::Shaders& shaders, std::index_sequence<Is...>)
        {
            (apply(context, std::get<shader_types::get<Is>>(shaders)), ...);
        }
        #pragma endregion

        void apply(d3d::DeviceContextPtr& context, const RenderState& state);
        void apply(d3d::DeviceContextPtr& context, const std::map<std::string, Constant>& constants);
        void apply(d3d::DeviceContextPtr& context, const Vertices& vertices);
        void apply(d3d::DeviceContextPtr& context, const d3d::Shaders& shaders);

    public:
        void draw(const DrawState& state);
    };
}
