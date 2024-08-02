#include <stdlib.h>
#include <stdio.h>

int main() {
    void *mem = malloc(10);
    if (mem == NULL) {
        perror("malloc");
        return 1;
    }

    uintptr_t addr = (uintptr_t)mem;

    printf("mem: %lx\n", addr);
    printf("32で割り切れる: %s\n", (addr % 32 == 0) ? "はい" : "いいえ");
    printf("64で割り切れる: %s\n", (addr % 64 == 0) ? "はい" : "いいえ");
    printf("65で割り切れる: %s\n", (addr % 65 == 0) ? "はい" : "いいえ");

    free(mem);
    return 0;
}
