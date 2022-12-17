#pragma once

namespace cisim::canvas::dx::parameters
{
    namespace impl
    {
        enum class PrimitiveTopology
        {
            Undefined = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED,
            Pointlist = D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
            Linelist = D3D_PRIMITIVE_TOPOLOGY_LINELIST,
            Linestrip = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
            Trianglelist = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
            Trianglestrip = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,

            // Used when Geometry Shader is present/active
            Linelist_Adjacency = D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
            Linestrip_Adjacency = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
            Trianglelist_Adjacency = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
            Trianglestrip_Adjacency = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,

            // Used when Tesselation (Hull, Domain) Shader is present/active
            // Number in the name of the topology represents number of control points
            ControlPoint_PatchList_01 = D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_02 = D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_03 = D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_04 = D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_05 = D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_06 = D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_07 = D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_08 = D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_09 = D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_10 = D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_11 = D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_12 = D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_13 = D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_14 = D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_15 = D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_16 = D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_17 = D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_18 = D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_19 = D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_20 = D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_21 = D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_22 = D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_23 = D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_24 = D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_25 = D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_26 = D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_27 = D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_28 = D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_29 = D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_30 = D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_31 = D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST,
            ControlPoint_PatchList_32 = D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST
        };
    }

    using PrimitiveTopology = EnumWrapper<impl::PrimitiveTopology, D3D11_PRIMITIVE_TOPOLOGY>;
}
