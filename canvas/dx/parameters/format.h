#pragma once

namespace cisim::canvas::dx::parameters
{
    enum class ComponentType
    {
        Unknown = D3D_REGISTER_COMPONENT_UNKNOWN,
        Uint32 = D3D_REGISTER_COMPONENT_UINT32,
        Sint32 = D3D_REGISTER_COMPONENT_SINT32,
        Float32 = D3D_REGISTER_COMPONENT_FLOAT32,
    };

    enum class ComponentCount
    {
        Unknown = 0b0000,
        One = 0b0001,
        Two = 0b0010,
        Three = 0b0100,
        Four = 0b1000
    };

    ComponentCount from_mask(uchar mask);

    struct Format
    {
        ComponentType component_type;
        ComponentCount component_count;

        DXGI_FORMAT to_descriptor() const
        {
            static std::map<ComponentCount, uchar> base_format{
                { ComponentCount::Unknown, DXGI_FORMAT_UNKNOWN },
                { ComponentCount::One, DXGI_FORMAT_R32_FLOAT },
                { ComponentCount::Two, DXGI_FORMAT_R32G32_FLOAT },
                { ComponentCount::Three, DXGI_FORMAT_R32G32B32_FLOAT },
                { ComponentCount::Four, DXGI_FORMAT_R32G32B32A32_FLOAT }
            };

            static std::map<ComponentType, uchar> component_offset{
                { ComponentType::Unknown, 0 },
                { ComponentType::Float32, 0 },
                { ComponentType::Uint32, 1 },
                { ComponentType::Sint32, 2 }
            };

            return DXGI_FORMAT(base_format[component_count] + component_offset[component_type]);
        }
    };
}

namespace std
{
    using namespace cisim::canvas::dx::parameters;

    template <>
    struct formatter<Format> : formatter<char>
    {
        // rely on the standard implementation of `parse` function, so don't reimplement it

        auto format(const Format& fmt, format_context& ctx) const
        {
            static map<ComponentType, string> input_type{
                { ComponentType::Unknown, "" },
                { ComponentType::Float32, "float" },
                { ComponentType::Uint32, "uint" },
                { ComponentType::Sint32, "int" }
            };

            static map<ComponentCount, string> input_count{
                { ComponentCount::Unknown, "" },
                { ComponentCount::One, "" },
                { ComponentCount::Two, "2" },
                { ComponentCount::Three, "3" },
                { ComponentCount::Four, "4" }
            };

            return format_to(ctx.out(), "{0}{1}", input_type[fmt.component_type], input_count[fmt.component_count]);
        }
    };
}
