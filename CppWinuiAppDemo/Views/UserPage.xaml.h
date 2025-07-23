#pragma once

#include "Views.UserPage.g.h"

namespace winrt::CppWinuiAppDemo::Views::implementation
{
    struct UserPage : UserPageT<UserPage>
    {
        UserPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::CppWinuiAppDemo::Views::factory_implementation
{
    struct UserPage : UserPageT<UserPage, implementation::UserPage>
    {
    };
}
