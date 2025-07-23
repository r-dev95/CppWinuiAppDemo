#pragma once

namespace winrt::CppWinuiAppDemo::ViewModels
{
    /// @brief Provides a base class for view models that implements INotifyPropertyChanged.
    struct BindableBase : implements<BindableBase, Microsoft::UI::Xaml::Data::INotifyPropertyChanged>
    {
        /// @brief Registers a handler for the PropertyChanged event.
        /// @param handler - The handler to register.
        /// @return The event token for the registered handler.
        event_token PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
        {
            return m_propertyChanged.add(handler);
        }

        /// @brief Removes a handler for the PropertyChanged event.
        /// @param token - The event token for the handler to remove.
        void PropertyChanged(event_token const& token)
        {
            m_propertyChanged.remove(token);
        }

    protected:
        /// @brief Raises the PropertyChanged event for a specific property.
        /// @param propertyName - The name of the property that has changed.
        void RaisePropertyChanged(hstring const& propertyName)
        {
            m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ propertyName });
        }

        /// @brief Sets a property value and raises the PropertyChanged event if the value has changed.
        /// @tparam T - The type of the property.
        /// @param storage - The storage reference for the property value.
        /// @param value - The new value to set for the property.
        /// @param propertyName - The name of the property that has changed.
        /// @return The boolean indicating whether the property value was changed.
        template<typename T>
        bool SetProperty(T& storage, T const& value, hstring const& propertyName)
        {
            if (storage != value)
            {
                storage = value;
                RaisePropertyChanged(propertyName);
                return true;
            }
            return false;
        }

        /// @brief Sets a property value and raises the PropertyChanged event if the value has changed.
        /// @tparam T - The type of the property.
        /// @param storage - The storage reference for the property value.
        /// @param value - The new value to set for the property.
        /// @param propertyName - The name of the property that has changed.
        /// @return The boolean indicating whether the property value was changed.
        template<typename T>
        bool SetProperty(T& storage, T const& value, char const* propertyName)
        {
            return SetProperty(storage, value, to_hstring(propertyName));
        }

        /// @brief Sets a property value for an optional type and raises the PropertyChanged event if the value has changed.
        /// @tparam T - The type of the property.
        /// @param storage - The storage reference for the optional property value.
        /// @param value - The new value to set for the property.
        /// @param propertyName - The name of the property that has changed.
        /// @return The boolean indicating whether the property value was changed.
        template<typename T>
        bool SetProperty(std::optional<T>& storage, T const& value, hstring const& propertyName)
        {
            if (storage != value)
            {
                storage = value;
                RaisePropertyChanged(propertyName);
                return true;
            }
            return false;
        }

        /// @brief Sets a property value for an optional type and raises the PropertyChanged event if the value has changed.
        /// @tparam T - The type of the property.
        /// @param storage - The storage reference for the optional property value.
        /// @param value - The new value to set for the property.
        /// @param propertyName - The name of the property that has changed.
        /// @return The boolean indicating whether the property value was changed.
        template<typename T>
        bool SetProperty(std::optional<T>& storage, T const& value, char const* propertyName)
        {
            return SetProperty(storage, value, to_hstring(propertyName));
        }

    private:
        /// @brief The event that is raised when a property value changes.
        event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}