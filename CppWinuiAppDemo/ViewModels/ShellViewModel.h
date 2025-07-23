#pragma once

#include "ViewModels.ShellViewModel.g.h"

#include "Services/CommonService.h"
#include "Services/NavigationService.h"
#include "Services/UserSettingsService.h"
#include "ViewModels/BindableBase.h"

namespace winrt::CppWinuiAppDemo::ViewModels::implementation
{
    /// @brief Provides the shell view model.
    struct ShellViewModel : ShellViewModelT<ShellViewModel, BindableBase>
    {
        /// @brief Initializes a new instance of the ShellViewModel class.
        /// @param comService - The common service instance.
        /// @param userSetService - The user settings service instance.
        /// @param navService - The navigation service instance.
        ShellViewModel::ShellViewModel(Services::CommonService comService, Services::UserSettingsService userSetService, Services::NavigationService navService);

        /// @brief Gets the navigation service.
        /// @return The navigation service instance.
        Services::NavigationService NavService();

        /// @brief Gets whether the application is in dark theme mode.
        /// @return The boolean indicating whether the dark theme is enabled.
        bool IsDarkTheme();
        /// @brief Sets whether the application is in dark theme mode.
        /// @param value - The boolean value to set for dark theme.
        void IsDarkTheme(bool value);

        /// @brief Gets the current clock text.
        /// @return The current clock text.
        hstring ClockText();
        /// @brief Sets the current clock text.
        /// @param value - The new clock text to set.
        void ClockText(hstring value);

        /// @brief Gets the collection of navigation items.
        /// @return The observable vector of navigation items.
        Windows::Foundation::Collections::IObservableVector<Models::NavItem> NavItems();
        /// @brief Sets the collection of navigation items.
        /// @param value - The observable vector of navigation items to set.
        void NavItems(Windows::Foundation::Collections::IObservableVector<Models::NavItem> const& value);

        /// @brief Gets the currently selected navigation item.
        /// @return The currently selected navigation item.
        Models::NavItem SelectedNavItem();
        /// @brief Sets the currently selected navigation item.
        /// @param value - The navigation item to select.
        void SelectedNavItem(Models::NavItem const& value);

        /// @brief Starts up the shell view model.
        void Startup();

        /// @brief Stops the timer that updates the clock.
        void StopTimer();

        /// @brief Navigates to the specified page when an item is invoked in the navigation view.
        /// @param _ - The navigation view sender.
        /// @param args - The navigation view item invoked event arguments.
        void ItemInvoked(Microsoft::UI::Xaml::Controls::NavigationView const&, Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args);

        /// @brief Navigates back when the back button is requested in the navigation view.
        /// @param sender - The navigation view sender.
        /// @param  - The navigation view back requested event arguments.
        void BackRequested(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Microsoft::UI::Xaml::Controls::NavigationViewBackRequestedEventArgs const&);

        /// @brief Chages the theme of the application when the command is loaded.
        void ChangeThemeLoaded();
        /// @brief Gets the command to change the theme of the application.
        /// @return The command to change the theme.
        Microsoft::UI::Xaml::Input::ICommand ChangeThemeCommand();

    private:
        /// @brief The common service instance.
        Services::CommonService m_comService{ nullptr };
        /// @brief The user settings service instance.
        Services::UserSettingsService m_userSetService{ nullptr };
        /// @brief The navigation service instance.
        Services::NavigationService m_navService{ nullptr };

        /// @brief The user settings instance.
        Models::UserSettings* m_userSettings;
        /// @brief The timer for updating the clock.
        Microsoft::UI::Xaml::DispatcherTimer m_timer;

        /// @brief The flag indicating whether the application is in dark theme mode.
        bool m_isDarkTheme{ false };
        /// @brief The command to change the theme of the application.
        Microsoft::UI::Xaml::Input::ICommand m_changeThemeCommand{ nullptr };
        /// @brief The current clock text.
        hstring m_clockText{ L"" };
        /// @brief The collection of navigation items.
        Windows::Foundation::Collections::IObservableVector<Models::NavItem> m_navItems;
        /// @brief The currently selected navigation item.
        std::optional<Models::NavItem> m_selectedNavItem;

        /// @brief Updates the clock text.
        /// @param  - The sender of the event.
        /// @param  - The event arguments for the clock update.
        void UpdateClock(Windows::Foundation::IInspectable const&, Windows::Foundation::IInspectable const&);
    };
}

namespace winrt::CppWinuiAppDemo::ViewModels::factory_implementation
{
    struct ShellViewModel : ShellViewModelT<ShellViewModel, implementation::ShellViewModel>
    {
    };
}
