#include "pch.h"

namespace cisim::canvas::dx::shader
{
    ManagerConfig::ManagerConfig()
        : file(*this, std::string{ "shaders" })
        , shader_entrypoint(*this, std::string{ "main" })
    {}

    ManagerConfig::ManagerConfig(const ManagerConfig& other)
        : file(*this, other.file())
        , shader_entrypoint(*this, other.shader_entrypoint())
    {}

    Manager::Manager(ManagerConfig&& config)
        : _config(std::move(config))
    {}
}
