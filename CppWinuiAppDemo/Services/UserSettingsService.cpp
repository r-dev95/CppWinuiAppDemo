#include "pch.h"
#include "Services/UserSettingsService.h"
#if __has_include("Services.UserSettingsService.g.cpp")
#include "Services.UserSettingsService.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::CppWinuiAppDemo::Services::implementation
{
    UserSettingsService::UserSettingsService(Services::CommonService comService) : m_comService(comService)
    {
    }

    Models::UserSettings* UserSettingsService::UserSettings()
    {
        return &m_userSettings;
    }

    void UserSettingsService::Load()
    {
        auto commonService = get_self<Services::implementation::CommonService>(m_comService);
        m_userSettings = commonService->LoadModelFromJsonFile<Models::UserSettings>("userSettings.json");
        Log(0);
    }

    void UserSettingsService::Save()
    {
        auto commonService = get_self<Services::implementation::CommonService>(m_comService);
        commonService->SaveModelToJsonFile<Models::UserSettings>("userSettings.json", m_userSettings);
        Log(1);
    }

    void UserSettingsService::Log(int flag)
    {
        auto str = flag == 0 ? "Loading" : "Saving";

        SPDLOG_DEBUG("{} user settings:", str);
        SPDLOG_DEBUG("m_userSettings.TimeFormat: {}", winrt::to_string(m_userSettings.TimeFormat));
    }
}
