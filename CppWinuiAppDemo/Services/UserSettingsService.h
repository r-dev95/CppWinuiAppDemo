#pragma once

#include "Services.UserSettingsService.g.h"

#include "Services/CommonService.h"
#include "Models/UserSettings.h"

namespace winrt::CppWinuiAppDemo::Services::implementation
{
    /// @brief Provides a service for managing user settings.
    struct UserSettingsService : UserSettingsServiceT<UserSettingsService>
    {
        /// @brief Initializes a new instance of the UserSettingsService class.
        /// @param comService - The common service instance.
        UserSettingsService(Services::CommonService comService);

        /// @brief Gets the user settings.
        /// @return The user settings model.
        Models::UserSettings* UserSettings();

        /// @brief Loads user settings from a JSON file.
        void Load();
        /// @brief Saves user settings to a JSON file.
        void Save();

    private:
        /// @brief The common service instance.
        Services::CommonService m_comService{ nullptr };

        /// @brief The user settings model.
        Models::UserSettings m_userSettings;

        /// @brief Logs the loading or saving of user settings.
        /// @param flag - The flag indicating whether to log loading (0) or saving (1).
        void Log(int flag);
    };
}

namespace winrt::CppWinuiAppDemo::Services::factory_implementation
{
    struct UserSettingsService : UserSettingsServiceT<UserSettingsService, implementation::UserSettingsService>
    {
    };
}