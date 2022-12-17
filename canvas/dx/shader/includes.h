#pragma once

namespace cisim::canvas::dx::shader
{
    class Includes
        : public ID3DInclude
        , public std::map<std::string_view, std::string_view>
    {
    public:
        // Inherited via ID3DInclude
        virtual HRESULT __stdcall Open([[maybe_unused]] D3D_INCLUDE_TYPE IncludeType_unused, LPCSTR pFileName, [[maybe_unused]] LPCVOID pParentData_unused, LPCVOID* ppData, UINT* pBytes) override;
        virtual HRESULT __stdcall Close(LPCVOID pData) override;
    };
}
