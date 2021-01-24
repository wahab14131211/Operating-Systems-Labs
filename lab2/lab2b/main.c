#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_REPS 50
#define DEFAULT_SLOWDOWN 10000

int main(int argc, char * argv[]) {
    int i;
    int slow_down = DEFAULT_SLOWDOWN;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s string [delay]\n", argv[0]);
        return 1;
    }
    if (argc >= 3) {
        slow_down = atoi(argv[2]);
    }

    for (i = 0; i < N_REPS; i++) {
        char * cp = argv[1];

        while (*cp) {
            printf("%c", *cp++);
            fflush(stdout);
            usleep(random() % slow_down);
        }
        usleep(5000);
    }
    return EXIT_SUCCESS;
}