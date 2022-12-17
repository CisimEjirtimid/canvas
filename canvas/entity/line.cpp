#include "pch.h"

namespace cisim::canvas::entity
{
    Line::Line()
    {
        using namespace dx;
        auto& device = DeviceState::instance();
        auto& state = _draw_state;

        state.render_state = device.default_render_state();

        {
            using namespace parameters;

            state.render_state
                .set(parameters::PrimitiveTopology::Enum::Linestrip)
                .set(InputLayout{
                    InputElement{
                        .name = "POSITION",
                        .index = 0,
                        .format = Format{
                            .component_type = ComponentType::Float32,
                            .component_count = ComponentCount::Three
                        }
                    },
                    InputElement{
                        .name = "COLOR",
                        .index = 0,
                        .format = Format{
                            .component_type = ComponentType::Float32,
                            .component_count = ComponentCount::Four
                        }
                    }
                });
        }

        shader::Manager manager;

        state.shader<d3d::VertexShaderPtr>() = manager.get<d3d::VertexShaderPtr>("line_vs");
        state.shader<d3d::PixelShaderPtr>() = manager.get<d3d::PixelShaderPtr>("line_ps");

        state.constants["transform"] = Constant{
            .stage = PipelineStage::Vertex,
            .slot = 0,
            .buffer = device.create_buffer<float>(16)
        };

        state.constants["alpha"] = Constant{
            .stage = PipelineStage::Pixel,
            .slot = 1,
            .buffer = device.create_buffer<float>(1)
        };

        auto transform = H4F::Eye().data();
        device.fill_buffer(state.constants["transform"].buffer,
            transform, 16);

        float alpha = 1.0f;
        device.fill_buffer(state.constants["alpha"].buffer,
            &alpha, 1);
    }

    void Line::push_back(const float3& point)
    {
        _points.push_back(point);
    }

    void Line::push_back(float3&& point)
    {
        _points.push_back(std::move(point));
    }

    void Line::insert(std::initializer_list<float3> points)
    {
        _points.insert(_points.end(), points);
    }

    void Line::compile()
    {
        using namespace dx;
        auto& device = DeviceState::instance();
        auto& state = _draw_state;

        struct VertexInput
        {
            float3 position;
            float4 color;
        };

        auto size = uint(_points.size());
        state.vertices = Vertices{
            .stage = PipelineStage::Vertex,
            .size = size,
            .stride = sizeof(VertexInput),
            .offset = 0,
            .buffer = device.create_buffer<VertexInput>(
            uint(_points.size()), Bind::VertexBuffer)
        };

        std::vector<VertexInput> input;

        for (auto& point : _points)
            input.push_back(VertexInput{ point, _color });

        device.fill_buffer(state.vertices.buffer, input);
    }

    dx::DrawState Line::get_draw_state()
    {
        return _draw_state;
    }
}
