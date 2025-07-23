#pragma once

#include "Services.CommonService.g.h"

#include "Services/JsonSerializer.h"

namespace winrt::CppWinuiAppDemo::Services::implementation
{
    /// @brief Provides common services.
    struct CommonService : CommonServiceT<CommonService>
    {
        /// @brief Gets the directory of the executable.
        /// @return The executable directory.
        hstring GetExeDirectory();

        /// @brief Opens the executable directory in Windows Explorer.
        void OpenExplorerExeDirectory();

        /// @brief Gets the current local time.
        /// @return The current local time.
        Windows::Foundation::DateTime GetCurrentLocalTime();

        /// @brief Loads a model from a JSON file.
        /// @tparam T - The type of the model to load.
        /// @param fName - The name of the JSON file to load.
        /// @return The loaded model of type T, or an empty instance if loading fails.
        template <typename T>
        T LoadModelFromJsonFile(std::string const& fName)
        {
            std::string fPath = to_string(GetExeDirectory()) + "/" + fName;

            auto result = Services::JsonSerializer<T>::Load(fPath);

            if (!result)
            {
                SPDLOG_WARN("Failed to load model from {}", fPath);
                return T{};
            }

            return result.value();
        }

        /// @brief Saves a model to a JSON file.
        /// @tparam T - The type of the model to save.
        /// @param fName - The name of the JSON file to save.
        /// @param model - The model of type T to save.
        template <typename T>
        void SaveModelToJsonFile(std::string const& fName, T const& model)
        {
            std::string fPath = to_string(GetExeDirectory()) + "/" + fName;

            if (!Services::JsonSerializer<Models::UserSettings>::Save(fPath, model))
            {
                SPDLOG_ERROR("Failed to save model to {}", fPath);
            }
        }
    };
}

namespace winrt::CppWinuiAppDemo::Services::factory_implementation
{
    struct CommonService : CommonServiceT<CommonService, implementation::CommonService>
    {
    };
}
