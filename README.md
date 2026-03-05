# 🧮 Git 演習プロジェクト — C言語 電卓
 2人1組 × 複数グループ

---

## 📁 リポジトリ構成

```
calculator/
├── main.c      
├── calc.h      
├── calc.c     
├── Makefile    
└── README.md
```

---

## 👩‍🎓 演習手順

### 🔧 準備

```bash
# リポジトリをクローン
git clone https://github.com/YOUR_NAME/calculator.git
cd calculator

# ファイルを確認
ls
# Makefile  README.md  calc.c  calc.h  main.c
```

---

### 📌 A班の手順 — `add` と `subtract` を実装する

#### 1. ブランチを作る

```bash
git switch -c feature/group-A-add-subtract
git branch
# * feature/group-A-add-subtract
#   main
```

#### 2. `calc.c` を編集する

`calc.c` を開き、`add()` と `subtract()` の `TODO` 部分を実装します：

```c
double add(double a, double b)
{
    return a + b;   /* ← ここを実装 */
}

double subtract(double a, double b)
{
    return a - b;   /* ← ここを実装 */
}
```

> B班の `multiply()` と `divide()` は **触らない**こと！

#### 3. ビルドして確認

```bash
make
./calc
# 式を入力: 10 + 3
# 答え: 10 + 3 = 13   ← ✅
```

#### 4. コミットする

```bash
git add calc.c
git commit -m "feat: add() と subtract() を実装"
```

#### 5. GitHub に push する

```bash
git push -u origin feature/group-A-add-subtract
```

---

### 📌 B班の手順 — `multiply` と `divide` を実装する

#### 1. ブランチを作る

```bash
git switch -c feature/group-B-mul-divide
git branch
# * feature/group-B-mul-divide
#   main
```

#### 2. `calc.c` を編集する

`multiply()` と `divide()` の `TODO` 部分を実装します：

```c
double multiply(double a, double b)
{
    return a * b;   /* ← ここを実装 */
}

int divide(double a, double b, double *result)
{
    if (b == 0.0) {
        return CALC_ERROR;   /* ゼロ除算ガード！ */
    }
    *result = a / b;
    return CALC_OK;
}
```

> A班の `add()` と `subtract()` は **触らない**こと！

#### 3. ビルドして確認

```bash
make
./calc
# 式を入力: 6 * 7
# 答え: 6 * 7 = 42   ← ✅

./calc
# 式を入力: 5 / 0
# エラー: ゼロで割ることはできません   ← ✅
```

#### 4. コミットする

```bash
git add calc.c
git commit -m "feat: multiply() と divide() を実装（ゼロ除算ガード付き）"
```

#### 5. GitHub に push する

```bash
git push -u origin feature/group-B-mul-divide
```

---

### 🔀 代表者がマージする

両班が push を完了したら、教師が main にマージします。

```bash
# 最新の main を取得
git switch main
git pull

# A班のブランチをマージ
git fetch origin feature/group-A-add-subtract
git merge --no-ff origin/feature/group-A-add-subtract \
    -m "feat: A班 — add/subtract を main にマージ"

# B班のブランチをマージ
git fetch origin feature/group-B-mul-divide
git merge --no-ff origin/feature/group-B-mul-divide \
    -m "feat: B班 — multiply/divide を main にマージ"
```

> ⚠️ **コンフリクトが発生する場合（学習チャンス！）**
>
> A班とB班が `calc.c` の同じファイルを編集しているため、  
> 2つ目のマージでコンフリクトが発生することがあります。
>
> ```
> <<<<<<< HEAD
>     return a + b;
> =======
>     return a * b;  ← B班の変更
> >>>>>>> origin/feature/group-B-mul-divide
> ```
>
> **解消手順：**
> ```bash
> # 1. エディタで両方の変更を残す形に修正
> # 2. ステージング
> git add calc.c
> # 3. コンフリクト解消コミット
> git commit -m "fix: A班・B班のコンフリクトを解消"
> ```

#### マージ後の動作確認

```bash
make
./calc
# 式を入力: 3 + 4     → 答え: 7
# 式を入力: 10 - 3    → 答え: 7
# 式を入力: 6 * 7     → 答え: 42
# 式を入力: 15 / 3    → 答え: 5
# 式を入力: 5 / 0     → エラー: ゼロで割ることはできません
```

#### main を push して完成！

```bash
git push origin main
```

---

## 📊 演習フロー図

```
GitHub (origin/main)
        │
        ├── git clone  ← 全員がここから始める
        │
        ├── A班
        │   └── feature/group-A-add-subtract
        │       ├── add() を実装
        │       ├── subtract() を実装
        │       ├── git commit
        │       └── git push ──────────────────┐
        │                                       │
        ├── B班                                 │
        │   └── feature/group-B-mul-divide      │
        │       ├── multiply() を実装            │
        │       ├── divide() を実装              │
        │       ├── git commit                  │
        │       └── git push ──────────┐        │
        │                              ▼        ▼
        │                    両ブランチを main にマージ
        │                              │
        └──────────────────────────────▼
                          origin/main (完成！🎉)
```

---

## ✅ 採点チェックリスト

| 確認項目 | A班 | B班 |
|---------|-----|-----|
| 正しいブランチ名で作業した | ☐ | ☐ |
| 担当関数だけを編集した | ☐ | ☐ |
| `make` がエラーなく通る | ☐ | ☐ |
| コミットメッセージが適切 | ☐ | ☐ |
| `git push` が成功した | ☐ | ☐ |
| B班: ゼロ除算でエラーが出る | — | ☐ |

---

## 🆘 よくあるトラブル

### `make` でコンパイルエラーが出る

```bash
calc.c:10:5: error: ...
```

→ `calc.c` の構文を確認。`;` の付け忘れや `{}` の対応ミスが多いです。

### `git push` が拒否される

```
! [rejected] ... (fetch first)
```

→ 誰かがすでに push しています。

```bash
git pull --rebase origin feature/group-A-add-subtract
git push
```

### ブランチを間違えて作業した

```bash
# 正しいブランチに移動して、変更を持ち越す
git stash
git switch feature/group-A-add-subtract
git stash pop
```

---

*演習リポジトリ — Git Branch/Merge 実践 (C言語 電卓プロジェクト)*
