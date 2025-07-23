#pragma once

#include "Views.ShellPage.g.h"

#include "ViewModels/ShellViewModel.h"

namespace winrt::CppWinuiAppDemo::Views::implementation
{
    /// @brief Provides the shell page view.
    struct ShellPage : ShellPageT<ShellPage>
    {
        /// @brief Initializes a new instance of the ShellPage class.
        /// @param vm - The shell view model instance.
        ShellPage(ViewModels::ShellViewModel vm);

        /// @brief Gets the view model.
        /// @return The shell view model.
        ViewModels::ShellViewModel ViewModel();

        /// @brief Startup method to initialize the shell page.
        void ShellPage::Startup();

    private:
        /// @brief The shell view model instance.
        ViewModels::ShellViewModel m_viewModel{ nullptr };
    };
}

namespace winrt::CppWinuiAppDemo::Views::factory_implementation
{
    struct ShellPage : ShellPageT<ShellPage, implementation::ShellPage>
    {
    };
}
