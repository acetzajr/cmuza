#include "acetza/muza/main.h"

#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/harmonizer.h"

#include <stdio.h>

void muza() {
  printf("Hello muza\n");
  mz_wave_t wave;
  mz_harmonizer_wave(&mz_harmonizer_ref, &wave);
  mz_wave_save(&wave, "tmp/wave.wav");
}
