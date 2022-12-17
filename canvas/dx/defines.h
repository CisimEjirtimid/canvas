#pragma once

namespace cisim::canvas
{
    namespace controls = winrt::Microsoft::UI::Xaml::Controls;

    namespace native
    {
        using SwapChainPanelPtr = winrt::com_ptr<ISwapChainPanelNative>;
    }
}

namespace cisim::canvas::dx
{
    namespace d3d
    {
        using DevicePtr = winrt::com_ptr<ID3D11Device>;
        using DeviceContextPtr = winrt::com_ptr<ID3D11DeviceContext>;

        using BlendStatePtr = winrt::com_ptr<ID3D11BlendState>;
        using RasterizerStatePtr = winrt::com_ptr<ID3D11RasterizerState>;
        using DepthStencilStatePtr = winrt::com_ptr<ID3D11DepthStencilState>;

        using RenderTargetViewPtr = winrt::com_ptr<ID3D11RenderTargetView>;
        using DepthStencilViewPtr = winrt::com_ptr<ID3D11DepthStencilView>;

        using ShaderReflectionPtr = winrt::com_ptr<ID3D11ShaderReflection>;
        using InputLayoutPtr = winrt::com_ptr<ID3D11InputLayout>;

        // shaders
        using VertexShaderPtr = winrt::com_ptr<ID3D11VertexShader>;
        using HullShaderPtr = winrt::com_ptr<ID3D11HullShader>;
        using DomainShaderPtr = winrt::com_ptr<ID3D11DomainShader>;
        using GeometryShaderPtr = winrt::com_ptr<ID3D11GeometryShader>;
        using ComputeShaderPtr = winrt::com_ptr<ID3D11ComputeShader>;
        using PixelShaderPtr = winrt::com_ptr<ID3D11PixelShader>;
        using Shaders = std::tuple<
            VertexShaderPtr, HullShaderPtr, DomainShaderPtr,
            GeometryShaderPtr, PixelShaderPtr, ComputeShaderPtr>;

        // data
        using Texture2DPtr = winrt::com_ptr<ID3D11Texture2D>;
        using BufferPtr = winrt::com_ptr<ID3D11Buffer>;
        using BlobPtr = winrt::com_ptr<ID3D10Blob>;
    }

    namespace dxgi
    {
        using AdapterPtr = winrt::com_ptr<IDXGIAdapter>;
        using Adapter1Ptr = winrt::com_ptr<IDXGIAdapter1>;
        using Adapter2Ptr = winrt::com_ptr<IDXGIAdapter2>;

        using FactoryPtr = winrt::com_ptr<IDXGIFactory>;
        using Factory1Ptr = winrt::com_ptr<IDXGIFactory1>;
        using Factory2Ptr = winrt::com_ptr<IDXGIFactory2>;

        using DevicePtr = winrt::com_ptr<IDXGIDevice>;
        using Device1Ptr = winrt::com_ptr<IDXGIDevice1>;
        using Device2Ptr = winrt::com_ptr<IDXGIDevice2>;

        using SwapChainPtr = winrt::com_ptr<IDXGISwapChain>;
        using SwapChain1Ptr = winrt::com_ptr<IDXGISwapChain1>;
        using SwapChain2Ptr = winrt::com_ptr<IDXGISwapChain2>;
    }

    namespace flags
    {
        static constexpr auto creation = 0
#ifdef _DEBUG
            | D3D11_CREATE_DEVICE_DEBUG
#endif
            ;

        static constexpr auto compilation = D3DCOMPILE_ENABLE_STRICTNESS
#ifdef _DEBUG
            | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION
#endif
            ;
    }

    namespace level
    {
        static constexpr D3D_FEATURE_LEVEL required = D3D_FEATURE_LEVEL_11_1;
        static D3D_FEATURE_LEVEL actual = D3D_FEATURE_LEVEL_1_0_CORE; // default
    }

    // used by Depth and Stencil State
    enum class ComparisonFunction
    {
        Never = D3D11_COMPARISON_NEVER,
        Less = D3D11_COMPARISON_LESS,
        Equal = D3D11_COMPARISON_EQUAL,
        LessThanOrEqual = D3D11_COMPARISON_LESS_EQUAL,
        Greater = D3D11_COMPARISON_GREATER,
        NotEqual = D3D11_COMPARISON_NOT_EQUAL,
        GreaterThanOrEqual = D3D11_COMPARISON_GREATER_EQUAL,
        Always = D3D11_COMPARISON_ALWAYS
    };

