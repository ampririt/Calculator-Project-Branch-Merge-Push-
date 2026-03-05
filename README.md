# 🧮 Git 演習 — C言語 電卓プロジェクト

> 2人1組  
> ゴール：**ブランチ作成 → コミット → main へマージ** を体験する

---

## 📁 ファイル構成

```
calculator/
├── main.c      ← 触らない（完成済み）
├── calc.h      ← 触らない（完成済み）
├── calc.c      ← ✏️ 2人で分担して実装する
├── Makefile    ← 触らない
└── README.md   ← このファイル
```

---

## 🎯 演習の流れ（全体像）

```
GitHub Classroom でリポジトリを受け取る（2人で1つ）
        │
        ├─ 担当A
        │   git switch -c feature/add-subtract
        │   add() と subtract() を実装
        │   git commit & git push
        │
        └─ 担当B
            git switch -c feature/mul-divide
            multiply() と divide() を実装
            git commit & git push

        ↓ 2人とも push できたら

    どちらか1人が main にマージ × 2回
        │
        └─ make で全演算が動けば完成 🎉
```

---

## 演習手順

### 🔧 Step 0 — リポジトリを受け取る

GitHub Classroom の招待リンクを開き、チームに参加します。  
チームのリポジトリが自動作成されたら：

```bash
git clone https://github.com/<ORG>/<REPO_NAME>.git
cd <REPO_NAME>
```

---

### 👤 担当A の手順 — `add` と `subtract`

#### 1. ブランチを作る

```bash
git switch -c feature/add-subtract
```

#### 2. `calc.c` を編集する

`add()` と `subtract()` の `/* TODO */` を実装します：

```c
double add(double a, double b)
{
    return a + b;  /* ← 実装する */
}

double subtract(double a, double b)
{
    return a - b;  /* ← 実装する */
}
```

> ⚠️ `multiply()` と `divide()` は **触らない**こと

#### 3. ビルドして確認

```bash
make
./calc
# 式を入力: 10 + 3
# 答え: 10 + 3 = 13  ✅
```

#### 4. コミットして push

```bash
git add calc.c
git commit -m "feat: add と subtract を実装"
git push -u origin feature/add-subtract
```

---

### 👤 担当B の手順 — `multiply` と `divide`

#### 1. ブランチを作る

```bash
git switch -c feature/mul-divide
```

#### 2. `calc.c` を編集する

`multiply()` と `divide()` の `/* TODO */` を実装します：

```c
double multiply(double a, double b)
{
    return a * b;  /* ← 実装する */
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

> ⚠️ `add()` と `subtract()` は **触らない**こと

#### 3. ビルドして確認

```bash
make
./calc
# 式を入力: 6 * 7
# 答え: 6 * 7 = 42  ✅

./calc
# 式を入力: 5 / 0
# エラー: ゼロで割ることはできません  ✅
```

#### 4. コミットして push

```bash
git add calc.c
git commit -m "feat: multiply と divide を実装（ゼロ除算ガード付き）"
git push -u origin feature/mul-divide
```

---

### 🤝 2人で行う：main へマージ

両方の push が完了したら、どちらか 1人が以下を実行します。

#### マージ①（担当Aのブランチ）

```bash
git switch main
git pull                                  # 最新の main を取得
git merge --no-ff feature/add-subtract \
    -m "feat: add と subtract を main にマージ"
```

#### マージ②（担当Bのブランチを取得してマージ）

```bash
git fetch origin feature/mul-divide
git merge --no-ff origin/feature/mul-divide \
    -m "feat: multiply と divide を main にマージ"
```

#### ⚠️ コンフリクトが出たら（学習チャンス！）

同じ `calc.c` を2人が編集しているので、2回目のマージでコンフリクトが出ることがあります。

```
<<<<<<< HEAD
    return a + b;
=======
    return a * b;
>>>>>>> origin/feature/mul-divide
```

**解消手順：**

```bash
# 1. ファイルを開いて <<<, ===, >>> を消し、両方の実装を残す
# 2. ステージング
git add calc.c
# 3. コミット
git commit -m "fix: コンフリクト解消 — 全演算を統合"
```

#### 最後に push して完成！

```bash
git push origin main
```

---

### ✅ 動作確認（全演算テスト）

```bash
make
./calc   # 10 + 3  → 13
./calc   # 10 - 3  → 7
./calc   # 6 * 7   → 42
./calc   # 15 / 3  → 5
./calc   # 5 / 0   → エラー: ゼロで割ることはできません
```

全部通れば 🎉 **演習完了！**

---

## 🆘 トラブルシューティング

### `make` でエラーが出る

```
calc.c:10: error: ...
```
→ `calc.c` の `{}` や `;` の書き忘れを確認してください。

### `git push` が拒否される

```
! [rejected] ... (fetch first)
```
→ パートナーがすでに push しています。

```bash
git pull --rebase origin feature/add-subtract
git push
```

### 間違ったブランチで作業してしまった

```bash
git stash                              # 変更を一時退避
git switch feature/add-subtract        # 正しいブランチへ
git stash pop                          # 変更を復元
```

---

## 📋 チェックリスト（確認）

- [ ] 担当ブランチ名が正しい（`feature/add-subtract` or `feature/mul-divide`）
- [ ] 担当の関数だけを実装した（他の関数を触っていない）
- [ ] `make` がエラーなく通る
- [ ] コミットメッセージが書いてある
- [ ] `git push` が成功した
- [ ] main へのマージが完了した
- [ ] 全演算（`+ - * /` とゼロ除算）が正しく動く
