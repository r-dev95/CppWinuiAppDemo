# 開発メモ

## .vcxprojの修正

非パッケージアプリとして、開発するために下記修正を行う。

https://learn.microsoft.com/ja-jp/windows/apps/winui/winui3/create-your-first-winui3-app

```diff
<Project ...>
    ...
    <PropertyGroup Label="Globals">
        ...
-       <AppxPackage>true</AppxPackage>
+       <AppxPackage>false</AppxPackage>
        ...
+       <WindowsPackageType>None</WindowsPackageType>
        ...
    </PropertyGroup>
    ...
</Project>
```

## 物理ディレクトリとnamespaceを合わせる

C++では、C#のようにファイルを追加した際にディレクトリに合わせてnamespaceを設定してくれません。

またビルド時に自動生成されるファイルの整合性が一部取れないため、手を加える必要があります。

### 前提

`.idl`、`.xaml`ファイルをビルドする際に生成されるファイルについて示します。

#### .idlファイル

```diff
-   namespace App1
+   namespace App1.Views
    {
        [default_interface]
        runtimeclass ShellPage : Microsoft.UI.Xaml.Controls.Page
        {
            ShellPage();
            Int32 MyProperty;
        }
    }
```

namespaceを切らない場合 (-)：

```bash
Generated Files
├─ShellPage.g.cpp
└─ShellPage.g.h
```

namespaceを切る場合 (+)：

```bash
Generated Files
├─Views.ShellPage.g.cpp
└─Views.ShellPage.g.h
```

#### .xamlファイル

`.xaml`ファイルは物理ディレクトリを分ける場合、`x:Class`を合わせる必要があるみたいです。

```diff
    <?xml version="1.0" encoding="utf-8"?>
    <Page
-       x:Class="App1.ShellPage"
+       x:Class="App1.Views.ShellPage"
        xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
        xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
-       xmlns:local="using:App1"
+       xmlns:local="using:App1.Views" ←これは生成されるファイルに影響はない
        xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
        xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
        mc:Ignorable="d">

        <Grid>

        </Grid>
    </Page>
```

物理ディレクトリを分けない場合 (-)：

```bash
Generated Files
├─ShellPage.xaml
├─ShellPage.xaml.g.h
├─ShellPage.xaml.g.hpp
└─ShellPage.xbf
```

物理ディレクトリを分ける場合 (+)：

```bash
Generated Files
└─Views
  ├─ShellPage.xaml
  ├─ShellPage.xaml.g.h
  ├─ShellPage.xaml.g.hpp
  └─ShellPage.xbf
```

### ファイルの修正

前提を踏まえて、ファイルを修正します。

#### .idlファイルの修正

前提の通り。

#### .xamlファイルの修正

前提の通り。

#### .xaml.h (または.h) ファイルの修正

```diff
    #pragma once

-   #include "ShellPage.g.h"
+   #include "Views.ShellPage.g.h"

-   namespace winrt::App1::implementation
+   namespace winrt::App1::Views::implementation
    {
        struct ShellPage : ShellPageT<ShellPage>
        {
            ShellPage()
            {
                // Xaml objects should not call InitializeComponent during construction.
                // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
            }

            int32_t MyProperty();
            void MyProperty(int32_t value);
        };
    }

-   namespace winrt::App1::factory_implementation
+   namespace winrt::App1::Views::factory_implementation
    {
        struct ShellPage : ShellPageT<ShellPage, implementation::ShellPage>
        {
        };
    }
```

#### .xaml.cpp (または.cpp) ファイルの修正

```diff
    #include "pch.h"
-   #include "ShellPage.xaml.h"
-   #if __has_include("ShellPage.g.cpp")
-   #include "ShellPage.g.cpp"
+   #include "Views/ShellPage.xaml.h"
+   #if __has_include("Views.ShellPage.g.cpp")
+   #include "Views.ShellPage.g.cpp"
    #endif

    using namespace winrt;
    using namespace Microsoft::UI::Xaml;

    // To learn more about WinUI, the WinUI project structure,
    // and more about our project templates, see: http://aka.ms/winui-project-info.

-   namespace winrt::App1::implementation
+   namespace winrt::App1::Views::implementation
    {
        int32_t ShellPage::MyProperty()
        {
            throw hresult_not_implemented();
        }

        void ShellPage::MyProperty(int32_t /* value */)
        {
            throw hresult_not_implemented();
        }
    }
```

**`.xaml`ファイルはなく、`.idl`ファイルのみの場合、これで修正は終了です。**

---
**`.xaml`ファイルもある場合**

ここからは自動生成されたファイルに手を加えるため、通常、推奨されません。

---

#### .xaml.g.hファイルの移動とファイル名の変更

`Views/`下のファイルを削除する必要はないので、コピペでOKです。(ビルドすれば再び生成されるので)

```diff
-   Generated Files
-   └─Views
-     └─ShellPage.xaml.g.h

+   Generated Files
+   └─Views.ShellPage.xaml.g.h
```

> [!note]
> 自動生成された`Generated Files/Views.ShellPage.g.h`を見ると、`Views.ShellPage.xaml.g.h`をincludeしようとしていることがわかります。
>
> 自動生成されたファイルの内容を変更したくないので、上記のようにファイルの移動と名前の変更で対応しています。
>
> ```cpp
> ...
> #if defined(WINRT_FORCE_INCLUDE_SHELLPAGE_XAML_G_H) || __has_include("Views.ShellPage.xaml.g.h")
> #include "Views.ShellPage.xaml.g.h"
> ...
> ```
