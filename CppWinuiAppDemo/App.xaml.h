#pragma once

#include "App.xaml.g.h"

namespace winrt::CppWinuiAppDemo::implementation
{
    /// @brief Provides the main application class.
    struct App : AppT<App>
    {
        /// @brief Initializes a new instance of the App class.
        App();

        /// @brief Initialize and activate the MainWindow.
        /// @param  - The launch activated event arguments.
        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

        /// @brief The event handler for when the application window is closed.
        /// @param  - The sender of the event.
        /// @param  - The window event arguments.
        void OnClosed(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::WindowEventArgs const&);
    };
}
