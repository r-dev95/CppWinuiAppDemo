<div align="center">
  <img
    src="docs/image/demo.gif"
    alt="Project Demo"
    width="500"/>
</div>

# :book: Overview

[![Japanese](https://img.shields.io/badge/Japanese-018EF5.svg?labelColor=d3d3d3&logo=readme)](./README.md)
[![license](https://img.shields.io/github/license/r-dev95/CppWinuiAppDemo)](./LICENSE)

[![Windows](https://custom-icon-badges.herokuapp.com/badge/Windows-0078d7.svg?labelColor=d3d3d3&logo=windows)](https://www.microsoft.com/ja-jp/windows?r=1)
[![C++](https://custom-icon-badges.herokuapp.com/badge/C++-00599C.svg?labelColor=d3d3d3&logo=cpp)](https://learn.microsoft.com/ja-jp/cpp/?view=msvc-170)

このリポジトリでは、Windows App SDK (WinUI3) と C++ を使用して構築された、モダンなWindowsデスクトップアプリケーションのサンプルを提供します。

MVVMデザインパターン、依存性の注入 (DI)、設定管理、ロギングなど、現代的なアプリケーション開発におけるベストプラクティスを学ぶための実践的なリソースとなることを目的としています。

> [!note]
> C#版: [r-dev95/WinuiAppDemo](https://github.com/r-dev95/WinuiAppDemo)

> [!warning]
> 物理ディレクトリやnamespaceを区切り開発する際、注意が必要なため、[こちら](docs/memo.md)を参照してください。

## :sparkles: Features

<div align="center">
  <img
    src="docs/image/app.png"
    alt="App Settings Page"
    width="500"/>
</div>

### 動的なUI更新

* タイトルバーに現在時刻をリアルタイムで表示
* ライトモードとダークモードのテーマ切り替え

### ページナビゲーション

* `NavigationView` を使用した複数ページ間の遷移

### 永続的な設定管理

* 時計の表示形式を設定ページから変更
* 変更した設定は `userSettings.json` ファイルに保存され、次回起動時も維持

### ファイルアクセス

* 設定ファイルが保存されているフォルダをエクスプローラーで開く機能

### ロギング

* `spdlog` によるアプリケーションの動作ログ記録

## :hammer_and_wrench: Technology Stack

* **UIフレームワーク:** Windows App SDK / WinUI 3
* **言語:** C++
* **アーキテクチャ:** MVVM (Model-View-ViewModel)
* **依存性の注入:** `ServiceCollection` (カスタム実装)
* **ロギング:** [spdlog](https://github.com/gabime/spdlog)
* **JSONパーサー:** [nlohmann/json](https://github.com/nlohmann/json)

## :rocket: Getting Started

### 前提条件

#### [Visual Studio 2022](https://visualstudio.microsoft.com/ja/vs/)

* C++によるデスクトップ開発ワークロード
* ユニバーサル Windows プラットフォーム開発ワークロード

#### [Windows App SDK](https://learn.microsoft.com/ja-jp/windows/apps/windows-app-sdk/downloads)

### インストールと実行手順

#### インストール

```bash
git clone https://github.com/r-dev95/CppWinuiAppDemo.git
```

#### ソリューションのオープン

`CppWinuiAppDemo.sln` ファイルをVisual Studioで開きます。

#### 実行

Visual Studioの上部ツールバーにある緑色の再生ボタン（`CppWinuiAppDemo (Package)`）をクリックするか、`F5`キーを押してデバッグを開始します。

## :file_folder: Project Structure

このプロジェクトは、関心事の分離を促進するためにMVVMパターンに基づいて構成されています。

```bash
CppWinuiAppDemo/
├── Models/         # アプリケーションのデータ構造を定義
├── Views/          # UIを定義するXAMLページとコードビハインド
├── ViewModels/     # UIのロジックと状態を管理
├── Services/       # ビジネスロジックや共通機能を提供
├── App.xaml.cpp    # DIコンテナの設定、サービスの登録、アプリの起動処理
└── MainWindow.xaml # アプリケーションのメインウィンドウ
```

## :key: ライセンス (License)

このリポジトリは [MIT License](./LICENSE.txt) の下でライセンスされています。
