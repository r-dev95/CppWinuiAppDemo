#include "pch.h"
#include "ViewModels/SettingsViewModel.h"
#if __has_include("ViewModels.SettingsViewModel.g.cpp")
#include "ViewModels.SettingsViewModel.g.cpp"
#endif

#include "ViewModels/RelayCommand.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::CppWinuiAppDemo::ViewModels::implementation
{
    SettingsViewModel::SettingsViewModel(Services::CommonService comService, Services::UserSettingsService userSetService) : m_comService(comService), m_userSetService(userSetService)
    {
        m_userSetService.Load();
        auto userSettingsService = get_self<Services::implementation::UserSettingsService>(m_userSetService);
        m_userSettings = userSettingsService->UserSettings();

        m_saveSettingsCommand = make<RelayCommand>([this]
            {
                m_userSetService.Save();
            }
        );

        m_openExplorerCommand = make<RelayCommand>([this]
            {
                m_comService.OpenExplorerExeDirectory();
            }
        );
    }

    Controls::ComboBox SettingsViewModel::TimeFormatComboBox()
    {
        return m_timeFormatComboBox;
    }

    void SettingsViewModel::TimeFormatComboBox(Controls::ComboBox const& value)
    {
        m_timeFormatComboBox = value;
    }

    hstring SettingsViewModel::SelectedTimeFormat()
    {
        return m_selectedTimeFormat;
    }

    void SettingsViewModel::SelectedTimeFormat(hstring const& value)
    {
        SetProperty(m_selectedTimeFormat, value, __func__);
    }

    void SettingsViewModel::Startup()
    {
        m_timeFormatComboBox.SelectionChanged({ this, &SettingsViewModel::OnChangedTimeFormat });
        SelectedTimeFormat(m_userSettings->TimeFormat);
    }

    Microsoft::UI::Xaml::Input::ICommand SettingsViewModel::SaveSettingsCommand()
    {
        return m_saveSettingsCommand;
    }

    Microsoft::UI::Xaml::Input::ICommand SettingsViewModel::OpenExplorerCommand()
    {
        return m_openExplorerCommand;
    }

    void SettingsViewModel::OnChangedTimeFormat(IInspectable const&, Controls::SelectionChangedEventArgs const&)
    {
        m_selectedTimeFormat = m_timeFormatComboBox.SelectedItem().as<winrt::hstring>();
        m_userSettings->TimeFormat = SelectedTimeFormat();
    }
}
