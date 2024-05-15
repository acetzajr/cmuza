#include "acetza/measure.h"

#include "acetza/printing.h"

#include <bits/time.h>
#include <stdio.h>
#include <time.h>

void measure(void (*fun)()) {
  struct timespec start;
  struct timespec stop;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  fun();
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  long seconds = stop.tv_sec - start.tv_sec;
  long nano = stop.tv_nsec - start.tv_nsec;
  printf("> Running time [seconds: ");
  az_u64_print(seconds);
  printf(", nano: ");
  az_u64_print(nano);
  printf("]\n");
}
