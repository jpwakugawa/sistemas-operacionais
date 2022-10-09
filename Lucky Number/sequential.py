#!/usr/bin/python3

from random import randint
from time import time

def lucky_number(n):
    start = time()
    matriz = []

    for i in range(n):
        line = []
        for j in range(n):
            random = randint(0, n-1)
            if i==0:
                line.append(random)
            else:
                line.append(matriz[i-1][random])
        matriz.append(line)

    end = time()
    exec_time = end - start
    return matriz, exec_time

def print_matriz(matriz):
    size = len(matriz)

    for i in range(size):
        for j in range(size):
            print(matriz[i][j]) if j==size-1 else print(matriz[i][j], end=" ")

n = int(input())
matriz, exec_time = lucky_number(n)

if n<=10:
    print_matriz(matriz)

print(f"Execution Time: {exec_time:.4f}")
