#pragma once

#include "Models.NavItem.g.h"

namespace winrt::CppWinuiAppDemo::Models::implementation
{
    /// @brief Provides a navigation item model.
    struct NavItem : NavItemT<NavItem>
    {
        /// @brief Initializes a new instance of the NavItem class.
        /// @param name - The name of the navigation item.
        /// @param tag - The tag associated with the navigation item.
        /// @param icon - The icon representing the navigation item.
        /// @param pageType - The type of the page associated with the navigation item.
        NavItem(hstring const& name, hstring const& tag, Microsoft::UI::Xaml::Controls::Symbol const& icon, Windows::UI::Xaml::Interop::TypeName const& pageType);

        /// @brief Gets the name of the navigation item.
        /// @return The name of the navigation item.
        hstring Name();
        /// @brief Sets the name of the navigation item.
        /// @param value - The name to set for the navigation item.
        void Name(hstring const& value);

        /// @brief Gets the tag associated with the navigation item.
        /// @return The tag of the navigation item.
        hstring Tag();
        /// @brief Sets the tag associated with the navigation item.
        /// @param value - The tag to set for the navigation item.
        void Tag(hstring const& value);

        /// @brief Gets the icon representing the navigation item.
        /// @return The icon of the navigation item.
        Microsoft::UI::Xaml::Controls::Symbol Icon();
        /// @brief Sets the icon representing the navigation item.
        /// @param value - The icon to set for the navigation item.
        void Icon(Microsoft::UI::Xaml::Controls::Symbol const& value);

        /// @brief Gets the type of the page associated with the navigation item.
        /// @return The type of the page associated with the navigation item.
        Windows::UI::Xaml::Interop::TypeName PageType();
        /// @brief Sets the type of the page associated with the navigation item.
        /// @param value - The type to set for the page associated with the navigation item.
        void PageType(Windows::UI::Xaml::Interop::TypeName const& value);

    private:
        /// @brief The name of the navigation item.
        hstring m_name;
        /// @brief The tag associated with the navigation item.
        hstring m_tag;
        /// @brief The icon representing the navigation item.
        Microsoft::UI::Xaml::Controls::Symbol m_icon;
        /// @brief The type of the page associated with the navigation item.
        Windows::UI::Xaml::Interop::TypeName m_pageType;
    };
}

namespace winrt::CppWinuiAppDemo::Models::factory_implementation
{
    struct NavItem : NavItemT<NavItem, implementation::NavItem>
    {
    };
}
