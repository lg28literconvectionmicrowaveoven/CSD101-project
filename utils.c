#include <unistd.h>
#include <utils.h>

int exists(char *path) {
    if (access(path, R_OK | W_OK) == 0)
        return 1;
    else
        return 0;
}
