#pragma once

#include <winrt/Microsoft.UI.Xaml.Input.h>

namespace winrt::CppWinuiAppDemo::ViewModels
{
    /// @brief Provides a command implementation that can be used for MVVM pattern.
    struct RelayCommand : implements<RelayCommand, Microsoft::UI::Xaml::Input::ICommand>
    {
        /// @brief Initializes a new instance of the RelayCommand class.
        /// @param execute - The action to execute when the command is invoked.
        /// @param canExecute - The function that determines whether the command can execute.
        RelayCommand(std::function<void()> execute,
            std::function<bool()> canExecute = [] { return true; })
            : m_execute(std::move(execute)), m_canExecute(std::move(canExecute))
        {
        }

        /// @brief Registers a handler for the CanExecuteChanged event.
        /// @param handler - The handler to register for the CanExecuteChanged event.
        /// @return The event token for the registered handler.
        event_token CanExecuteChanged(
            Windows::Foundation::EventHandler<IInspectable> const& handler)
        {
            return m_canExecuteChanged.add(handler);
        }

        /// @brief Removes a handler for the CanExecuteChanged event.
        /// @param token - The event token for the handler to remove.
        void CanExecuteChanged(event_token const& token)
        {
            m_canExecuteChanged.remove(token);
        }

        /// @brief Gets a value indicating whether the command can execute.
        /// @param  - The argument for the command execution.
        /// @return A boolean indicating whether the command can execute.
        bool CanExecute(IInspectable const&) const
        {
            return m_canExecute();
        }

        /// @brief Executes the command.
        /// @param  - The argument for the command execution.
        void Execute(IInspectable const&) const
        {
            m_execute();
        }

        /// @brief Raises the CanExecuteChanged event to notify that the command's ability to execute has changed.
        void RaiseCanExecuteChanged()
        {
            m_canExecuteChanged(nullptr, nullptr);
        }

    private:
        /// @brief The action to execute when the command is invoked.
        std::function<void()> m_execute;
        /// @brief The function that determines whether the command can execute.
        std::function<bool()> m_canExecute;
        /// @brief The event that is raised when the command's ability to execute changes.
        winrt::event<Windows::Foundation::EventHandler<IInspectable>> m_canExecuteChanged;
    };
}
