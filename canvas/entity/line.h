#pragma once

namespace cisim::canvas::entity
{
    class Line : public Base
    {
        std::vector<float3> _points;
        float4 _color = float4{ 0.5, 0.5, 0.5, 1.0 };

        dx::DrawState _draw_state;
    public:
        Line();

        void push_back(const float3& point);
        void push_back(float3&& point);
        void insert(std::initializer_list<float3> points);

        void compile();

        dx::DrawState get_draw_state() override;
    };
}
