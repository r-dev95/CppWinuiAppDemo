#include "pch.h"
#include "Views/ShellPage.xaml.h"
#if __has_include("Views.ShellPage.g.cpp")
#include "Views.ShellPage.g.cpp"
#endif

#include "AppLocator.h"
#include "Models/NavItem.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::CppWinuiAppDemo::Views::implementation
{
    ShellPage::ShellPage(ViewModels::ShellViewModel vm) : m_viewModel(vm)
    {
    }

    ViewModels::ShellViewModel ShellPage::ViewModel()
    {
        return m_viewModel;
    }

    void ShellPage::Startup()
    {
        auto mainWindow = AppLocator::Services()->GetService<MainWindow>();
        mainWindow.ExtendsContentIntoTitleBar(true);
        mainWindow.SetTitleBar(AppTitleBar());

        auto navService = m_viewModel.NavService();
        navService.Frame(navigationFrame());
        navService.SettingsPageType(winrt::xaml_typename<Views::SettingsPage>());
        navService.Register(Models::NavItem{ L"Home", L"Home", Controls::Symbol::Home, winrt::xaml_typename<Views::HomePage>() });
        navService.Register(Models::NavItem{ L"User", L"User", Controls::Symbol::OtherUser, winrt::xaml_typename<Views::UserPage>() });

        m_viewModel.Startup();
    }
}
