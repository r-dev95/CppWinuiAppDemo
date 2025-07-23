#include "pch.h"
#include "Views/SettingsPage.xaml.h"
#if __has_include("Views.SettingsPage.g.cpp")
#include "Views.SettingsPage.g.cpp"
#endif

#include "AppLocator.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::CppWinuiAppDemo::Views::implementation
{
    SettingsPage::SettingsPage()
    {
        m_viewModel = AppLocator::Services()->GetService<ViewModels::SettingsViewModel>();
        Loaded({ this, &SettingsPage::OnLoaded });
    }

    ViewModels::SettingsViewModel SettingsPage::ViewModel()
    {
        return m_viewModel;
    }

    void SettingsPage::OnLoaded(IInspectable const&, RoutedEventArgs const&)
    {
        m_viewModel.TimeFormatComboBox(timeFormatComboBox());
        m_viewModel.Startup();
    }
}
