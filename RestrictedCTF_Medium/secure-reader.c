
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    char path[PATH_MAX];
    char buffer[1024];

    if (argc != 2) {
        fprintf(stderr, "Usage: secure-reader <filename>\n");
        return 1;
    }

    const char *filename = argv[1];

    size_t len = strlen(filename);

    if (len == 0 || len > 100) {
        fprintf(stderr, "Invalid filename.\n");
        return 1;
    }

    if (strcmp(filename, ".") == 0 ||
        strcmp(filename, "..") == 0) {
        fprintf(stderr, "Invalid filename.\n");
        return 1;
    }

    for (size_t i = 0; i < len; i++) {
        if (!isalnum((unsigned char)filename[i]) &&
            filename[i] != '.' &&
            filename[i] != '_' &&
            filename[i] != '-') {
            fprintf(stderr, "Invalid filename.\n");
            return 1;
        }
    }

    snprintf(path, sizeof(path), "/opt/data/%s", filename);

    int fd = open(path, O_RDONLY);

    if (fd < 0) {
        perror("Unable to open file");
        return 1;
    }

    printf("--- File Contents ---\n");

    ssize_t bytes;

    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) {
        if (fwrite(buffer, 1, bytes, stdout) != (size_t)bytes) {
            perror("Output error");
            close(fd);
            return 1;
        }
    }

    if (bytes < 0) {
        perror("Read error");
        close(fd);
        return 1;
    }

    printf("\n");

    close(fd);
    return 0;
}
