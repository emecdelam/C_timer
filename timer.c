#define _POSIX_C_SOURCE 199309L

#include "timer.h"

FILE* bench_output = NULL;
static pthread_mutex_t __attribute__((unused)) bench_mutex = PTHREAD_MUTEX_INITIALIZER;

// Initialize the bench file output
int bench_init(const char* filename __attribute__((unused))) {
#if !BENCH_DISABLE
    bench_output = fopen(filename, "w");
    if (bench_output == NULL) {
        perror("Failed to open benchmark output file");
        return -1;
    }
    fprintf(bench_output, "name,start_ns,end_ns,elapsed_ns\n");
    return 0;
#else
    return 0;
#endif
}


// Starts a benchmark for a function given the name
bench_t bench_start(const char* name __attribute__((unused))) {
#if !BENCH_DISABLE
    struct timespec start, end = {0, 0};
    if (strchr(name, ',') != NULL) {
        fprintf(stderr, "Warning: benchmark name contains ',' which will corrupt CSV output\n");
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    bench_t bench = {.start = start, .end = end, .name = name};
    return bench;
#else
    return (bench_t){0};
#endif
}

// Gets the elapsed time in nanoseconds for a benchmark
double bench_get(bench_t bench __attribute__((unused))) {
#if !BENCH_DISABLE
    long elapsed_sec = bench.end.tv_sec - bench.start.tv_sec;
    long elapsed_ns = bench.end.tv_nsec - bench.start.tv_nsec;
    
    if (elapsed_ns < 0) {
        elapsed_sec--;
        elapsed_ns += 1000000000L;
    }
    
    return elapsed_sec * 1000000000.0 + elapsed_ns;
#else
    return 0.0;
#endif
}


// Stops a benchmark for a function
int bench_stop(bench_t bench __attribute__((unused))) {
#if !BENCH_DISABLE
    clock_gettime(CLOCK_MONOTONIC, &bench.end);
    
    long elapsed_sec = bench.end.tv_sec - bench.start.tv_sec;
    long elapsed_ns = bench.end.tv_nsec - bench.start.tv_nsec;
    
    if (elapsed_ns < 0) {
        elapsed_sec--;
        elapsed_ns += 1000000000L;
    }
    
    double elapsed_total_ns = elapsed_sec * 1000000000.0 + elapsed_ns;
    double start_total_ns = bench.start.tv_sec * 1000000000.0 + bench.start.tv_nsec;
    double end_total_ns = bench.end.tv_sec * 1000000000.0 + bench.end.tv_nsec;

    if (BENCH_MULTITHREAD) {
        pthread_mutex_lock(&bench_mutex);
    }

    fprintf(bench_output, "%s,%.0f,%.0f,%.0f\n",
            bench.name, start_total_ns, end_total_ns, elapsed_total_ns);
    if (BENCH_MULTITHREAD) {
        pthread_mutex_unlock(&bench_mutex);
    }
#endif
    return 0;
}


// Closes the output file
int bench_deinit() {
#if !BENCH_DISABLE
    if (bench_output != NULL) {
        fflush(bench_output);
        fclose(bench_output);
        bench_output = NULL;
        return 0;
    }
    return -1;
#else
    return 0;
#endif
}
