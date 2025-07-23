#pragma once

#include <fstream>

namespace winrt::CppWinuiAppDemo::Services
{
    /// @brief Provides JSON serialization and deserialization functionality.
    /// @tparam T - The type to serialize or deserialize.
    template <typename T>
    class JsonSerializer
    {
    public:
        /// @brief Loads an object of type T from a JSON file.
        /// @param fpath - The file path to the JSON file.
        /// @return The loaded object of type T, or std::nullopt if loading fails.
        static std::optional<T> Load(std::string const& fpath)
        {
            try
            {
                std::ifstream file(fpath);
                if (!file.is_open()) return std::nullopt;
                nlohmann::json j;
                file >> j;
                return j.get<T>();
            }
            catch (...)
            {
                return std::nullopt;
            }
        }

        /// @brief Saves an object of type T to a JSON file.
        /// @param fpath - The file path to save the JSON file.
        /// @param obj - The object of type T to save.
        /// @return The result indicating if the save operation was successful.
        static bool Save(std::string const& fpath, T const& obj)
        {
            try
            {
                nlohmann::json j = obj;
                std::ofstream file(fpath);
                if (!file.is_open()) return false;
                file << j.dump(4);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }
    };
}
