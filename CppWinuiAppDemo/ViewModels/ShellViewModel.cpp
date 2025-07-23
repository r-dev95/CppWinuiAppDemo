#include "pch.h"
#include "ViewModels/ShellViewModel.h"
#if __has_include("ViewModels.ShellViewModel.g.cpp")
#include "ViewModels.ShellViewModel.g.cpp"
#endif

#include "AppLocator.h"
#include "ViewModels/RelayCommand.h"
#include "Views/ShellPage.xaml.h"

using namespace winrt;
using namespace Microsoft::UI;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::Foundation::Collections;
using namespace Windows::Globalization::DateTimeFormatting;

namespace winrt::CppWinuiAppDemo::ViewModels::implementation
{
    ShellViewModel::ShellViewModel(Services::CommonService comService, Services::UserSettingsService userSetService, Services::NavigationService navService) : m_comService(comService), m_userSetService(userSetService), m_navService(navService)
    {
        m_userSetService.Load();
        auto userSettingsService = get_self<Services::implementation::UserSettingsService>(m_userSetService);
        m_userSettings = userSettingsService->UserSettings();

        m_changeThemeCommand = make<RelayCommand>([this]
            {
                ChangeThemeLoaded();
            }
        );
    }

    Services::NavigationService ShellViewModel::NavService()
    {
        return m_navService;
    }

    bool ShellViewModel::IsDarkTheme()
    {
        return m_isDarkTheme;
    }

    void ShellViewModel::IsDarkTheme(bool value)
    {
        if (SetProperty(m_isDarkTheme, value, __func__))
        {
            m_userSettings->Theme = value ? ElementTheme::Dark : ElementTheme::Light;
        }
    }

    hstring ShellViewModel::ClockText()
    {
        return m_clockText;
    }

    void ShellViewModel::ClockText(hstring value)
    {
        SetProperty(m_clockText, value, __func__);
    }

    IObservableVector<Models::NavItem> ShellViewModel::NavItems()
    {
        return m_navItems;
    }

    void ShellViewModel::NavItems(IObservableVector<Models::NavItem> const& value)
    {
        SetProperty(m_navItems, value, __func__);
    }

    Models::NavItem ShellViewModel::SelectedNavItem()
    {
        return m_selectedNavItem.value();
    }

    void ShellViewModel::SelectedNavItem(Models::NavItem const& value)
    {
        if (value == nullptr)
        {
            m_selectedNavItem.reset();
            return;
        }
        SetProperty(m_selectedNavItem, value, __func__);
    }

    void ShellViewModel::Startup()
    {
        // Theme
        m_isDarkTheme = m_userSettings->Theme == ElementTheme::Dark;

        // Common service (Clock).
        m_timer.Interval(std::chrono::seconds(1));
        m_timer.Tick({ this, &ShellViewModel::UpdateClock });
        m_timer.Start();

        // Navigation service.
        NavItems(m_navService.GetNavItems());
        auto firstPage = NavItems().GetAt(0);
        m_navService.Navigate(firstPage.Tag());
        SelectedNavItem(firstPage);
    }

    void ShellViewModel::StopTimer()
    {
        if (m_timer.IsEnabled())
        {
            m_timer.Stop();
        }
    }

    void ShellViewModel::ItemInvoked(NavigationView const&, NavigationViewItemInvokedEventArgs const& args)
    {
        if (args.IsSettingsInvoked())
        {
            m_navService.Frame().Navigate(m_navService.SettingsPageType());
            return;
        }
        else
        {
            m_navService.Navigate(args.InvokedItem().as<hstring>());
        }
    }

    void ShellViewModel::BackRequested(NavigationView const& sender, NavigationViewBackRequestedEventArgs const&)
    {
        m_navService.GoBack();

        if (m_navService.Frame().CurrentSourcePageType().Name == m_navService.SettingsPageType().Name)
        {
            sender.SelectedItem(sender.SettingsItem());
            SelectedNavItem(nullptr);
        }
        else
        {
            SelectedNavItem(m_navService.GetCurrentFrameType());
        }
    }

    void ShellViewModel::ChangeThemeLoaded()
    {
        auto shellPage = AppLocator::Services()->GetService<Views::ShellPage>();
        shellPage.RequestedTheme(m_isDarkTheme ? ElementTheme::Dark : ElementTheme::Light);

        auto titleBar = AppLocator::Services()->GetService<MainWindow>().AppWindow().TitleBar();
        titleBar.ButtonForegroundColor(m_isDarkTheme ? Colors::White() : Colors::Black());
        titleBar.ButtonHoverBackgroundColor(m_isDarkTheme ? Colors::DimGray() : Colors::LightGray());
        titleBar.ButtonHoverForegroundColor(m_isDarkTheme ? Colors::White() : Colors::Black());
    }

    Microsoft::UI::Xaml::Input::ICommand ShellViewModel::ChangeThemeCommand()
    {
        return m_changeThemeCommand;
    }

    void ShellViewModel::UpdateClock(IInspectable const&, IInspectable const&)
    {
        auto dateTime = m_comService.GetCurrentLocalTime();
        DateTimeFormatter formatter{ m_userSettings->TimeFormat };
        ClockText(formatter.Format(dateTime));
    }
}
