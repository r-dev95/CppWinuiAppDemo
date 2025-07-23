#include "pch.h"
#include "NavItem.h"
#if __has_include("Models.NavItem.g.cpp")
#include "Models.NavItem.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation::Collections;

namespace winrt::CppWinuiAppDemo::Models::implementation
{
    NavItem::NavItem(hstring const& name, hstring const& tag, Controls::Symbol const& icon, Windows::UI::Xaml::Interop::TypeName const& pageType) : m_name{ name }, m_tag{ tag }, m_icon{ icon }, m_pageType{ pageType }
    {
    }

    hstring NavItem::Name()
    {
        return m_name;
    }

    void NavItem::Name(hstring const& value)
    {
        m_name = value;
    }

    hstring NavItem::Tag()
    {
        return m_tag;
    }

    void NavItem::Tag(hstring const& value)
    {
        m_tag = value;
    }

    Controls::Symbol NavItem::Icon()
    {
        return m_icon;
    }

    void NavItem::Icon(Controls::Symbol const& value)
    {
        m_icon = value;
    }

    Windows::UI::Xaml::Interop::TypeName NavItem::PageType()
    {
        return m_pageType;
    }

    void NavItem::PageType(Windows::UI::Xaml::Interop::TypeName const& value)
    {
        m_pageType = value;
    }
}
