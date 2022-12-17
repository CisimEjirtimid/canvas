#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt::Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::canvas::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        Title(winrt::to_hstring("Canvas"));

        using namespace cisim;

        auto messages_config = ChannelConfig{}
            .withCapacity(0)
            .withSendTimeout(0_s)
            .withRecvTimeout(Time::FromSeconds(INT_MAX));

        _messages.open(messages_config);

        auto commands_config = ChannelConfig{}
            .withCapacity(0)
            .withSendTimeout(0_s)
            .withRecvTimeout(500_ms);

        _engine.start(cisim::canvas::State{ _messages }, commands_config);

        DispatcherQueue().TryEnqueue([this]()
            {
                _engine.async<cisim::canvas::GetSwapChain>().wait();

                auto [status, message] = _messages.recv();

                if (status == cisim::SyncQStatus::OK)
                {
                    cisim::match::nonexhaustive(message) (
                        [this](cisim::canvas::SwapChain message) {
                            // This must be done on UI thread, where ever was swap chain created
                            panel().as<ISwapChainPanelNative>()->SetSwapChain(message.swap_chain.get());
                        });
                }

                _engine.async(cisim::canvas::Resize{ cisim::SizeU{ panel().Height(), panel().Width() } });
            });

        _test.start();
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::action_click(IInspectable const&, RoutedEventArgs const&)
    {
        action().Content(box_value(L"Letter drawn!"));

        _engine.async(cisim::canvas::Insert{ cisim::Path{ "C:/test.txt" } });
    }

    void MainWindow::panel_size_changed([[maybe_unused]] IInspectable const& sender, SizeChangedEventArgs const& e)
    {
        auto size = e.NewSize();
        _engine.async(cisim::canvas::Resize{ cisim::SizeU{ size.Height, size.Width } });
    }
}
