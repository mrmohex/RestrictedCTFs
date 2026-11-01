
#include <stdio.h>
#include <string.h>

int main(void) {
    char input[256];
    char real[256];

    FILE *fp = fopen("/root/secret/root.txt", "r");

    if (!fp) {
        puts("Unable to read flag.");
        return 1;
    }

    if (!fgets(real, sizeof(real), fp)) {
        fclose(fp);
        return 1;
    }
    fclose(fp);

    real[strcspn(real, "\n")] = '\0';

    printf("\nEnter flag: ");

    if (!fgets(input, sizeof(input), stdin))
        return 1;

    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, real) == 0) {
        printf("\033[1;32m");
        puts("");
        puts("  ╔══════════════════════════════════════╗");
        puts("  ║                                      ║");
        puts("  ║          ACCESS GRANTED              ║");
        puts("  ║                                      ║");
        puts("  ║  ██████╗ ██╗    ██╗███╗   ██╗        ║");
        puts("  ║  ██╔══██╗██║    ██║████╗  ██║        ║");
        puts("  ║  ██████╔╝██║ █╗ ██║██╔██╗ ██║        ║");
        puts("  ║  ██╔═══╝ ██║███╗██║██║╚██╗██║        ║");
        puts("  ║  ██║     ╚███╔███╔╝██║ ╚████║        ║");
        puts("  ║  ╚═╝      ╚══╝╚══╝ ╚═╝  ╚═══╝        ║");
        puts("  ║                                      ║");
        puts("  ║       PWNED! CHALLENGE SOLVED        ║");
        puts("  ║       RESPECT, HACKER.               ║");
        puts("  ║                                      ║");
        puts("  ╚══════════════════════════════════════╝");
        puts("");
        printf("\033[0m");
    } else {
        printf("\033[1;31m");
        puts("\n  [!] ACCESS DENIED");
        puts("  [-] Invalid flag. Keep hacking!\n");
        printf("\033[0m");
    }

    return 0;
}
