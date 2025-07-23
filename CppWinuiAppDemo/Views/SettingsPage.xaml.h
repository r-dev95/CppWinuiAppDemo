#pragma once

#include "Views.SettingsPage.g.h"

#include "ViewModels/SettingsViewModel.h"

namespace winrt::CppWinuiAppDemo::Views::implementation
{
    /// @brief Provides the settings page view.
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
        /// @brief Initializes a new instance of the SettingsPage class.
        SettingsPage();

        /// @brief Gets the view model.
        /// @return The settings view model.
        ViewModels::SettingsViewModel ViewModel();

        /// @brief Initializes the settings page view model.
        /// @param  - The sender of the event.
        /// @param  - The routed event arguments.
        void OnLoaded(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);

    private:
        /// @brief The settings view model instance.
        ViewModels::SettingsViewModel m_viewModel{ nullptr };
    };
}

namespace winrt::CppWinuiAppDemo::Views::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
