#include "calc.h"

/* ============================================================
 *  このファイルに演算関数を実装してください。
 *  担当はブランチ名で確認してください。
 *    Group A → feature/group-A-add-subtract
 *    Group B → feature/group-B-mul-divide
 * ============================================================ */

/* --- Group A の担当 ---------------------------------------- */

/* add(): a と b の和を返す */
double add(double a, double b)
{
    /* TODO: ここを実装する */
    return 0;
}

/* subtract(): a から b を引いた差を返す */
double subtract(double a, double b)
{
    /* TODO: ここを実装する */
    return 0;
}

/* --- Group B の担当 ---------------------------------------- */

/* multiply(): a と b の積を返す */
double multiply(double a, double b)
{
    /* TODO: ここを実装する */
    return 0;
}

/* divide(): a ÷ b を計算して *result に格納する
 * b == 0 のとき CALC_ERROR を返すこと
 * 成功時は CALC_OK を返すこと                */
int divide(double a, double b, double *result)
{
    /* TODO: ここを実装する (ゼロ除算ガードを忘れずに!) */
    *result = 0;
    return CALC_OK;
}
