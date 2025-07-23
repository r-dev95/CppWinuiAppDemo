#pragma once

#include "Services/CommonService.h"

namespace winrt::CppWinuiAppDemo
{
    /// @brief Provides application logging functionality.
    struct AppLogging
    {
        /// @brief Initializes a new instance of the AppLogging class.
        /// @param commonService - The common service instance.
        AppLogging(Services::CommonService commonService) : m_commonService(commonService)
        {
            auto fpath = GetFilePath();
            auto logger = spdlog::rotating_logger_mt("file", fpath, (size_t)std::pow(1024, 3), 10);
            logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%6P][%6t][%-8l][%s][%5#] - %v");
            logger->set_level(spdlog::level::trace);
            spdlog::set_level(spdlog::level::trace);
            spdlog::flush_every(std::chrono::seconds(1));
            spdlog::set_default_logger(logger);
        }

    private:
        /// @brief The common service instance.
        Services::CommonService m_commonService{ nullptr };

        /// @brief The logger instance.
        std::shared_ptr<spdlog::logger> m_logger{ nullptr };

        /// @brief Gets the file path.
        /// @return The file path.
        std::string GetFilePath()
        {
            auto commonService = get_self<Services::implementation::CommonService>(m_commonService);
            auto fname = GetFileName(commonService);
            return to_string(commonService->GetExeDirectory()) + "/logs/" + fname + ".log";
        }

        /// @brief Gets the file name based on the current local time.
        /// @param commonService - The common service instance.
        /// @return The file name.
        std::string GetFileName(Services::implementation::CommonService *commonService)
        {
            auto dt = commonService->GetCurrentLocalTime();
            Windows::Globalization::DateTimeFormatting::DateTimeFormatter formatter{ L"shortdate" };
            auto fname = std::wstring(formatter.Format(dt));
            fname.erase(std::remove(fname.begin(), fname.end(), '/'), fname.end());
            return RemoveInvalidChars(to_string(fname));
        }

        /// @brief Removes invalid characters from a string.
        /// @param str - The input string to clean.
        /// @return The cleaned string without invalid characters.
        std::string RemoveInvalidChars(std::string const& str)
        {
            std::string output;
            for (char ch : str)
            {
                if ((ch >= 0x20 && ch != 0x7F)
                    && ch != 0x200E
                    && ch != 0x200F
                    && !(ch >= 0x202A && ch <= 0x202E))
                {
                    output += ch;
                }
            }
            return output;
        }
    };
}
