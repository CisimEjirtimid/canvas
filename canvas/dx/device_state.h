#pragma once

namespace winrt
{
    bool succeeded(const hresult& result);
    bool failed(const hresult& result);
}

namespace cisim::canvas::dx
{
    class DeviceState : public Singleton<DeviceState>
    {
        d3d::Texture2DPtr _framebuffer = nullptr;
        d3d::RenderTargetViewPtr _render_target_view = nullptr;
        void init_render_target();

        #pragma region CreateShader
        template <typename T>
        using CreateShader = HRESULT(ID3D11Device::*)(const void*, SIZE_T, ID3D11ClassLinkage*, T**);

        template <typename T, typename UnderlyingT>
        CreateShader<UnderlyingT> shader_creator()
        {
            if constexpr (IsVertexShader<T>)
                return &ID3D11Device::CreateVertexShader;
            else if constexpr (IsHullShader<T>)
                return &ID3D11Device::CreateHullShader;
            else if constexpr (IsDomainShader<T>)
                return &ID3D11Device::CreateDomainShader;
            else if constexpr (IsGeometryShader<T>)
                return &ID3D11Device::CreateGeometryShader; // Geom with stream output?
            else if constexpr (IsPixelShader<T>)
                return &ID3D11Device::CreatePixelShader;
            else if constexpr (IsComputeShader<T>)
                return &ID3D11Device::CreateComputeShader;
            else
                throw std::runtime_error{ "Wrong Shader Type Provided!" };
        }
        #pragma endregion

    public:
        DeviceState(token) {};

        dxgi::SwapChain1Ptr swap_chain = nullptr;
        d3d::DevicePtr device = nullptr;
        d3d::DeviceContextPtr context = nullptr;

        void init(HWND hwnd = nullptr);

        template <typename T>
        SizeT<T> framebuffer_size() const // framebuffer_size
        {
            D3D11_TEXTURE2D_DESC framebuffer_descriptor;
            _framebuffer->GetDesc(&framebuffer_descriptor);

            return SizeT<T>{ framebuffer_descriptor.Height, framebuffer_descriptor.Width };
        }

        void framebuffer_resize(const SizeU& size); // framebuffer_resize

        RenderState default_render_state() const;

        template <typename T>
        d3d::BufferPtr create_buffer(
            uint size,
            Bind bind = Bind::ConstantBuffer,
            Usage usage = Usage::Default,
            CPUAccess access = CPUAccess::None,
            ResourceMisc misc = ResourceMisc::None)
        {
            uint buffer_size = sizeof(T) * size;

            // constant buffers must be aligned to 16 bytes
            if (bind == Bind::ConstantBuffer)
            {
                auto length = sizeof(T) * size;
                auto mod = length % 16;
                buffer_size = uint(length - mod + 16);
            }

            D3D11_BUFFER_DESC bd =
            {
                .ByteWidth = buffer_size,
                .Usage =  D3D11_USAGE(usage),
                .BindFlags = uint(bind),
                .CPUAccessFlags = uint(access),
                .MiscFlags = uint(misc),
                .StructureByteStride = 0
            };

            d3d::BufferPtr buffer;
            winrt::check_hresult(device->CreateBuffer(&bd, nullptr, buffer.put()));

            return buffer;
        }

        template <typename T>
        void fill_buffer(
            d3d::BufferPtr buffer,
            T* data, uint size)
        {
            if (!buffer)
                throw std::runtime_error{ "Invalid buffer pointer!" };

            D3D11_BUFFER_DESC desc;
            buffer->GetDesc(&desc);

            if (desc.ByteWidth < size * sizeof(T))
                throw std::length_error{ "Provided data is bigger than the buffer!" };

            if (Bind(desc.BindFlags) == Bind::ConstantBuffer)
            {
                context->UpdateSubresource(buffer.get(), 0, nullptr, data, 0, 0);
            }
            else
            {
                D3D11_BOX subBox;
                subBox.left = 0;
                subBox.right = uint(sizeof(T) * size);
                subBox.front = 0;
                subBox.back = 1;
                subBox.top = 0;
                subBox.bottom = 1;

                context->UpdateSubresource(buffer.get(), 0, &subBox, data, 0, 0);
            }
        }

        template <typename T>
        void fill_buffer(
            d3d::BufferPtr buffer,
            const std::vector<T>& data)
        {
            fill_buffer(buffer, data.data(), uint(data.size()));
        }

        template <typename T>
            requires IsShader<T>
        d3d::BlobPtr compile_shader(
            const ShaderSource& source,
            shader::Includes&& includes = shader::Includes{},
            const shader::Macros& macros = shader::Macros{})
        {
            d3d::BlobPtr shader;
            d3d::BlobPtr errors;

            auto type = type_string<T>();

            auto result = winrt::hresult{
                    D3DCompile(source.source.data(), source.source.length(), nullptr,
                        macros.raw().data(), &includes, source.entry.data(),
                        type.data(), flags::compilation, 0, shader.put(), errors.put())
                };

            if (winrt::failed(result))
            {
                winrt::hresult_error error{ result };

                auto message = std::format(
                    "HRESULT Error {:#x}: {}\nShader {} compilation failed with error: {}",
                    uint32_t(error.code()), winrt::to_string(error.message()),
                    type, reinterpret_cast<char*>(errors->GetBufferPointer()));

                throw std::runtime_error{ message };
            }

            return shader;
        }

        template <typename T>
            requires IsShader<T>
        T create_shader(d3d::BlobPtr blob)
        {
            T shader;

            auto create = shader_creator<T, T::template type>();

            winrt::check_hresult(
                (device.get()->*create)(
                    blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader.put()));

            return shader;
        }

        void clear(std::array<float, 4> clear_color);

        void present();
    };
}
