#!/usr/bin/python3
# %%

import matplotlib.pyplot as plt
import numpy as np


def sliceLast(str):
    return str[:-1]


def readStats(filename):
    userTime = 0
    systemTime = 0
    cpuUsage = 0
    realTime = 0
    total = 0
    with open(filename, 'r') as file:
        lines = file.read().split('\n')
        total = len(lines) - 1
        for line in lines:
            parts = line.split(' ')
            if len(parts) == 1:
                continue
            userTime += float(sliceLast(parts[1]))
            systemTime += float(sliceLast(parts[3]))
            cpuUsage += float(sliceLast(parts[5]))
            realTime += float(sliceLast(parts[7]))
    return ([userTime / total, systemTime / total, realTime / total], cpuUsage / total, total)


def cpu(title, pcpu, tcpu):
    index = np.arange(3)
    barWidth = 0.35

    _, ax = plt.subplots()
    ax.bar(index, [0, pcpu, 0], barWidth, label='Process')
    ax.bar(index + barWidth, [0, tcpu, 0], barWidth, label='Thread')

    ax.set_xlabel('Resource Usage')
    ax.set_ylabel('Usage (%)')
    ax.set_title(title)
    ax.set_xticks(index + barWidth / 2)
    ax.set_xticklabels(['', 'CPU Usage', ''])
    ax.legend()
    plt.show()


def graph(algorithm, fname):
    pdata, pcpu, total = readStats('p_' + fname + '.txt')
    tdata, tcpu, total = readStats('t_' + fname + '.txt')

    title = 'Processes vs. Threads (' + algorithm + ') ' + \
        str(total) + ' iterations'

    index = np.arange(len(pdata))
    barWidth = 0.35

    _, ax = plt.subplots()
    ax.bar(index, pdata, barWidth, label='Process')
    ax.bar(index + barWidth, tdata, barWidth, label='Thread')

    ax.set_xlabel('Resource usage')
    ax.set_ylabel('Time (seconds)')
    ax.set_title(title)
    ax.set_xticks(index + barWidth / 2)
    ax.set_xticklabels(['User Time', 'System Time', 'Real Time'])
    ax.legend()
    plt.show()
    cpu(title, pcpu, tcpu)


def main():
    graph('Merge Sort', 'merge')
    graph('Quick Sort', 'quick')
    graph('Map-Reduce', 'mpred')


if __name__ == '__main__':
    main()
# %%
