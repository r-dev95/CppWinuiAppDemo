#pragma once

#include "Services.NavigationService.g.h"

#include "Models/NavItem.h"

namespace winrt::CppWinuiAppDemo::Services::implementation
{
    /// @brief Provides navigation services.
    struct NavigationService : NavigationServiceT<NavigationService>
    {
        /// @brief Initializes a new instance of the NavigationService class.
        NavigationService();

        /// @brief Gets the current frame used for navigation.
        /// @return The current frame.
        Microsoft::UI::Xaml::Controls::Frame Frame();
        /// @brief Sets the current frame used for navigation.
        /// @param value - The frame to set.
        void Frame(Microsoft::UI::Xaml::Controls::Frame const& value);

        /// @brief Gets the type of the settings page.
        /// @return The type of the settings page.
        Windows::UI::Xaml::Interop::TypeName SettingsPageType();
        /// @brief Sets the type of the settings page.
        /// @param value - The type to set for the settings page.
        void SettingsPageType(Windows::UI::Xaml::Interop::TypeName const& value);

        /// @brief Registers a navigation item.
        /// @param item - The navigation item to register.
        void Register(Models::NavItem item);

        /// @brief Navigates to a page identified by its tag.
        /// @param tag - The tag of the page to navigate to.
        void Navigate(hstring tag);

        /// @brief Gets whether the frame can navigate back.
        /// @return The result indicating if navigation back is possible.
        bool CanGoBack();

        /// @brief Navigates back in the frame's navigation history.
        void GoBack();

        /// @brief Gets the navigation items.
        /// @return The collection of navigation items.
        Windows::Foundation::Collections::IObservableVector<Models::NavItem> GetNavItems();

        /// @brief Gets the current frame type.
        /// @return The current frame type as a NavItem.
        Models::NavItem GetCurrentFrameType();

    private:
        /// @brief The frame used for navigation.
        Microsoft::UI::Xaml::Controls::Frame m_frame{ nullptr };
        /// @brief The type of the settings page.
        Windows::UI::Xaml::Interop::TypeName m_settingsPageType;
        /// @brief The collection of navigation items.
        std::map<hstring, std::optional<Models::NavItem>> m_navItems;
    };
}

namespace winrt::CppWinuiAppDemo::Services::factory_implementation
{
    struct NavigationService : NavigationServiceT<NavigationService, implementation::NavigationService>
    {
    };
}