#include "pch.h"
#include "device_state.h"

namespace winrt
{
    bool succeeded(const hresult& result)
    {
        return result >= 0;
    }

    bool failed(const hresult& result)
    {
        return !succeeded(result);
    }
}

namespace cisim::canvas::dx
{
    void DeviceState::init_render_target()
    {
        winrt::check_hresult(swap_chain->GetBuffer(0, __uuidof(_framebuffer), _framebuffer.put_void()));
        winrt::check_hresult(device->CreateRenderTargetView(_framebuffer.get(), nullptr, _render_target_view.put()));

        ID3D11RenderTargetView* rtvs[] = { _render_target_view.get() };
        // TODO: missing DepthStencilView here
        context->OMSetRenderTargets(1, rtvs, nullptr);
    }

    void DeviceState::init(HWND hwnd)
    {
        // create a struct to hold information about the swap chain
        DXGI_SWAP_CHAIN_DESC1 scd{
            .Width = 640,
            .Height = 480,
            .Format = DXGI_FORMAT_B8G8R8A8_UNORM,
            .Stereo = false,
            .SampleDesc{
                .Count = 1,
                .Quality = 0
            },
            .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
            .BufferCount = 2,
            .Scaling = DXGI_SCALING_STRETCH,
            .SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
            .AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED,
            .Flags = 0
        };

        // create a device (and, in turn, create a immediate context)
        winrt::check_hresult(D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            flags::creation,
            &level::required,
            1,
            D3D11_SDK_VERSION,
            device.put(),
            &level::actual,
            context.put()
        ));

        if (level::actual < level::required)
            throw std::runtime_error{ "Insufficient Feature Level Detected! Feature Level 11_1 needed." };

        auto dxgi_device = device.as<IDXGIDevice>();
        dxgi::AdapterPtr adapter; dxgi_device->GetAdapter(adapter.put());
        dxgi::Factory2Ptr factory; adapter->GetParent(__uuidof(factory), factory.put_void());

        if (hwnd)
        {
            DXGI_SWAP_CHAIN_FULLSCREEN_DESC scfd{
                .RefreshRate{
                    .Numerator = 0,
                    .Denominator = 1
                },
                .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
                .Scaling = DXGI_MODE_SCALING_UNSPECIFIED,
                .Windowed = true
            };

            winrt::check_hresult(factory->CreateSwapChainForHwnd(
                device.get(),
                hwnd,
                &scd,
                &scfd,
                nullptr,
                swap_chain.put()
            ));
        }
        else
        {
            winrt::check_hresult(factory->CreateSwapChainForComposition(
                device.get(),
                &scd,
                nullptr,
                swap_chain.put()
            ));
        }

        init_render_target();
    }

    void DeviceState::framebuffer_resize(const SizeU& size)
    {
        if (!size)
            return;

        // De-init render target
        {
            context->OMSetRenderTargets(0, nullptr, nullptr);

            // Release all outstanding references to the swap chain's buffers.
            _framebuffer = nullptr;
            _render_target_view = nullptr;
        }

        // Resize buffers in swap chain
        winrt::check_hresult(swap_chain->ResizeBuffers(2, size.width, size.height, DXGI_FORMAT_UNKNOWN, 0));

        // Re-init render target
        init_render_target();
    }

    void DeviceState::clear(std::array<float, 4> clear_color)
    {
        ID3D11RenderTargetView* rtvs[] = { _render_target_view.get() };
        // TODO: missing DepthStencilView here
        context->OMSetRenderTargets(1, rtvs, nullptr);

        context->ClearRenderTargetView(_render_target_view.get(), clear_color.data());
    }

    void DeviceState::present()
    {
        DXGI_PRESENT_PARAMETERS parameters{
            .DirtyRectsCount = 0,
            .pDirtyRects = nullptr,
            .pScrollRect = nullptr,
            .pScrollOffset = nullptr
        };

        winrt::check_hresult(swap_chain->Present1(1, 0, &parameters));
    }

    RenderState DeviceState::default_render_state() const
    {
        using namespace parameters;

        // example how Render State would be defined
        RenderState render_state;

        render_state
            .set(BlendState{
                .enabled = true,
                .color_blend{
                    .source = BlendingFactor::SourceAlpha,
                    .destination = BlendingFactor::InverseSourceAlpha,
                    .operation = BlendingOperation::Add
                },
                .alpha_blend{
                    .source = BlendingFactor::SourceAlpha,
                    .destination = BlendingFactor::DestinationAlpha,
                    .operation = BlendingOperation::Add
                },
                .write_mask = ColorWriteEnable::All
            })
            .set(RasterizerState{
                .fill = FillMode::Solid,    //
                .cull = CullMode::Back,     // affected by graphics debug option
                .front_counter_clockwise = false,
                .multisample = true,
                .antialiased_line = true,
                .scissor = true
            })
            .set(DepthStencilState{
                .depth = DepthState{
                    .enabled = true,
                    .write_mask = DepthWriteMask::All,
                    .function = ComparisonFunction::Less
                },
                .stencil = StencilState{
                    .enabled = false,
                    .read_mask = 0xff,
                    .write_mask = 0xff,
                    .front = StencilFace{
                        .stencil_fail_op = StencilOperation::Keep,
                        .stencil_pass_depth_fail_op = StencilOperation::IncrementWrap,
                        .stencil_pass_depth_pass_op = StencilOperation::Keep,
                        .function = ComparisonFunction::Always
                    },
                    .back = StencilFace{
                        .stencil_fail_op = StencilOperation::Keep,
                        .stencil_pass_depth_fail_op = StencilOperation::DecrementWrap,
                        .stencil_pass_depth_pass_op = StencilOperation::Keep,
                        .function = ComparisonFunction::Always
                    }
                }
            })
            .set(Viewport{
                .top_left = float2{ 0.f, 0.f },
                .bottom_right = float2{ 1.f, 1.f },
                .depth = Rangef{ 0.f, 1.f }
            })
            .set(Scissor{
                .top_left = float2{ 0.f, 0.f },
                .bottom_right = float2{ 1.f, 1.f }
            });

        return render_state;
    }
}
