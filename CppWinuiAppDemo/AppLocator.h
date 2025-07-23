#pragma once

#include "Services/ServiceCollection.h"

namespace winrt::CppWinuiAppDemo
{
    /// @brief Provides a static locator for application services.
    struct AppLocator
    {
        /// @brief Gets the service collection.
        /// @return The service collection.
        static com_ptr<Services::implementation::ServiceCollection> Services()
        {
            return m_services;
        }

        /// @brief Sets the service collection.
        /// @param services - The service collection to set.
        static void Services(com_ptr<Services::implementation::ServiceCollection> const& services)
        {
            m_services = services;
        }

    private:
        /// @brief The static service collection instance.
        inline static com_ptr<Services::implementation::ServiceCollection> m_services{ nullptr };
    };
}
