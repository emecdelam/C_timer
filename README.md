# C_timer

A simple thread safe library for measuring time impact of functions

## Usage

To get started you need to add timer.c and timer.h to your project

For initialisation, you need to call `bench_init("{filename.csv}");` in your main function
and later `bench_deinit();`

For benchmarks, you simply need to follow this template
```c
bench_t b = bench_start("function");
function(...);
bench_stop(b);
```
## Plotting

For plotting, you can specify multiple arguments like so
```python
python3 plot.py {filename.csv} {output.png} [banned_function_a banned_function_b]
```


## Results

To view the results you can use the given plot.py file (requires matplotlib)
You should get a printout like this :
```
=== Benchmark stats ===
Total records: 480
Unique functions: 16
Total time range: 648.95 ms

======= Results =======
Function                       Mean (ms)    Count    Min (ms)     Max (ms)     Total (ms)  
------------------------------------------------------------------------------------------
thread_1_work                  16.784       30       0.780        106.473      503.532     
thread_11_work                 15.898       30       1.147        97.130       476.926     
thread_4_work                  15.849       30       0.433        78.355       475.480     
thread_5_work                  15.375       30       0.411        45.932       461.249     
thread_0_work                  15.330       30       0.846        84.656       459.912     
thread_12_work                 15.238       30       0.653        117.632      457.148     
thread_13_work                 15.158       30       0.415        56.311       454.731     
thread_9_work                  14.783       30       0.045        81.268       443.502     
thread_6_work                  14.669       30       0.240        83.822       440.073     
thread_7_work                  14.538       30       0.421        70.464       436.149     
thread_10_work                 14.299       30       0.091        88.134       428.955     
thread_3_work                  14.152       30       0.274        84.907       424.574     
thread_8_work                  14.064       30       0.246        51.873       421.906     
thread_15_work                 14.026       30       0.490        81.235       420.788     
thread_14_work                 14.001       30       0.297        105.298      420.034     
thread_2_work                  13.359       30       0.190        67.093       400.770     
```

And a similar graph

![alt text](https://github.com/emecdelam/C_timer/blob/master/assets/example.png)

## Configuration

In `timer.h` you can configure these
```
// Change to disable benchmarks
#define BENCH_DISABLE 0
// Change to disable multithread safety (faster in single thread)
#define BENCH_MULTITHREAD 1
```
If you want to disable the benchmarks or disable multithread
