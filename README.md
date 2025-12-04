# C_timer

A simple toggable thread safe library for measuring time impact of functions

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
Total time range: 491.73 ms

======= Results =======
Function                       Mean (ms)    Count    Min (ms)     Max (ms)     Total (ms)  
------------------------------------------------------------------------------------------
my_function_h                  10.669       30       0.802        20.488       320.068     
my_function_d                  10.588       30       1.903        19.251       317.648     
my_function_a                  10.265       30       0.091        21.650       307.949     
my_function_g                  10.265       30       0.733        18.808       307.936     
my_function_i                  10.082       30       0.036        20.544       302.460     
my_function_c                  10.042       30       0.244        25.008       301.254     
my_function_e                  9.860        30       1.046        32.404       295.806     
my_function_j                  9.552        30       0.295        21.835       286.556     
my_function_o                  9.356        30       0.311        20.392       280.676     
my_function_b                  9.283        30       0.113        25.766       278.475     
my_function_k                  9.223        30       1.224        18.620       276.701     
my_function_l                  9.033        30       0.209        21.302       270.985     
my_function_n                  8.908        30       0.352        23.941       267.229     
my_function_m                  8.823        30       0.023        22.632       264.693     
my_function_f                  8.760        30       0.685        21.283       262.803     
my_function_p                  7.502        30       0.371        19.719       225.064    
```

And a graph

![alt text](https://github.com/emecdelam/C_timer/blob/master/assets/example.png)

## Configuration

In `timer.h` you can configure these
```
// Change to disable benchmarks (faster program)
#define BENCH_DISABLE 0
// Change to disable multithread safety (faster in single thread)
#define BENCH_MULTITHREAD 1
```
If you want to disable the benchmarks or disable multithread
