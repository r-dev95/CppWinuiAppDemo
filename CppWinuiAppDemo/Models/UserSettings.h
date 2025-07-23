#pragma once

namespace winrt::CppWinuiAppDemo::Models
{
    /// @brief Defines user settings.
    struct UserSettings
    {
        /// @brief The theme of the application.
        Microsoft::UI::Xaml::ElementTheme Theme{ Microsoft::UI::Xaml::ElementTheme::Light };
        /// @brief The time format used in the application.
        hstring TimeFormat{ L"longtime" };
    };

    /// @brief Converts UserSettings to JSON format.
    /// @param j - The JSON object to serialize to.
    /// @param p - The UserSettings object to serialize from.
    inline void to_json(nlohmann::json& j, const UserSettings& p) {
        j = nlohmann::json{
            {"Theme", static_cast<int>(p.Theme)},
            {"TimeFormat", winrt::to_string(p.TimeFormat)}
        };
    }

    /// @brief Converts JSON format to UserSettings.
    /// @param j - The JSON object to deserialize from.
    /// @param p - The UserSettings object to deserialize to.
    inline void from_json(const nlohmann::json& j, UserSettings& p) {
        int theme;
        std::string timeFormat;
        j.at("Theme").get_to(theme);
        p.Theme = static_cast<Microsoft::UI::Xaml::ElementTheme>(theme);
        j.at("TimeFormat").get_to(timeFormat);
        p.TimeFormat = winrt::to_hstring(timeFormat);
    }
}