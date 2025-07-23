#include "pch.h"
#include "App.xaml.h"

#include "AppLocator.h"
#include "AppLogging.h"
#include "MainWindow.xaml.h"
#include "Views/HomePage.xaml.h"
#include "Views/SettingsPage.xaml.h"
#include "Views/ShellPage.xaml.h"
#include "Views/UserPage.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::CppWinuiAppDemo::implementation
{
    App::App()
    {
#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
        {
            if (IsDebuggerPresent())
            {
                auto errorMessage = e.Message();
                __debugbreak();
            }
        });
#endif

        AppLocator::Services(make_self<Services::implementation::ServiceCollection>());
        auto services = AppLocator::Services();

        // Services
        services->RegisterSingleton<Services::CommonService, Services::implementation::CommonService>();
        services->RegisterWithFactory<Services::UserSettingsService>(
            [](Services::implementation::ServiceCollection& provider)
            {
                auto comService = provider.GetService<Services::CommonService>();
                return make_self<Services::implementation::UserSettingsService>(comService).as<Services::UserSettingsService>();
            },
            Services::ServiceLifetime::Singleton
        );
        services->RegisterSingleton<Services::NavigationService, Services::implementation::NavigationService>();

        // Views and ViewModels
        services->RegisterSingleton<CppWinuiAppDemo::MainWindow, MainWindow>();
        services->RegisterWithFactory<ViewModels::ShellViewModel>(
            [](Services::implementation::ServiceCollection& provider)
            {
                auto comService = provider.GetService<Services::CommonService>();
                auto userSetService = provider.GetService<Services::UserSettingsService>();
                auto navService = provider.GetService<Services::NavigationService>();
                return make_self<ViewModels::implementation::ShellViewModel>(comService, userSetService, navService).as<ViewModels::ShellViewModel>();
            },
            Services::ServiceLifetime::Singleton
        );
        services->RegisterWithFactory<Views::ShellPage>(
            [](Services::implementation::ServiceCollection& provider)
            {
                auto vm = provider.GetService<ViewModels::ShellViewModel>();
                return make_self<Views::implementation::ShellPage>(vm).as<Views::ShellPage>();
            },
            Services::ServiceLifetime::Singleton
        );
        services->RegisterWithFactory<ViewModels::SettingsViewModel>(
            [](Services::implementation::ServiceCollection& provider)
            {
                auto comService = provider.GetService<Services::CommonService>();
                auto userSetService = provider.GetService<Services::UserSettingsService>();
                return make_self<ViewModels::implementation::SettingsViewModel>(comService, userSetService).as<ViewModels::SettingsViewModel>();
            },
            Services::ServiceLifetime::Singleton
        );
        services->RegisterSingleton<Views::SettingsPage, Views::implementation::SettingsPage>();
        services->RegisterSingleton<Views::HomePage, Views::implementation::HomePage>();
        services->RegisterSingleton<Views::UserPage, Views::implementation::UserPage>();
    }

    void App::OnLaunched(LaunchActivatedEventArgs const&)
    {
        auto services = AppLocator::Services();

        AppLogging(services->GetService<Services::CommonService>());

        auto mainWindow = services->GetService<CppWinuiAppDemo::MainWindow>();
        mainWindow.Closed({ this, &App::OnClosed });
        mainWindow.Activate();

        auto shellPage = services->GetService<Views::ShellPage>();
        mainWindow.Content(shellPage);
        shellPage.Startup();
    }

    void App::OnClosed(IInspectable const&, WindowEventArgs const&)
    {
        AppLocator::Services()->GetService<ViewModels::ShellViewModel>().StopTimer();
        AppLocator::Services()->Release();
    }
}
