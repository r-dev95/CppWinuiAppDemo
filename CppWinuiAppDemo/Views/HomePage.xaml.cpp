#include "pch.h"
#include "Views/HomePage.xaml.h"
#if __has_include("Views.HomePage.g.cpp")
#include "Views.HomePage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::CppWinuiAppDemo::Views::implementation
{
    HomePage::HomePage()
    {
    }

    int32_t HomePage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void HomePage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
