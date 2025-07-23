#pragma once

#include "Services/ServiceLifetime.h"
#include <functional>
#include <mutex>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

namespace winrt::CppWinuiAppDemo::Services::implementation
{
    /// @brief Provides a service collection for dependency injection.
    struct ServiceCollection : implements<ServiceCollection, Windows::Foundation::IInspectable>
    {
        /// @brief Initializes a new instance of the ServiceCollection class.
        ServiceCollection() {}

        /// @brief Registers a service with the Singleton lifetime.
        /// @tparam T - The type of the service to register.
        template<typename T>
        void RegisterSingleton()
        {
            Register<T, T>(ServiceLifetime::Singleton);
        }

        /// @brief Registers a service with the Transient lifetime.
        /// @tparam T - The type of the service to register.
        template<typename T>
        void RegisterTransient()
        {
            Register<T, T>(ServiceLifetime::Transient);
        }

        /// @brief Registers a service with the Singleton lifetime.
        /// @tparam TInterface - The interface type of the service.
        /// @tparam TImplementation - The implementation type of the service.
        template<typename TInterface, typename TImplementation>
        void RegisterSingleton()
        {
            Register<TInterface, TImplementation>(ServiceLifetime::Singleton);
        }

        /// @brief Registers a service with the Transient lifetime.
        /// @tparam TInterface - The interface type of the service.
        /// @tparam TImplementation - The implementation type of the service.
        template<typename TInterface, typename TImplementation>
        void RegisterTransient()
        {
            Register<TInterface, TImplementation>(ServiceLifetime::Transient);
        }

        /// @brief Registers a service with a factory function and a specified lifetime.
        /// @tparam TInterface - The interface type of the service.
        /// @param factory - A factory function that creates an instance of the service.
        /// @param lifetime - The lifetime of the service.
        template<typename TInterface>
        void RegisterWithFactory(std::function<TInterface(ServiceCollection&)> factory, ServiceLifetime lifetime)
        {
            std::scoped_lock lock(m_mutex);
            m_services[typeid(TInterface)] = ServiceEntry
            {
                [this, factory]() -> TInterface
                {
                    return factory(*this);
                },
                lifetime,
                nullptr
            };
        }

        /// @brief Gets a registered service by its type.
        /// @tparam T - The type of the service to register.
        /// @return An instance of the requested service type.
        template<typename T>
        T GetService()
        {
            std::scoped_lock lock(m_mutex);
            return Resolve(typeid(T)).as<T>();
        }

    private:
        using FactoryFunction = std::function<Windows::Foundation::IInspectable()>;

        /// @brief Defines a service entry in the service collection.
        struct ServiceEntry
        {
            /// @brief The factory function to create the service instance.
            FactoryFunction factory;
            /// @brief The lifetime of the service.
            ServiceLifetime lifetime;
            /// @brief The instance of the service, if it is a singleton.
            Windows::Foundation::IInspectable instance{ nullptr };
        };

        /// @brief The collection of registered services.
        std::unordered_map<std::type_index, ServiceEntry> m_services;
        /// @brief The mutex to protect access to the service collection.
        std::recursive_mutex m_mutex;

        /// @brief Registers a service with a factory function and a specified lifetime.
        /// @tparam TInterface - The interface type of the service.
        /// @tparam TImplementation - The implementation type of the service.
        /// @param lifetime - The lifetime of the service.
        template<typename TInterface, typename TImplementation>
        void Register(ServiceLifetime lifetime)
        {
            RegisterWithFactory<TInterface>(
                [](ServiceCollection& provider) -> TInterface
                {
                    return provider.CreateInstance<TInterface, TImplementation>();
                },
                lifetime
            );
        }

        /// @brief Resolves a service by its type index.
        /// @param key - The type index of the service to resolve.
        /// @return The resolved service instance.
        Windows::Foundation::IInspectable Resolve(std::type_index key)
        {
            auto it = m_services.find(key);
            if (it == m_services.end())
            {
                throw std::runtime_error("Service not registered.");
            }

            ServiceEntry& entry = it->second;

            if (entry.lifetime == ServiceLifetime::Singleton)
            {
                if (!entry.instance)
                {
                    entry.instance = entry.factory();
                }
                return entry.instance;
            }
            else if (entry.lifetime == ServiceLifetime::Transient)
            {
                return entry.factory();
            }

            throw std::runtime_error("Unsupported service lifetime.");
        }

        /// @brief Creates an instance of a service implementation.
        /// @tparam TInterface - The interface type of the service.
        /// @tparam TImplementation - The implementation type of the service.
        /// @return The created service instance.
        template<typename TInterface, typename TImplementation>
        TInterface CreateInstance()
        {
            if constexpr (std::is_constructible_v<TImplementation>)
            {
                return make<TImplementation>();
            }
            else
            {
                static_assert(false, "CreateInstance must be specialized for type with dependencies.");
            }
        }
    };
}
