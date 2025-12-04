#include "timer.h"



#define NUM_THREADS 16
#define ITERATIONS_PER_THREAD 30

static char alphabeth[NUM_THREADS] = "abcdefghijklmnop";



long rand_range(long min, long max) {
    return min + (rand() % (max - min + 1));
}

void dummy_work(long iterations) {
    volatile long sum = 0;
    for (long i = 0; i < iterations; i++) {
        sum += i*i;
    }
}

void* thread_work(void* arg) {
    int thread_id = (intptr_t)arg;
    
    char name[64];
    snprintf(name, sizeof(name), "my_function_%c", alphabeth[thread_id]);
    
    for (int i = 0; i < ITERATIONS_PER_THREAD; i++) {
        // -- USER --
        bench_t b = bench_start(name);
        long iterations = rand_range(400, 10000000);
        dummy_work(iterations);
        bench_stop(b);
        // -- USER --
        usleep(rand_range(0, 10000));
    }
    
    return NULL;
}

int main() {

    // -- USER --
    bench_init("benchmarks.csv");
    // -- USER --




    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_work, (void*)(intptr_t)i);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    
    // -- USER --
    bench_deinit();
    // -- USER --


    return 0;
}
