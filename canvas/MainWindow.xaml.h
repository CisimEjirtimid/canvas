#pragma once

#include "MainWindow.g.h"

namespace winrt::canvas::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        cisim::Channel<cisim::canvas::Message> _messages;
        cisim::canvas::Engine _engine;

        cisim::test::ThreadTest _test;

        MainWindow();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void action_click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void panel_size_changed([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e);
    };
}

namespace winrt::canvas::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
