#include <unistd.h>
#include <utils.h>

int exists(char *path) {
    if (access(path, R_OK | W_OK) == 0)
        return 1;
    else
        return 0;
}

void input(char *buf, char *prompt, int num) {
    if (!strchr(buf, '\n'))
        while (getchar() != '\n')
            ;
    printf("%s", prompt);
    fgets(buf, num + 1, stdin);
}

char *readFile(char *path) {
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL) {
        printf("Could not open file %s. Terminating.", path);
        fclose(fptr);
        exit(-1);
    }
    fseek(fptr, 0L, SEEK_END);
    long int size = ftell(fptr);
    fseek(fptr, 0L, SEEK_SET);
    char *contents = malloc(size + 1);
    fread(contents, 1, size, fptr);
    fclose(fptr);
    contents[size] = '\0';
    return contents;
}

void writeFile(char *str, char *path) {
    FILE *fptr = fopen(path, "w");
    if (fptr == NULL) {
        printf("Could not open file %s. Terminating.", path);
        fclose(fptr);
        exit(-1);
    }
    fwrite(str, 1, sizeof(str) - 1, fptr);
    fclose(fptr);
}
