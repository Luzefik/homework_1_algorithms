#!/usr/bin/env python3
"""
Generates PNG plots into out_dir:
 - ops_throughput.png : ops_per_sec vs size for each variant
 - mem_usage.png      : mem_bytes vs size for each variant
 - sorting_times.png  : sorting times (mean+std) per algorithm vs size
 - init_times.png     : initialization time (init_ms) vs size for each variant

Requires: pandas, matplotlib, seaborn, numpy
"""
import argparse
import os
import sys
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np


def plot_ops(ops_csv, out_dir, split=False):
    df = pd.read_csv(ops_csv)
    # group by variant and size
    sns.set(style='whitegrid')
    plt.figure(figsize=(8,5))
    df_plot = df.copy()
    # ops_per_sec may be float; aggregate mean
    agg = df_plot.groupby(['variant','size'])['ops_per_sec'].mean().reset_index()
    sns.lineplot(data=agg, x='size', y='ops_per_sec', hue='variant', marker='o', style='variant')
    # make markers and lines more visible (in case series overlap)
    ax = plt.gca()
    for line in ax.get_lines():
        line.set_markersize(7)
        line.set_linewidth(2)
    plt.xscale('log')
    plt.title('Ops/sec vs size')
    plt.tight_layout()
    out = os.path.join(out_dir, 'ops_throughput.png')
    plt.savefig(out)
    print('Wrote', out)

    # mem_bytes
    plt.figure(figsize=(8,5))
    memagg = df_plot.groupby(['variant','size'])['mem_bytes'].mean().reset_index()
    sns.lineplot(data=memagg, x='size', y='mem_bytes', hue='variant', marker='o', style='variant')
    ax = plt.gca()
    for line in ax.get_lines():
        line.set_markersize(7)
        line.set_linewidth(2)
    plt.xscale('log')
    plt.yscale('log')
    plt.title('Estimated memory (bytes) vs size')
    plt.tight_layout()
    out2 = os.path.join(out_dir, 'mem_usage.png')
    plt.savefig(out2)
    print('Wrote', out2)


def plot_init_times(ops_csv, out_dir):
    # Simple plot for init_ms vs size per variant
    df = pd.read_csv(ops_csv)
    if 'init_ms' not in df.columns:
        print('init_ms column not found in', ops_csv)
        return
    sns.set(style='whitegrid')
    plt.figure(figsize=(8,5))
    agg = df.groupby(['variant','size'])['init_ms'].mean().reset_index()
    sns.lineplot(data=agg, x='size', y='init_ms', hue='variant', marker='o', style='variant')
    ax = plt.gca()
    for line in ax.get_lines():
        line.set_markersize(7)
        line.set_linewidth(2)
    plt.xscale('log')
    plt.title('Initialization time (ms) vs size')
    plt.xlabel('size')
    plt.ylabel('init (ms)')
    plt.tight_layout()
    out = os.path.join(out_dir, 'init_times.png')
    plt.savefig(out)
    print('Wrote', out)


def plot_sorting(sort_csv, out_dir):
    df = pd.read_csv(sort_csv)
    sns.set(style='whitegrid')
    # compute mean and std per algorithm,size
    stats = df.groupby(['algorithm','size'])['time_ms'].agg(['mean','std']).reset_index()
    plt.figure(figsize=(8,5))
    for alg, g in stats.groupby('algorithm'):
        plt.errorbar(g['size'], g['mean'], yerr=g['std'].fillna(0), label=alg, marker='o')
    plt.xscale('log')
    plt.title('Sorting time (ms) vs size')
    plt.xlabel('size')
    plt.ylabel('time (ms)')
    plt.legend()
    plt.tight_layout()
    out = os.path.join(out_dir, 'sorting_times.png')
    plt.savefig(out)
    print('Wrote', out)


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--ops', required=True)
    p.add_argument('--sort', required=True)
    p.add_argument('--out_dir', required=True)
    p.add_argument('--split', action='store_true')
    args = p.parse_args()

    os.makedirs(args.out_dir, exist_ok=True)

    # validate files
    if not os.path.exists(args.ops):
        print('ERROR: ops CSV not found:', args.ops, file=sys.stderr)
        sys.exit(2)
    if not os.path.exists(args.sort):
        print('ERROR: sort CSV not found:', args.sort, file=sys.stderr)
        sys.exit(2)

    try:
        plot_ops(args.ops, args.out_dir, split=args.split)
        plot_init_times(args.ops, args.out_dir)
        plot_sorting(args.sort, args.out_dir)
    except Exception as e:
        print('Plotting failed:', e, file=sys.stderr)
        sys.exit(3)


if __name__ == '__main__':
    main()
