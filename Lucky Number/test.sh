#!/bin/bash

gcc -g sequential.c -o sequential
gcc -g -pthread n_threads.c -o n_threads

for n in 10 100 1000
do
  echo
  echo "TESTS WITH N = $n"
  echo "=== Sequential ==="
  time ./sequential $n 

  echo "=== N_Threads ==="
  time ./n_threads $n
  echo
done