#include <stdio.h>

#define MAX_N 7

int CustomPow(int a, int b) {
    int result = 1;

    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

int main() {
    int lambda, dForDelta, matrix[MAX_N][MAX_N], n;

    //Ввод данных
    scanf("%i", &n);

    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j)
            scanf("%d", &matrix[i][j]);
    }
    int alfa = n - 1, currentX = alfa, currentY = alfa;

    // Первая часть
    printf("\n%d ", matrix[currentY][currentX]);

    for (int i = 0; i < alfa; i++) {
        lambda = i + 1;
        dForDelta = CustomPow(-1, i);

        if (dForDelta > 0) {
            currentX -= 1;
        } else {
            currentY -= 1;
        }
        printf("%d ", matrix[currentY][currentX]);

        for (int i = 0; i < lambda; i++) {
            currentX = currentX + dForDelta;
            currentY = currentY - dForDelta;
            printf("%d ", matrix[currentY][currentX]);
        }
    }
    
    //Вторая часть
    for (int i = alfa; 0 < i; i--) {
        lambda = i - 1;
        if (dForDelta > 0) {
            currentX -= 1;
        } else {
            currentY -= 1;
        }
        printf("%d ", matrix[currentY][currentX]);

        for (int i = 0; i < lambda; i++) {
            currentX = currentX + dForDelta * (-1);
            currentY = currentY - dForDelta * (-1);
            printf("%d ", matrix[currentY][currentX]);
        }
        dForDelta = CustomPow(-1, i);
    }
    putchar('\n');
}
