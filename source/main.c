#include "stdio.h"
#include <bits/time.h>
#include <time.h>

void muza() { printf("Hello muza\n"); }

void print_long_with_comas(long n) {
  if (n < 1000) {
    printf("%ld", n);
    return;
  }
  print_long_with_comas(n / 1000);
  printf(",%ld", n % 1000);
}

void run_and_measure() {
  struct timespec start;
  struct timespec stop;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  muza();
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  long seconds = stop.tv_sec - start.tv_sec;
  long nano = stop.tv_nsec - start.tv_nsec;
  printf("> Running time [seconds: ");
  print_long_with_comas(seconds);
  printf(", nano: ");
  print_long_with_comas(nano);
  printf("]\n");
}

int main() { run_and_measure(); }
