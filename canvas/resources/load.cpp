#include "pch.h"

namespace cisim::canvas::resources
{
    namespace __detail
    {
        namespace res = winrt::Microsoft::Windows::ApplicationModel::Resources;

        class Loader
        {
            res::ResourceManager _manager;
        public:
            Loader()
                : _manager(winrt::to_hstring("resources.pri"))
            {
            }

            std::string load(const std::string& resource_file, const std::string& resource_name)
            {
                auto full_name = std::format("{}/{}", resource_file, resource_name);

                auto hstring_value = _manager.MainResourceMap().GetValue(winrt::to_hstring(full_name)).ValueAsString();
                return winrt::to_string(hstring_value);
            }
        };
    }

    std::string load(const std::string& file, const std::string& name)
    {
        thread_local __detail::Loader loader;

        return loader.load(file, name);
    }
}
