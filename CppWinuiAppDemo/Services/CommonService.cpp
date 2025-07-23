#include "pch.h"
#include "Services/CommonService.h"
#if __has_include("Services.CommonService.g.cpp")
#include "Services.CommonService.g.cpp"
#endif

#include <shellapi.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::CppWinuiAppDemo::Services::implementation
{
    hstring CommonService::GetExeDirectory()
    {
        wchar_t buffer[MAX_PATH];
        GetModuleFileNameW(nullptr, buffer, MAX_PATH);
        std::wstring buffer_w = buffer;
        std::wstring dpath = buffer_w.substr(0, buffer_w.find_last_of(L"\\/"));
        return hstring(dpath);
    }

    void CommonService::OpenExplorerExeDirectory()
    {
        auto dPath = GetExeDirectory();
        if (!std::filesystem::exists(to_string(dPath))) {
            SPDLOG_WARN("User settings directory does not exist: {}", to_string(dPath));
            return;
        }
        std::wstring args = std::wstring(dPath.begin(), dPath.end());
        ShellExecuteW(nullptr, L"open", L"explorer.exe", args.c_str(), nullptr, SW_SHOWNORMAL);
    }

    Windows::Foundation::DateTime CommonService::GetCurrentLocalTime()
    {
        Windows::Globalization::Calendar calendar;
        Windows::Foundation::DateTime dt = calendar.GetDateTime();
        return dt;
    }
}