    enum class Usage
    {
        Default = D3D11_USAGE_DEFAULT,
        Immutable = D3D11_USAGE_IMMUTABLE,
        Dynamic = D3D11_USAGE_DYNAMIC,
        Staging = D3D11_USAGE_STAGING
    };

    enum class Bind
    {
        None = 0,
        VertexBuffer = D3D11_BIND_VERTEX_BUFFER,
        IndexBuffer = D3D11_BIND_INDEX_BUFFER,
        ConstantBuffer = D3D11_BIND_CONSTANT_BUFFER,
        ShaderResource = D3D11_BIND_SHADER_RESOURCE,
        StreamOutput = D3D11_BIND_STREAM_OUTPUT,
        RenderTarget = D3D11_BIND_RENDER_TARGET,
        DepthStencil = D3D11_BIND_DEPTH_STENCIL,
        UnorderedAccess = D3D11_BIND_UNORDERED_ACCESS,
        Decoder = D3D11_BIND_DECODER,
        Encoder = D3D11_BIND_VIDEO_ENCODER
    };

    enum class CPUAccess
    {
        None = 0,
        Read = D3D11_CPU_ACCESS_READ,
        Write = D3D11_CPU_ACCESS_WRITE
    };

    enum class ResourceMisc
    {
        None = 0,
        GenerateMips = D3D11_RESOURCE_MISC_GENERATE_MIPS,
        Shared = D3D11_RESOURCE_MISC_SHARED,
        TextureCube = D3D11_RESOURCE_MISC_TEXTURECUBE,
        DrawIndirectArgs = D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS,
        BufferAllowRawViews = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS,
        BufferStructured = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED,
        ResourceClamp = D3D11_RESOURCE_MISC_RESOURCE_CLAMP,
        SharedKeyedMutex = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX,
        GDICompatible = D3D11_RESOURCE_MISC_GDI_COMPATIBLE,
        SharedNTHandle = D3D11_RESOURCE_MISC_SHARED_NTHANDLE,
        RestrictedContent = D3D11_RESOURCE_MISC_RESTRICTED_CONTENT,
        RestrictSharedResource = D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE,
        RestrictSharedResourceDriver = D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE_DRIVER,
        Guarded = D3D11_RESOURCE_MISC_GUARDED,
        TilePool = D3D11_RESOURCE_MISC_TILE_POOL,
        Tiled = D3D11_RESOURCE_MISC_TILED,
        HWProtected = D3D11_RESOURCE_MISC_HW_PROTECTED
    };

    enum class PipelineStage : size_t
    {
        Unknown,
        Vertex,
        Hull,
        Domain,
        Geometry,
        Pixel,
        Compute
    };

    struct ShaderSource
    {
        std::string_view source;
        std::string_view entry;
    };

    template <typename T>
    concept IsVertexShader = std::is_same_v<T, d3d::VertexShaderPtr>;

    template <typename T>
    concept IsHullShader = std::is_same_v<T, d3d::HullShaderPtr>;

    template <typename T>
    concept IsDomainShader = std::is_same_v<T, d3d::DomainShaderPtr>;

    template <typename T>
    concept IsGeometryShader = std::is_same_v<T, d3d::GeometryShaderPtr>;

    template <typename T>
    concept IsPixelShader = std::is_same_v<T, d3d::PixelShaderPtr>;

    template <typename T>
    concept IsComputeShader = std::is_same_v<T, d3d::ComputeShaderPtr>;

    template <typename T>
    concept IsShader =
        IsVertexShader<T> || IsHullShader<T> || IsDomainShader<T> ||
        IsGeometryShader<T> || IsPixelShader<T> || IsComputeShader<T>;

    template <typename T>
        requires IsShader<T>
    std::string type_string()
    {
        std::string type;

        if constexpr (IsVertexShader<T>)
            type = "vs_5_0";
        else if constexpr (IsHullShader<T>)
            type = "hs_5_0";
        else if constexpr (IsDomainShader<T>)
            type = "ds_5_0";
        else if constexpr (IsGeometryShader<T>)
            type = "gs_5_0";
        else if constexpr (IsPixelShader<T>)
            type = "ps_5_0";
        else if constexpr (IsComputeShader<T>)
            type = "cs_5_0";

        return type;
    }
}
