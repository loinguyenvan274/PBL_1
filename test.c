#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void d_cArray(char** array, char* character, int Size) {
    static int count_dArray = 0;
    if (count_dArray == 0) {
        count_dArray = Size;
        *array = (char*)malloc(count_dArray * sizeof(char));
    } else {
        count_dArray += Size;
        *array = realloc(*array, count_dArray * sizeof(char));
    }
    strcat(*array, character);
}

int main() {
    char* b = NULL; // Khởi tạo con trỏ b với giá trị NULL
    char a[] = "hello anh em ";
    printf("%d\n",)
    d_cArray(&b, a, sizeof(a));
    printf("%s", b);
    strcpy(a, "bach khoa");
    d_cArray(&b, a, sizeof(a));
    printf("%s", b);

    free(b); // Giải phóng bộ nhớ sau khi không cần thiết nữa
    return 0;
}
