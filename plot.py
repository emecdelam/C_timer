#!/usr/bin/env python3

import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import csv
from collections import defaultdict

def plot_chart(csv_file, output_file, filter_funcs=None):   
    data = []
    with open(csv_file, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            data.append({
                'name': row['name'],
                'start_ns': float(row['start_ns']),
                'end_ns': float(row['end_ns']),
                'elapsed_ns': float(row['elapsed_ns'])
            })
    for row in data:
        row['start_ms'] = row['start_ns'] / 1e6
        row['end_ms'] = row['end_ns'] / 1e6
        row['elapsed_ms'] = row['elapsed_ns'] / 1e6
    
    min_start = min(row['start_ms'] for row in data)
    for row in data:
        row['start_ms'] -= min_start
        row['end_ms'] -= min_start
    
    if filter_funcs:
        data = [row for row in data if row['name'] in filter_funcs]
        if not data:
            print(f"Error: No matching functions found. Available: {list(dict.fromkeys(row['name'] for row in data))}")
            return
    
    functions = list(dict.fromkeys(row['name'] for row in data))
    func_to_y = {func: i for i, func in enumerate(functions)}
    
    colors = plt.cm.tab20([(i / len(functions)) for i in range(len(functions))])
    func_to_color = {func: colors[i] for i, func in enumerate(functions)}
    
    fig, ax = plt.subplots(figsize=(16, 8))
    
    for row in data:
        y = func_to_y[row['name']]
        width = row['elapsed_ms']
        color = func_to_color[row['name']]
        
        rect = mpatches.Rectangle(
            (row['start_ms'], y - 0.35),
            width,
            0.7,
            linewidth=0.5,
            edgecolor='black',
            facecolor=color,
            alpha=0.8
        )
        ax.add_patch(rect)
    
    max_end = max(row['end_ms'] for row in data)
    ax.set_xlim(0, max_end * 1.02)
    ax.set_ylim(-0.5, len(functions) - 0.5)
    ax.set_yticks(range(len(functions)))
    ax.set_yticklabels(functions, fontsize=11)
    ax.invert_yaxis()
    ax.set_xlabel('time [ms]', fontsize=12, fontweight='bold')
    ax.set_ylabel('function', fontsize=12, fontweight='bold')
    ax.grid(True, axis='x', alpha=0.3, linestyle='--')
    legend_patches = [mpatches.Patch(facecolor=func_to_color[func], edgecolor='black', label=func) 
                      for func in functions]
    ax.legend(handles=legend_patches, loc='upper left', bbox_to_anchor=(1.01, 1), fontsize=10)
    
    plt.savefig(output_file, dpi=150, bbox_inches='tight')


    print("\n=== Benchmark stats ===")
    print(f"Total records: {len(data)}")
    print(f"Unique functions: {len(functions)}")
    print(f"Total time range: {max_end:.2f} ms")
    
    stats = defaultdict(list)
    for row in data:
        stats[row['name']].append(row['elapsed_ms'])
    
    sorted_funcs = sorted(functions, key=lambda f: sum(stats[f]) / len(stats[f]), reverse=True)

    print("\n======= Results =======")
    print(f"{'Function':<30} {'Mean (ms)':<12} {'Count':<8} {'Min (ms)':<12} {'Max (ms)':<12} {'Total (ms)':<12}")
    print("-" * 90)
    for func in sorted_funcs:
        times = stats[func]
        print(f"{func:<30} {sum(times)/len(times):<12.3f} {len(times):<8} {min(times):<12.3f} {max(times):<12.3f} {sum(times):<12.3f}")
        
    print("\n\n")
    plt.show()
    
    
if __name__ == "__main__":
    import sys
    
    csv_file = "benchmarks.csv" if len(sys.argv) < 2 else sys.argv[1]
    output_file = "chart.png" if len(sys.argv) < 3 else sys.argv[2]
    filter_funcs = sys.argv[3:] if len(sys.argv) > 3 else None
    
    try:
        plot_chart(csv_file, output_file, filter_funcs)
    except FileNotFoundError:
        print(f"Error: Could not find {csv_file}")
        sys.exit(1)
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)
