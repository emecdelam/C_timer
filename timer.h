#include <time.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

// Change to disable benchmarks
#define BENCH_DISABLE 0
// Change to disable multithread safety (faster in single thread)
#define BENCH_MULTITHREAD 1

typedef struct bench {
    struct timespec start, end;
    const char* name;
} bench_t;

extern FILE* bench_output;

int bench_init(const char* filename);

bench_t bench_start(const char* name);

double bench_get(bench_t bench);

int bench_stop(bench_t bench);


int bench_deinit();
