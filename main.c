#include <stdio.h>
#include <stdlib.h>

void integer_allocation() {
        printf("Hi guys!\n"
               "Let's try to allocate some memory "
               "(for an array of size 10 of int elements).\n");

        int *demo_pointer = (int *)malloc(sizeof(int) * 10);
        for (int i = 0; i < 10; i++) {
                printf("We have the memory address: %p for element  at "
                       "position: %d\n",
                       demo_pointer + sizeof(int) * i, i);
        }

        printf("We have succesfully allocated the memory.\n");
        free(demo_pointer);
}

void longlong_allocation() {
        printf("Let's try to do this for long long too.\n");
        long long *demo_pointer =
            (long long *)malloc(sizeof(long long) * 10000000000000000);

        for (long long i = 0; i < 10000000000000000; i++) {
                if (i == 0 || i == 10000000000000000 - 1) {
                        printf("We have the memory address: %p for element  at "
                               "position: %lld\n",
                               demo_pointer + sizeof(int) * i, i);
                }
        }
        printf("Now what?\n");
}

void char_allocation() {
        printf("Let's try to do this for long long too.\n");
        char *demo_pointer = (char *)malloc(sizeof(char) * 10000000000000000);

        for (long long i = 0; i < 10000000000000000; i++) {
                if (i == 0 || i == 10000000000000000 - 1) {
                        printf("We have the memory address: %p for element  at "
                               "position: %lld\n",
                               demo_pointer + sizeof(int) * i, i);
                }
        }
        printf("Now what?\n");
}

int main() {
        integer_allocation();
        // longlong_allocation();
        char_allocation();
        return 0;
}
