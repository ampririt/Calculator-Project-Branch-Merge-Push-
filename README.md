# Git 実践レッスン — C言語 電卓プロジェクトで学ぶ Branch / Merge / Push

> **対象者：** Git 初心者〜中級者  
> **使用言語：** C言語  
> **想定環境：** Linux / macOS / WSL2

---

## 📋 目次

1. [このレッスンのゴール](#1-このレッスンのゴール)
2. [プロジェクト概要](#2-プロジェクト概要)
3. [セットアップ](#3-セットアップ)
4. [ブランチ戦略の設計](#4-ブランチ戦略の設計)
5. [実践①：四則演算の実装 (feature/basic-ops)](#5-実践①四則演算の実装)
6. [実践②：割り算ゼロ除算バグ修正 (fix/division-by-zero)](#6-実践②ゼロ除算バグの修正)
7. [実践③：平方根機能の追加 (feature/sqrt)](#7-実践③平方根機能の追加)
8. [マージとコンフリクト解消](#8-マージとコンフリクト解消)
9. [GitHub に Push](#9-github-に-push)
10. [ブランチ履歴の確認](#10-ブランチ履歴の確認)
11. [チートシート](#11-チートシート)

---

## 1. このレッスンのゴール

本レッスンでは、**C言語で電卓プログラムを開発する**シナリオを通して、以下を実務に近い形で体験します。

| スキル | 内容 |
|--------|------|
| `git branch` | 機能・バグ修正ごとにブランチを切る |
| `git merge` | main への統合、コンフリクト解消 |
| `git push` | GitHub への公開、ブランチ管理 |

---

## 2. プロジェクト概要

開発する電卓プログラムの構成：

```
calculator/
├── main.c          # エントリーポイント・UI
├── calc.h          # 関数プロトタイプ宣言
├── calc.c          # 演算ロジック
├── Makefile        # ビルド設定
└── README.md
```

最終的な機能：

- ✅ 四則演算（`+` `-` `*` `/`）
- ✅ ゼロ除算エラーハンドリング
- ✅ 平方根（`sqrt`）

---

## 3. セットアップ

### 3-1. プロジェクトを初期化する

```bash
# プロジェクトディレクトリを作成
mkdir calculator && cd calculator

# Git リポジトリを初期化
git init

# 初期ファイルを作成
touch main.c calc.h calc.c Makefile README.md
```

### 3-2. 初期ファイルを書く

**`calc.h`** — ヘッダファイル（最初の骨格）

```c
#ifndef CALC_H
#define CALC_H

/* 将来の関数宣言をここに追加する */

#endif /* CALC_H */
```

**`Makefile`**

```makefile
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
TARGET  = calc
SRCS    = main.c calc.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) -lm

clean:
	rm -f $(TARGET)
```

**`README.md`**

```markdown
# Calculator — C言語 電卓

Git 実践用の電卓プロジェクトです。
```

### 3-3. 最初のコミットを作る

```bash
git add .
git commit -m "chore: プロジェクト初期化"
```

> 💡 **コミットメッセージ規約（Conventional Commits）**
>
> | プレフィックス | 用途 |
> |----------------|------|
> | `feat:` | 新機能 |
> | `fix:` | バグ修正 |
> | `chore:` | ビルド・設定変更 |
> | `docs:` | ドキュメント |
> | `refactor:` | リファクタリング |

---

## 4. ブランチ戦略の設計

実務では開発前にブランチ構成を決めます。今回はシンプルな構成を採用：

```
main          ─●──────────────────────────────●── (リリース用)
               │                              ↑
               ├─ feature/basic-ops ──●──●───┤  merge
               │                             │
               ├─ fix/division-by-zero ──●───┤  merge
               │                             │
               └─ feature/sqrt ──●──●────────┘  merge
```

- **`main`** — 常に動く状態を保つ。直接コミットしない
- **`feature/*`** — 新機能ブランチ
- **`fix/*`** — バグ修正ブランチ

---

## 5. 実践①：四則演算の実装

### Step 1 — ブランチを切る

```bash
# main が最新であることを確認
git switch main

# 機能ブランチを作成して移動
git switch -c feature/basic-ops

# 現在のブランチを確認
git branch
# * feature/basic-ops
#   main
```

### Step 2 — `calc.h` を編集する

```c
#ifndef CALC_H
#define CALC_H

/* 四則演算の関数プロトタイプ */
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);   /* ゼロ除算は後で対応 */

#endif /* CALC_H */
```

```bash
git add calc.h
git commit -m "feat: calc.h に四則演算のプロトタイプを追加"
```

### Step 3 — `calc.c` を実装する

```c
/* calc.c — 演算ロジック */
#include "calc.h"

double add(double a, double b)      { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b)   { return a / b; }  /* TODO: ゼロ除算未対応 */
```

```bash
git add calc.c
git commit -m "feat: 四則演算の実装を追加 (calc.c)"
```

### Step 4 — `main.c` を書く

```c
/* main.c — ユーザーインターフェース */
#include <stdio.h>
#include "calc.h"

int main(void) {
    double a, b;
    char op;

    printf("=== C電卓 v1.0 ===\n");
    printf("式を入力 (例: 3.5 + 2): ");
    scanf("%lf %c %lf", &a, &op, &b);

    double result;
    switch (op) {
        case '+': result = add(a, b);      break;
        case '-': result = subtract(a, b); break;
        case '*': result = multiply(a, b); break;
        case '/': result = divide(a, b);   break;
        default:
            printf("エラー: 不明な演算子 '%c'\n", op);
            return 1;
    }

    printf("結果: %.6g\n", result);
    return 0;
}
```

```bash
git add main.c
git commit -m "feat: main.c に対話型UIを実装"
```

### Step 5 — ビルドして動作確認

```bash
make
./calc
# === C電卓 v1.0 ===
# 式を入力 (例: 3.5 + 2): 10 + 3
# 結果: 13
```

```bash
# 問題なければコミット
git add Makefile
git commit -m "chore: Makefile を更新"
```

### Step 6 — main にマージ

```bash
git switch main
git merge --no-ff feature/basic-ops -m "feat: 四則演算機能を main にマージ"
```

実行結果イメージ：

```
Merge made by the 'ort' strategy.
 calc.c | 6 ++++++
 calc.h | 8 ++++++++
 main.c | 26 ++++++++++++++++++++++++++
 3 files changed, 40 insertions(+)
```

```bash
# マージ済みブランチを削除
git branch -d feature/basic-ops
```

---

## 6. 実践②：ゼロ除算バグの修正

### バグの発見

```bash
./calc
# 式を入力: 5 / 0
# 結果: inf          ← 💥 バグ！エラーにすべき
```

### Step 1 — バグ修正ブランチを作る

```bash
git switch main
git switch -c fix/division-by-zero
```

### Step 2 — `calc.h` にエラーコードを追加

```c
#ifndef CALC_H
#define CALC_H

/* エラーコード */
#define CALC_OK    0
#define CALC_ERROR 1

/* 四則演算 */
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
int    divide(double a, double b, double *result);   /* 戻り値をエラーコードに変更 */

#endif /* CALC_H */
```

```bash
git add calc.h
git commit -m "fix: divide() をエラーコード返却型に変更 (calc.h)"
```

### Step 3 — `calc.c` を修正する

```c
#include "calc.h"

double add(double a, double b)      { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }

/* ゼロ除算ガード付き */
int divide(double a, double b, double *result) {
    if (b == 0.0) {
        return CALC_ERROR;   /* エラーを返す */
    }
    *result = a / b;
    return CALC_OK;
}
```

```bash
git add calc.c
git commit -m "fix: ゼロ除算時に CALC_ERROR を返すよう修正"
```

### Step 4 — `main.c` のエラーハンドリングを追加

```c
/* main.c の divide 部分を更新 */
case '/': {
    double res;
    if (divide(a, b, &res) != CALC_OK) {
        printf("エラー: ゼロで割ることはできません\n");
        return 1;
    }
    result = res;
    break;
}
```

```bash
git add main.c
git commit -m "fix: main.c でゼロ除算エラーをハンドリング"
```

### Step 5 — 修正を確認してマージ

```bash
make
./calc
# 式を入力: 5 / 0
# エラー: ゼロで割ることはできません  ← ✅ 修正完了
```

```bash
git switch main
git merge --no-ff fix/division-by-zero -m "fix: ゼロ除算バグを修正して main にマージ"
git branch -d fix/division-by-zero
```

---

## 7. 実践③：平方根機能の追加

### Step 1 — ブランチを作る

```bash
git switch main
git switch -c feature/sqrt
```

### Step 2 — `calc.h` に追加

```c
#ifndef CALC_H
#define CALC_H

#define CALC_OK    0
#define CALC_ERROR 1

double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
int    divide(double a, double b, double *result);
int    calc_sqrt(double a, double *result);   /* 追加：平方根 */

#endif /* CALC_H */
```

```bash
git add calc.h
git commit -m "feat: calc_sqrt() のプロトタイプを追加"
```

### Step 3 — `calc.c` に実装

```c
#include <math.h>
#include "calc.h"

/* ... 既存の関数 ... */

/* 負数への sqrt ガード付き */
int calc_sqrt(double a, double *result) {
    if (a < 0.0) {
        return CALC_ERROR;   /* 虚数は未対応 */
    }
    *result = sqrt(a);
    return CALC_OK;
}
```

```bash
git add calc.c
git commit -m "feat: calc_sqrt() を実装 (負数ガード付き)"
```

### Step 4 — `main.c` に `s` コマンドを追加

```c
/* ... 既存の switch の前に追加 ... */
if (op == 's') {
    /* sqrt は単項演算子なので別処理 */
    double res;
    if (calc_sqrt(a, &res) != CALC_OK) {
        printf("エラー: 負の数の平方根は計算できません\n");
        return 1;
    }
    printf("√%.6g = %.6g\n", a, res);
    return 0;
}
```

```bash
git add main.c
git commit -m "feat: main.c に sqrt コマンド (s) を追加"
```

```bash
make
./calc
# 式を入力: 9 s 0
# √9 = 3  ← ✅
```

---

## 8. マージとコンフリクト解消

### 8-1. 通常のマージ（Fast-forward / --no-ff）

```bash
git switch main
git merge --no-ff feature/sqrt -m "feat: 平方根機能を main にマージ"
git branch -d feature/sqrt
```

### 8-2. コンフリクトが発生する例

2人が同時に `calc.h` を編集した場合を再現してみます。

**ブランチ A（feature/log）で編集：**

```c
/* calc.h の末尾に追加 */
int calc_log(double a, double *result);   /* 自然対数 */
```

**ブランチ B（feature/power）で同じ行に追加：**

```c
/* calc.h の末尾に追加 */
double power(double base, double exp);   /* 累乗 */
```

**マージするとコンフリクト発生：**

```
<<<<<<< HEAD (feature/log の内容)
int calc_log(double a, double *result);
=======
double power(double base, double exp);
>>>>>>> feature/power
```

**解消方法：**

```c
/* 両方を残す形に手動で編集する */
int    calc_log(double a, double *result);
double power(double base, double exp);
```

```bash
# 解消したらステージングしてコミット
git add calc.h
git commit -m "fix: calc.h のコンフリクトを解消（log と power を両方追加）"
```

> ⚠️ **VS Code を使うと便利**  
> コンフリクト箇所が色分け表示され、「Accept Current / Accept Incoming / Accept Both」ボタンで視覚的に解消できます。

---

## 9. GitHub に Push

### 9-1. リモートリポジトリを登録

```bash
# GitHub でリポジトリ "calculator" を作成してから実行
git remote add origin https://github.com/YOUR_NAME/calculator.git

# 登録確認
git remote -v
# origin  https://github.com/YOUR_NAME/calculator.git (fetch)
# origin  https://github.com/YOUR_NAME/calculator.git (push)
```

### 9-2. main を push する

```bash
# -u で追跡設定も同時に行う（初回のみ）
git push -u origin main
```

```
Enumerating objects: 18, done.
Branch 'main' set up to track remote branch 'main' from 'origin'.
To https://github.com/YOUR_NAME/calculator.git
 * [new branch]      main -> main
```

### 9-3. 作業ブランチを push してプルリクエストを作る（実務フロー）

```bash
# ブランチごと push
git push -u origin feature/new-feature

# 2回目以降は
git push
```

GitHub 上でそのブランチの「**Compare & Pull Request**」ボタンを押してレビューを依頼します。

### 9-4. Push が拒否されたら

```
! [rejected]  main -> main (non-fast-forward)
```

他の人がすでに push していた場合。解決手順：

```bash
# 1. リモートの変更を取得してリベース
git pull --rebase origin main

# 2. コンフリクトがあれば解消してから
git rebase --continue

# 3. 再 push
git push
```

> ⚠️ `git push --force` はチーム開発では原則禁止。他人のコミット履歴を破壊します。

---

## 10. ブランチ履歴の確認

```bash
# グラフ付きログ（短縮表示）
git log --oneline --graph --all
```

期待される出力イメージ：

```
*   f3a1b2c (HEAD -> main, origin/main) feat: 平方根機能を main にマージ
|\
| * 9e8d7c6 feat: main.c に sqrt コマンド (s) を追加
| * 4b3a2d1 feat: calc_sqrt() を実装
| * 1c0b9e8 feat: calc_sqrt() のプロトタイプを追加
|/
*   7a6f5e4 fix: ゼロ除算バグを修正して main にマージ
|\
| * 5d4c3b2 fix: main.c でゼロ除算エラーをハンドリング
| * 3e2d1c0 fix: ゼロ除算時に CALC_ERROR を返すよう修正
| * 1b0a9f8 fix: divide() をエラーコード返却型に変更 (calc.h)
|/
*   8c7b6a5 feat: 四則演算機能を main にマージ
|\
| * 6a5b4c3 feat: main.c に対話型UIを実装
| * 4c3b2a1 feat: 四則演算の実装を追加 (calc.c)
| * 2a1b0c9 feat: calc.h に四則演算のプロトタイプを追加
|/
* 0f9e8d7 chore: プロジェクト初期化
```

---

## 11. チートシート

### ブランチ操作

| コマンド | 説明 |
|----------|------|
| `git switch -c feature/xxx` | ブランチ作成＆移動 |
| `git switch main` | main に移動 |
| `git branch` | ブランチ一覧（`*` が現在地） |
| `git branch -d feature/xxx` | マージ済みブランチを削除 |
| `git branch -D feature/xxx` | 強制削除 |

### マージ

| コマンド | 説明 |
|----------|------|
| `git merge --no-ff feature/xxx` | マージコミットを作成 |
| `git merge --abort` | マージを中断して戻す |
| `git add . && git commit` | コンフリクト解消後のコミット |

### Push / Pull

| コマンド | 説明 |
|----------|------|
| `git push -u origin main` | 初回 push（追跡設定付き） |
| `git push` | 2回目以降 |
| `git pull --rebase` | リモートの変更を取得してリベース |
| `git remote -v` | リモート URL を確認 |

### ログ確認

| コマンド | 説明 |
|----------|------|
| `git log --oneline --graph --all` | グラフ付き全ブランチ履歴 |
| `git status` | 現在の変更状態 |
| `git diff` | 未ステージの変更を確認 |

---

## 🎓 まとめ

今回のレッスンで学んだこと：

1. **機能・修正ごとにブランチを切る** → main を常に安全な状態に保つ
2. **こまめにコミットする** → 変更の意図が履歴に残る
3. **`--no-ff` でマージ** → ブランチの存在が履歴に残り追跡しやすい
4. **コンフリクトは慌てない** → ファイルを手動で編集 → `git add` → `git commit`
5. **`git push -u` で追跡設定** → 2回目以降は `git push` だけで OK

> **次のステップ：** `git rebase`、`git stash`、`git cherry-pick`、GitHub Actions による自動ビルド

---

*Generated for Git 実践レッスン — C言語 電卓プロジェクト*
