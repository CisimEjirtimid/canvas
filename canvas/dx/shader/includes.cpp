#include "pch.h"

namespace cisim::canvas::dx::shader
{
    HRESULT __stdcall Includes::Open([[maybe_unused]] D3D_INCLUDE_TYPE IncludeType_unused, LPCSTR pFileName, [[maybe_unused]] LPCVOID pParentData_unused, LPCVOID* ppData, UINT* pBytes)
    {
        std::string key{ pFileName };

        if (this->contains(key))
        {
            auto& value = this->at(key);

            *pBytes = UINT(value.size());

            auto* data = new uint8_t[*pBytes];
            std::copy(value.begin(), value.end(), data);
            *ppData = data;

            return S_OK;
        }

        return E_FAIL;
    }

    HRESULT __stdcall Includes::Close(LPCVOID pData)
    {
        delete[] pData;
        return S_OK;
    }
}
