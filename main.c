#include <stdio.h>
#include "calc.h"

int main(void)
{
    double a, b;
    char   op;

    printf("=============================\n");
    printf("   C電卓  (Git 演習プロジェクト)\n");
    printf("=============================\n");
    printf("演算子: +  -  *  /\n");
    printf("式を入力 (例: 3.5 + 2): ");

    if (scanf("%lf %c %lf", &a, &op, &b) != 3) {
        printf("入力エラー\n");
        return 1;
    }

    double result = 0;

    switch (op) {
        case '+':
            result = add(a, b);
            break;
        case '-':
            result = subtract(a, b);
            break;
        case '*':
            result = multiply(a, b);
            break;
        case '/': {
            if (divide(a, b, &result) != CALC_OK) {
                printf("エラー: ゼロで割ることはできません\n");
                return 1;
            }
            break;
        }
        default:
            printf("エラー: 不明な演算子 '%c'\n", op);
            return 1;
    }

    printf("答え: %.6g %c %.6g = %.6g\n", a, op, b, result);
    return 0;
}
