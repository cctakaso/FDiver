# FileDiver Project readme
Copyright (c) 2025 Takashi Ogisawa
last update  2025/12/09

## 概要
FileDiverは、Microsoft Foundation Class (MFC)を使用して開発されたWindowsアプリケーションプロジェクトです。このリポジトリには、アプリケーションのソースコード、リソース、および関連する設定ファイルが含まれています。

## 特徴・機能
最高速・高機能ファイル検索ソフト（Ｇｒｅｐ）です。
1. 超高速検索
2. 日本語の表現のゆらぎを克服する、あいまい検索機能
3. 複数のキーワードを、一気に検索できるマルチキー対応
4. 各種圧縮書庫ファイル内検索機能
   1) 複数の書庫内のファイルを連続検索します！
   2) 圧縮ファイルの入れ子状態（圧縮ファイル内、圧縮ファイル）でも検索できます！
   3) タグファイルとして保管したあとも、
        指定ファイルを好きなときに解凍して閲覧が可能です！
5. 検索結果の保管＆オープン機能
6. 検索結果リストの表示方法選択機能 (ツリー/リスト,パス分類/ファイル分類)
7. タグジャンプ機能
8. 検索処理中に、なるべく他のソフトウエアの速度を損なわない
9. インターネット文書（各種日本語コード）のシームレスな検索機能
10. 各種アプリケーションが作成したバイナリ書類内の高速検索が可能です。

### 圧縮書庫ファイルの検索には、それぞれ以下のファイルが必要です
* LZH 形式.......  （UNLHA32.DLL 必要）
* ARJ 形式.......  （UNZRJ32.DLL 必要）
* ZIP 形式.......  （UNZIP32.DLL 必要）
* CAB 形式.......  （CAB32.DLL 必要）
* TAR 形式（GNU ZIP/GZ).......（TAR32.DLL 必要）
* 各アーカイバ用DLLは、「統合アーカイバ・プロジェクト」
* http://www.madobe.net/archiver/index.html にあります。

### 各種アプリケーションが作成したバイナリ書類からのテキスト抽出
* OpenOffice.org Writer/Calc/Impress/Draw
* Open Document (text/spreadsheet/presentation/drawing documemts)
* Microsoft WORD (ver5.0/95/97/2000/Xp/2003/2007)
* Microsoft Excel (ver5.0/95/97/2000/Xp/2003/2007)
* Microsoft PowerPoint (97/2000/Xp/2003/2007)
* リッチテキスト, Windows3.1 Write, OutlookExpressエクスポート形式
* 一太郎 (ver5/ver6/ver7/ver8/9/10/11/12)
* OASYS/Win ,  新松/松5/松6 ,   Lotus 123 ,  Adobe PDF
ActiveX版のxdoc2txt（xdoc2txt.ocx）を使っています。http://www31.ocn.ne.jp/~h_ishida/xdoc2txt.html

### 各種日本語ファイルの検索には、漢字フィルターUNKANJ.DLL(拙作)が必要ですが、
これは自動的に組み込まれます。他のものより高速オプティマイズされています。


## スクリーンショット
![メイン画面]()


## 特徴
- **プラットフォーム**: Windows (Win32)
- **開発環境**: Visual Studio
- **使用技術**: MFC (Microsoft Foundation Class)
- **ビルド構成**:
  - Debug
  - Release

## 必要条件
- **開発ツール**: Visual Studio 2026最新（2019以降OK）
- **プラットフォームツールセット**: v145
- **依存プロジェクト**:
  - [MDFC](../MDFC/Mdfc.vcxproj)
  - [UnKanj](../Unkanj/UnKanj.vcxproj)

## ビルド手順
1. Visual Studioで`FileDiver.sln`を開きます。
2. 使用するビルド構成（例: Debug, Release）を選択します。
3. ソリューションをビルドします。

## ディレクトリ構成
```
FileDiver/
 ├── .vs/ # Visual Studio関連ファイル（無視されます）
 ├── Debug/ # デバッグビルド出力（無視されます）
 ├── Release/ # リリースビルド出力（無視されます）
 ├── res/ # リソースファイル
 ├── FileDiver.vcxproj # プロジェクトファイル
 ├── action.cpp
 ├── action.h
 ├── ...
 └── README.md
```

## 無視ファイル
このプロジェクトでは、`.gitignore`を使用して以下のファイルやディレクトリをGit管理から除外しています。

### Visual Studio / MSVC / MFC関連
- `.vs/`
- `*.suo`
- `*.user`
- `*.userosscache`
- `*.sln.docstates`

### IntelliSense / ブラウズ情報
- `*.VC.db`
- `*.VC.opendb`
- `*.sdf`
- `*.ipch/`
- `*.opensdf`

### ビルド成果物
- `**/Debug/`
- `**/Release/`
- `**/build/`
- `**/bin/`
- `**/obj/`
- `**/ipch/`

### コンパイラ / リンカ生成物
- `*.obj`
- `*.o`
- `*.lib`

## ライセンス
## License
This project is licensed under the zlib License - see the [LICENSE](LICENSE) file for details.
