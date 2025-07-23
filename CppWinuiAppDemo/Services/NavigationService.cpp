#include "pch.h"
#include "Services/NavigationService.h"
#if __has_include("Services.NavigationService.g.cpp")
#include "Services.NavigationService.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation::Collections;

namespace winrt::CppWinuiAppDemo::Services::implementation
{
    NavigationService::NavigationService()
    {
    }

    Controls::Frame NavigationService::Frame()
    {
        return m_frame;
    }

    void NavigationService::Frame(Controls::Frame const& value)
    {
        m_frame = value;
    }

    Windows::UI::Xaml::Interop::TypeName NavigationService::SettingsPageType()
    {
        return m_settingsPageType;
    }

    void NavigationService::SettingsPageType(Windows::UI::Xaml::Interop::TypeName const& value)
    {
        m_settingsPageType = value;
    }

    void NavigationService::Register(Models::NavItem item)
    {
        if (item && !item.Tag().empty())
        {
            m_navItems[item.Tag()] = item;
        }
    }

    void NavigationService::Navigate(hstring tag)
    {
        if (m_frame && m_navItems.find(tag) != m_navItems.end())
        {
            auto navItem = m_navItems[tag].value();
            if (navItem)
            {
                m_frame.Navigate(navItem.PageType());
            }
        }
    }

    bool NavigationService::CanGoBack()
    {
        return m_frame && m_frame.CanGoBack();
    }

    void NavigationService::GoBack()
    {
        if (CanGoBack())
        {
            m_frame.GoBack();
        }
    }

    IObservableVector<Models::NavItem> NavigationService::GetNavItems()
    {
        auto items = single_threaded_observable_vector<Models::NavItem>();
        for (const auto& [_, item] : m_navItems)
        {
            if (item)
            {
                items.Append(item.value());
            }
        }
        return items;
    }

    Models::NavItem NavigationService::GetCurrentFrameType()
    {
        auto pageType = m_frame.CurrentSourcePageType();
        auto navItem = GetNavItems().GetAt(0);

        for (const auto& [_, item] : m_navItems)
        {
            if (item && item.value().PageType().Name == pageType.Name)
            {
                navItem = item.value();
                break;
            }
        }
        return navItem;
    }
}
