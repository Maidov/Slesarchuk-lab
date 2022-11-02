#include <stdio.h>

#define maxN 100

int CustomGrade(int a, int b) {
  int result = 1;

  for (int i = 0; i < b; i++) {
    result *= a;
  }
  return result;
}




int main() {
  int lambda, dForDelta, matrix[maxN * maxN], n;

  //Ввод данных
  scanf("%i", &n);

  for (int i = 0; i != n*n; ++i) {
      scanf("%d", &matrix[i]);
  }

  /*
  // Вывод матрицы
  putchar('\n');
  for (int i = 0; i != n*n; ++i) {
     printf("%d ", matrix[i]);

     if (!((i + 1) % n)) {
       printf("\n");
     }
  }
  */

  int alfa = n - 1, current = (n * n) - 1;

  // Первая часть
  printf("\n%d\n", matrix[current]);

  for (int i = 0; i < alfa; i++) {  
    lambda = i + 1;
    dForDelta = CustomGrade(-1, i);

    if (dForDelta > 0) {
      current -= 1;
    } else {
      current -= n;
    }

    printf("%d\n", matrix[current]);

    for (int i = 0; i < lambda; i++) {  
      current = current - alfa * dForDelta;
      printf("%d\n", matrix[current]);
    }
  }

  //Вторая часть
  for (int i = alfa; 0 < i; i--) {
    lambda = i - 1;

    if (dForDelta > 0) {
      current -= 1;
    } else {
      current -= n;
    }

    printf("%d\n", matrix[current]);

    for (int i = 0; i < lambda; i++) {
      current = current - alfa * dForDelta * (-1);
      printf("%d\n", matrix[current]);
    }
    dForDelta = CustomGrade(-1, i);
  }
  putchar('\n');
}
