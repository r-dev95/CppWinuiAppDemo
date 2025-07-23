#include "pch.h"
#include "Views/UserPage.xaml.h"
#if __has_include("Views.UserPage.g.cpp")
#include "Views.UserPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::CppWinuiAppDemo::Views::implementation
{
    UserPage::UserPage()
    {
    }

    int32_t UserPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void UserPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
