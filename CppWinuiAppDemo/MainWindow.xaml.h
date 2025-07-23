#pragma once

#include "MainWindow.g.h"

namespace winrt::CppWinuiAppDemo::implementation
{
    /// @brief Provides the main application window.
    struct MainWindow : MainWindowT<MainWindow>
    {
        /// @brief Initializes a new instance of the MainWindow class.
        MainWindow();
    };
}

namespace winrt::CppWinuiAppDemo::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
