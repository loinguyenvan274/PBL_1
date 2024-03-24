#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void d_cArray(char** array, char* character) {
    static int count_dArray = 0;
    int characterLength = strlen(character);
    if (count_dArray == 0) {
        count_dArray = characterLength + 1; // Bao gồm cả ký tự null kết thúc chuỗi
        *array = (char*)malloc(count_dArray * sizeof(char));
        strcpy(*array, character); // Sao chép chuỗi character vào vùng nhớ mới
    } else {
        int arrayLength = strlen(*array);
        count_dArray += characterLength;
        *array = realloc(*array, count_dArray * sizeof(char));
        memcpy(*array + arrayLength, character, characterLength + 1); // Sao chép chuỗi character vào cuối *array
    }
}

int main() {
    char a[44] = "54";
    // char *b = :
    strcat(a,"4");
    printf("%s",a);
    return 0;
}
