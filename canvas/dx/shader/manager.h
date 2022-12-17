#pragma once

namespace cisim::canvas::dx::shader
{
    struct ManagerConfig
    {
        template<typename T>
        using Builder = ConfigBuilder<ManagerConfig, T>;

        Builder<std::string> file;
        Builder<std::string> shader_entrypoint;

        ManagerConfig();
        ManagerConfig(const ManagerConfig& other);
    };

    class Manager
    {
        ManagerConfig _config;

    public:
        Manager(ManagerConfig&& config = ManagerConfig{});

        template <typename T>
            requires IsShader<T>
        T get(const std::string& name)
        {
            auto& cache = shader::Cache::instance();
            auto& device = DeviceState::instance();

            if (auto existing_shader = cache.get<T>(name))
            {
                return existing_shader;
            }
            else
            {
                auto file = _config.file();
                auto entrypoint = _config.shader_entrypoint();

                auto source = resources::load(file, name);
                auto blob = device.compile_shader<T>({ source, entrypoint }, shader::Includes{}, shader::Macros{});
                auto new_shader = device.create_shader<T>(blob);

                return cache.insert<T>(name, new_shader);
            }
        }
    };
}
