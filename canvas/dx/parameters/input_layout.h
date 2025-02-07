#pragma once

namespace cisim::canvas::dx::parameters
{
    struct InputElement
    {
        std::string name;
        uint index;
        Format format;
    };

    struct InputLayout : public std::vector<InputElement>
    {
        InputLayout() = default;
        InputLayout(std::initializer_list<InputElement> elements);

        std::vector<D3D11_INPUT_ELEMENT_DESC> to_descriptor() const;

        std::string to_input_signature() const;

        static InputLayout reflect(d3d::BlobPtr blob);
    };
}

namespace std
{
    // this formatter is used for combined formatting (outer & inner), with two different format strings
    // outer part is passed through between "", and inner part is passed regularly
    struct combined_formatter
    {
        std::string outer_format_string = "";
        std::string inner_format_string = "";

        auto parse(format_parse_context& ctx)
        {
            std::string args = "";

            auto it = ctx.begin();

            if (*it == '"') // begin reading outer_format_string
            {
                it++; // remove first "
                while (*it != '"')
                {
                    if (*it == '\\' && *(it + 1) == '"')
                    {
                        outer_format_string += '"';
                        it += 2;
                    }
                    else
                    {
                        outer_format_string += *it++;
                    }
                }
                it++; // remove second "

                // read the inner_format_string
                while (it != ctx.end() && *it != '}')
                    inner_format_string += *it++;
            }

            return it;
        }
    };

    template <typename T>
    struct formatter<vector<T>> : combined_formatter
    {
        auto format(const std::vector<T>& vec, format_context& ctx) const
        {
            auto format_string = std::format("{{0:{0}}}{{1}}", inner_format_string);
            auto& delimiter = outer_format_string;

            std::string result;

            for (auto& val : vec)
                result += std::vformat(format_string, std::make_format_args(val, delimiter));

            return std::format_to(ctx.out(), "{}", result);
        }
    };

    template <>
    struct formatter<InputElement> : combined_formatter
    {
        static atomic_int index;

        auto format(const InputElement& element, format_context& ctx) const
        {
            auto format_string = std::format("{{0}} {0}{1} : {{1}}{{2}}", outer_format_string, index++);

            // using std::vformat_to that doesn't enforce consteval format strings
            return std::vformat_to(ctx.out(), format_string,
                std::make_format_args(element.format, element.name, element.index));
        }
    };

    template <>
    struct formatter<InputLayout> : formatter<std::vector<InputElement>>
    {
    };
}
