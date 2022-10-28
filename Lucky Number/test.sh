#!/bin/bash

gcc -g sequential.c -o sequential.e
gcc -g -pthread n_threads.c -o n_threads.e
# gcc -g -pthread semaphore.c -o semaphore.e

for n in 10 100 1000
do
  echo "===================="
  echo "Tests with n = $n"
  echo "=== Sequential ====="
  time ./sequential.e $n 

  echo "=== N_Threads ======"
  time ./n_threads.e $n
  echo

  # echo "=== Semaphore ======"
  # time ./semaphore.e $n
  # echo
done