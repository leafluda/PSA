#include <stdio.h>

void myscanf(char* format, void* data) {
    char c;
    int* int_ptr;
    float* float_ptr;
    char* char_ptr;
    char* string_ptr;

    switch (*format) {
    case '%':
        switch (*(format + 1)) {
        case 'd':
            int_ptr = (int*)data;
            *int_ptr = 0;
            while ((c = getchar()) == ' ' || c == '\t' || c == '\n');
            while (c >= '0' && c <= '9') {
                *int_ptr = *int_ptr * 10 + c - '0';
                c = getchar();
            }
            ungetc(c, stdin);
            break;
        case 'f':
            float_ptr = (float*)data;
            *float_ptr = 0;
            while ((c = getchar()) == ' ' || c == '\t' || c == '\n');
            while (c >= '0' && c <= '9') {
                *float_ptr = *float_ptr * 10 + c - '0';
                c = getchar();
            }
            if (c == '.') {
                float decimal = 0.1;
                c = getchar();
                while (c >= '0' && c <= '9') {
                    *float_ptr += decimal * (c - '0');
                    decimal /= 10;
                    c = getchar();
                }
            }
            ungetc(c, stdin);
            break;
        case 'c':
            char_ptr = (char*)data;
            while ((c = getchar()) == ' ' || c == '\t' || c == '\n');
            *char_ptr = c;
            break;
        case 's':
            string_ptr = (char*)data;
            while ((c = getchar()) == ' ' || c == '\t' || c == '\n');
            while (c != ' ' && c != '\t' && c != '\n' && c != EOF) {
                *string_ptr++ = c;
                c = getchar();
            }
            ungetc(c, stdin);
            *string_ptr = '\0';
            break;
        }
        break;
    default:
        while ((c = getchar()) != *format && c != EOF);
        if (c == EOF) {
            return;
        }
        break;
    }
}

int main() {
    int x;
    float y;
    char c;
    char str[100];

    myscanf("%d", &x);
    printf("x: %d\n", x);

    myscanf("%f", &y);
    printf("y: %f\n", y);

    myscanf("%c", &c);
    printf("c: %c\n", c);

    myscanf("%s", str);
    printf("str: %s\n", str);

    return 0;
}
