#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int hasEmptySpot(long int **c, int set, int E) {
    int s = (set * E);
    int i;
    for (i = s; i < s + E; i++) {
        if (c[i][0] == 0) {
            return i;
        }
    }
    return -1;
}

void incrementAge(long int **c, int set, int E) {
    int s = (set * E);
    int i;
    for (i = s; i < s + E; i++) {
        if (c[i][0] == 1) {
            c[i][2] += 1;
        }
    }
}

int getOldestIndex(long int **c, int set, int E) {
    int s = (set * E);
    int i, max = 0, index = -1;
    for (i = s; i < s + E; i++) {
        if (c[i][0] == 1 && c[i][2] > max) {
            max = c[i][2];
            index = i;
        }
    }
    return index;
}

void store(long int **c, int set, int E, long int tag, int method) {
    int empty = hasEmptySpot(c, set, E);
    incrementAge(c, set, E);
    if (empty != -1) {
        c[empty][0] = 1;
        c[empty][1] = tag;
    }
    //method 0 = lru, 1 = fifo
    else if (method) {
        int i = getOldestIndex(c, set, E);
        c[i][0] = 1;
        c[i][1] = tag;
        c[i][2] = 0;
    }
}

int search(long int **c, int set, int E, long int tag) {
    int s = (set * E);
    int i;
    for (i = s; i < s + E; i++) {
        if (c[i][0] == 1 && c[i][1] == tag) {
            return 1;
        }
    }
    return 0;
}

void printCache(long int **c, int S) {
    int i;
    for (i = 0; i < S; i++) {
        printf("[%lx, %lx, %lx]\n", c[i][0], c[i][1], c[i][2]);
    }
}

int isPower2(int n) {
    return ceil(log2(n)) == floor(log2(n));
}

int main(int argc, char **argv) {
    if (argc - 1 != 6) {
        printf("Invalid number of arguments\n");
        return 0;
    }

    int C = atoi(argv[1]); 
    int B = atoi(argv[5]); 
    int E = 0;
    int S = 0;
    int b = 0, s = 0;
    int pre = 0, re = 0;
    int reads = 0, writes = 0;
    int hits = 0, misses = 0;
    long int addr = 0;
    char op;
    long int **cache;

    if (strcmp(argv[2], "direct") == 0) {
        E = 1;
        S = C / (B * E);
        b = log2(B);
        s = log2(S);
    }
    else if (strstr(argv[2], ":") != NULL) {
        sscanf(argv[2], "assoc:%d", &E);
        S = C / (B * E);
        b = log2(B);
        s = log2(S);
    }
    else if (strcmp(argv[2], "assoc") == 0) {
        S = 1;
        E = C / (B * S);
        b = log2(B);
        s = 0;
    }

    if (!isPower2(C) || !isPower2(B)) {
        printf("Value not power of 2\n");
        return 0;
    }

    //arch: [valid, tag, age]
    cache = malloc(S * E * sizeof(long int *));
    int i;
    for (i = 0; i < S * E; i++) {
        cache[i] = malloc(3 * sizeof(long int));
        cache[i][0] = 0;
        cache[i][1] = 0;
        cache[i][2] = 0;
    }

    pre = strcmp("p1", argv[3]) == 0;
    re = strcmp("fifo", argv[4]) == 0;

    FILE *file = fopen(argv[6], "r");
    if (!file) {
        printf("Invalid file\n");
        return 0;
    }

    int counter = 0;
    while (1 < 2) {
        counter++;
        fscanf(file, "%*x");
        fscanf(file, " %c %c", &op, &op);
        fscanf(file, "%lx\n", &addr);
        if (op == 'e') {
            break;
        }

        long int id = addr >> b;
        long int set = id & ((1 << s) - 1);
        long int tag = id >> s;

        int res = search(cache, set, E, tag);
        if (res) {
            hits++;
        }
        else {
            misses++;
            reads++;
            store(cache, set, E, tag, re);
            if (pre) {
                long preId = (addr + B) >> b;
                set = preId & ((1 << s) - 1);
                tag = preId >> s;
                res = search(cache, set, E, tag);
                if (!res) {
                    reads++;
                    store(cache, set, E, tag, re);
                }
            }
        }
        if (op == 'W') {
            writes++;
        }
    }

    /*
    printf("C: %d\n", C);
    printf("B: %d\n", B);
    printf("S: %d\n", S);
    printf("E: %d\n", E);
    printf("Pre: %d\n", pre);
    printf("Re: %d\n", re);
    printf("b: %d\n", b);
    printf("s: %d\n", s);
    printf("\n------------------------\n\n");
    */
    printf("Memory reads: %d\n", reads);
    printf("Memory writes: %d\n", writes);
    printf("Cache hits: %d\n", hits);
    printf("Cache misses: %d\n", misses);

    return 0;
}
