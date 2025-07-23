#pragma once

namespace winrt::CppWinuiAppDemo::Services
{
    /// @brief Defines the lifetime of a service in the application.
    enum class ServiceLifetime
    {
        /// @brief The service is created once and shared across the application.
        Singleton,
        /// @brief The service is created each time it is requested.
        Transient
    };

}
