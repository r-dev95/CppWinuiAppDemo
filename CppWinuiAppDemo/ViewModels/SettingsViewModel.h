#pragma once

#include "ViewModels.SettingsViewModel.g.h"

#include "Models/UserSettings.h"
#include "Services/CommonService.h"
#include "Services/UserSettingsService.h"
#include "ViewModels/BindableBase.h"

namespace winrt::CppWinuiAppDemo::ViewModels::implementation
{
    /// @brief Provides the settings view model.
    struct SettingsViewModel : SettingsViewModelT<SettingsViewModel, BindableBase>
    {
        /// @brief Initializes a new instance of the SettingsViewModel class.
        /// @param commonService - The common service instance.
        /// @param userSettingsService - The user settings service instance.
        SettingsViewModel(Services::CommonService comService, Services::UserSettingsService userSetService);

        /// @brief Gets the ComboBox for time format selection.
        /// @return The ComboBox for time format selection.
        Microsoft::UI::Xaml::Controls::ComboBox TimeFormatComboBox();
        /// @brief Sets the ComboBox for time format selection.
        /// @param value - The ComboBox to set for time format selection.
        void TimeFormatComboBox(Microsoft::UI::Xaml::Controls::ComboBox const& value);

        /// @brief Gets the selected time format.
        /// @return The selected time format.
        hstring SelectedTimeFormat();
        /// @brief Sets the selected time format.
        /// @param value - The new time format to set.
        void SelectedTimeFormat(hstring const& value);

        /// @brief Starts up the settings view model.
        void Startup();

        /// @brief Gets the command to save settings.
        /// @return The command to save settings.
        Microsoft::UI::Xaml::Input::ICommand SaveSettingsCommand();

        /// @brief Gets the command to open the file explorer in the executable directory.
        /// @return The command to open the file explorer.
        Microsoft::UI::Xaml::Input::ICommand OpenExplorerCommand();

        /// @brief Sets the selected time format when the ComboBox selection changes.
        /// @param  - The sender of the event.
        /// @param  - The selection changed event arguments.
        /// @note This method is implemented because the Two-Way binding of the combo box does not work properly.
        void OnChangedTimeFormat(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const&);

    private:
        /// @brief The common service instance.
        Services::CommonService m_comService{ nullptr };
        /// @brief The user settings service instance.
        Services::UserSettingsService m_userSetService{ nullptr };

        /// @brief The user settings instance.
        Models::UserSettings* m_userSettings;

        /// @brief The ComboBox for time format selection.
        Microsoft::UI::Xaml::Controls::ComboBox m_timeFormatComboBox{ nullptr };
        /// @brief The selected time format.
        hstring m_selectedTimeFormat;

        /// @brief The command to save settings.
        Microsoft::UI::Xaml::Input::ICommand m_saveSettingsCommand{ nullptr };
        /// @brief The command to open the file explorer in the executable directory.
        Microsoft::UI::Xaml::Input::ICommand m_openExplorerCommand{ nullptr };
    };
}

namespace winrt::CppWinuiAppDemo::ViewModels::factory_implementation
{
    struct SettingsViewModel : SettingsViewModelT<SettingsViewModel, implementation::SettingsViewModel>
    {
    };
}
