#include "pch.h"

namespace std
{
    atomic_int formatter<cisim::canvas::dx::parameters::InputElement>::index = 0;
}

namespace cisim::canvas::dx::parameters
{
    InputLayout::InputLayout(std::initializer_list<InputElement> elements)
        : std::vector<InputElement>(elements)
    {
    }

    std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayout::to_descriptor() const
    {
        // Read input layout description from shader info
        std::vector<D3D11_INPUT_ELEMENT_DESC> input_layout_desc;
        for (auto& element : *this)
        {
            // fill out & save input element desc
            input_layout_desc.push_back(D3D11_INPUT_ELEMENT_DESC{
                .SemanticName = element.name.c_str(),
                .SemanticIndex = element.index,
                .Format = element.format.to_descriptor(),
                .InputSlot = 0,
                .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,
                .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
                .InstanceDataStepRate = 0
                });
        }

        return input_layout_desc;
    }

    std::string InputLayout::to_input_signature() const
    {
        #pragma region shader_template
        static constexpr auto shader_template = R"###(
struct vs_input
{{
    {:";
    ""input_"}
}};

float4 main(vs_input input) : SV_Position
{{
    return float4(0, 0, 0, 0);
}}
)###";
        #pragma endregion

        return std::vformat(shader_template, std::make_format_args(*this));
    }

    InputLayout InputLayout::reflect(d3d::BlobPtr blob)
    {
        // Reflect shader info
        d3d::ShaderReflectionPtr reflection;

        winrt::check_hresult(
            D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(),
                __uuidof(reflection), reflection.put_void()));

        // Get shader info
        D3D11_SHADER_DESC shader_desc;
        reflection->GetDesc(&shader_desc);

        // Read input layout description from shader info
        InputLayout input_layout;
        for (uint32 i = 0; i < shader_desc.InputParameters; i++)
        {
            D3D11_SIGNATURE_PARAMETER_DESC param_desc;
            reflection->GetInputParameterDesc(i, &param_desc);

            // fill out & save input element desc
            input_layout.push_back(
                InputElement{
                    .name = param_desc.SemanticName,
                    .index = param_desc.SemanticIndex,
                    .format = Format{
                        .component_type = ComponentType{ param_desc.ComponentType },
                        .component_count = from_mask(param_desc.Mask)
                }
                });
        }

        return input_layout;
    }
}
