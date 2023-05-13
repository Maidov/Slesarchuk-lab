#include <stdio.h>

typedef struct row {
    int key;
    int value;
} row;

int Max(int a, int b) {
    return a > b ? a : b;
}

void DisplayTable(row* table, int size){
    printf("\n");
    printf("|   KEY   |   VALUE  |\n----------------------\n");
    for (int i = 0; i < size; i++){
        printf("|    %d    |     %d    |\n", table[i].key, table[i].value);
    }
}

void Swap(row* table, int intdex1, int intdex2){
    int bufKey = table[intdex1].key;
    int bufVal = table[intdex1].value;
    
    table[intdex1].key = table[intdex2].key;
    table[intdex1].value = table[intdex2].value;
    table[intdex2].key = bufKey;
    table[intdex2].value = bufVal;
}

void heapify(row* table, int size, int i){
    int lrg = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if ((lrg < size) && (table[i].key < table[left].key)){
        lrg = left;
    }
    if ((right < size) && (table[i].key < table[right].key)){
        lrg = right;
    }
    if (lrg != i){
        Swap(table, lrg, i);
        heapify(table, size, lrg);
    }
}

void Staff(row* table, int i, int currentSize){
    while (1) {
        int right = i * 2 + 2;
        int left = i * 2 + 1;
        if (Max(right, left) < currentSize) {
            if (table[i].key >= Max(table[right].key, table[left].key)){
                break;
            }
            else if (table[right].key > table[left].key){
                Swap(table, right, i);
                i = right;
            } else {
                Swap(table, left, i);
                i = left;
            }
        }
        else if (left < currentSize) {
            if (table[left].key > table[i].key){
                Swap(table, i, left);
                i = left;
            } else {
                break;
            }
        }
        else if (right < currentSize) {
            if (table[right].key > table[i].key){
                Swap(table, i, right);
                i = right;
            } else {
                break;
            }
        } else {
            break;
        }
    }
}

void UpsideDownFloppyDoppy(row* table, int size){
    for (int i = (size - 2) / 2; i > -1; i--) {
        Staff(table, i, size);
    }
    
    for (int i = size - 1; i > -1; i--) {
        Swap(table, 0, i);
        Staff(table, 0, i);
    }
}

int BinSearch(row* table, int key, int size) {
    int right = size, left = -1;
    while (left + 1 < right) {
        int mid = (right + left) / 2;
        if (table[mid].key == key) {
            printf("\nУ данного ключа значение: %d\n", table[mid].value);
            return 0;
        }
        if (table[mid].key < key) {
            left = mid;
        } else {
            right = mid;
        }
    }
    printf("Нет такого ключа\n");
    return 1;
}

int main() {
    printf("Введите размер таблицы: ");
    int size;
    scanf("%d", &size);
    row table[size];
    printf("Вводите пары ключ значение: \n");
    for (int i = 0; i < size; i++) {
        scanf("%d %d", &table[i].key, &table[i].value);
    }
    DisplayTable(table, size);
    
    UpsideDownFloppyDoppy(table, size);
    
    DisplayTable(table, size);
    
    while(1){
        printf("Введите ключ для поиска: ");
        int sKey;
        scanf("%d", &sKey);
        BinSearch(table, sKey, size);
    }
    putchar('\n');
}