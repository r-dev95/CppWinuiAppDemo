#pragma once

#include "Views.HomePage.g.h"

namespace winrt::CppWinuiAppDemo::Views::implementation
{
    struct HomePage : HomePageT<HomePage>
    {
        HomePage();

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::CppWinuiAppDemo::Views::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
