#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char surname[15];
    char initial[4];
    char gender[1];
    char groupNum[2];
    char sub1[1];
    char sub2[1];
    char sub3[1];
} student;

int main(void) {
    FILE* fp = fopen("students2.csv", "r");
    FILE* out = fopen("students.bin", "w");
 
    if (!fp)
        printf("Can't open file\n");
 
    else {
        int n = 100;
        char buffer[n];
        int row = 0;
        int column = 0;
        while (fgets(buffer,
                     n, fp)) {
            column = 0;
            ++row;
            if (row == 1)
                continue;
            student* s = (student*) malloc (sizeof(student));
            int index = 0;
            for (int i = 0; i < n; ++i) {
                if (buffer[i] == '\n') {
                    break;
                }
                if (buffer[i] == ',') {
                    ++column;
                    index = 0;
                    continue;
                }
                if (column == 0) {
                    s -> surname[index] = buffer[i];
                }
                if (column == 1) {
                    s -> initial[index] = buffer[i];
                }
                if (column == 2) {
                    s -> gender[index] = buffer[i];
                }
                if (column == 3) {
                    s -> groupNum[index] = buffer[i];
                }
                if (column == 4) {
                    s -> sub1[index] = buffer[i];
                }
                if (column == 5) {
                    s -> sub2[index] = buffer[i];
                }
                if (column == 6) {
                    s -> sub3[index] = buffer[i];
                    break;
                }
                ++index;
            }
            fwrite(s, sizeof(student), 1, out);
        }
        fclose(fp);
        fclose(out);
        FILE* in = fopen("students.bin", "r");
        student* s = (student*) malloc (sizeof(student));
        int count = 0;
        while (fread(s, sizeof(student), 1, in) == 1) {
            if ((s -> sub1[0] != s -> sub2[0]) && (s -> sub1[0] != s -> sub3[0]) && (s -> sub2[0] != s -> sub3[0])) {
                ++count;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}
