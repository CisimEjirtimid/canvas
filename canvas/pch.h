#pragma once
#include <unknwn.h>

// Undefine GetCurrentTime macro to prevent
// conflict with Storyboard::GetCurrentTime
#undef GetCurrentTime

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <wil/cppwinrt_helpers.h>

#include <microsoft.ui.xaml.media.dxinterop.h>

#include <winrt/Microsoft.Windows.ApplicationModel.Resources.h>
//#include <winrt/Windows.ApplicationModel.Resources.h>
//#include <winrt/Windows.ApplicationModel.Resources.Core.h>

// D3D
#include <dxgi1_6.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>

// STL
#include <string_view>
#include <format>
#include <set>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <filesystem>

#define WIN32_LEAN_AND_MEAN

// base
#include <tools/config_builder.h>
#include <tools/enum_wrapper.h>
#include <tools/h4.h>
#include <tools/range.h>
#include <tools/singleton.h>
#include <tools/size.h>
#include <tools/static_vec.h>
#include <tools/time.h>
#include <tools/thread.h>
#include <tools/types.h>
#include <tools/type_tuple.h>
#include <tools/variant_match.h>

// canvas/resources
#include <canvas/resources/load.h>

// canvas/dx
#include <canvas/dx/defines.h>
#include <canvas/dx/parameters/blend_state.h>
#include <canvas/dx/parameters/depth_state.h>
#include <canvas/dx/parameters/stencil_state.h>
#include <canvas/dx/parameters/depth_stencil_state.h>
#include <canvas/dx/parameters/format.h>
#include <canvas/dx/parameters/input_layout.h>
#include <canvas/dx/parameters/primitive_topology.h>
#include <canvas/dx/parameters/rasterizer_state.h>
#include <canvas/dx/parameters/scissor.h>
#include <canvas/dx/parameters/viewport.h>
#include <canvas/dx/shader/cache.h>
#include <canvas/dx/shader/includes.h>
#include <canvas/dx/shader/macros.h>
#include <canvas/dx/render_state.h>
#include <canvas/dx/draw_state.h>
#include <canvas/dx/device_state.h>
#include <canvas/dx/shader/manager.h>
#include <canvas/dx/context.h>

// canvas/entity
#include <canvas/entity/base.h>
#include <canvas/entity/line.h>

// canvas
#include <canvas/engine.h>
