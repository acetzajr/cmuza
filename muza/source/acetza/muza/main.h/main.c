#include "acetza/muza/renders.h"

#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/enveloper.h"

#include <stdio.h>

void mz_hello() { printf("Hello muza\n"); }

void renderx0() {
  printf("Hello renderx0\n");
  mz_wave_t wave;
  mz_enveloper_wave(&mz_enveloper_ref, &wave);
  mz_wave_reverb(&wave, 1, 7, 1.0 / 12.0, 2.0 / 3.0);
  mz_wave_normalize(&wave);
  mz_wave_save(&wave, "tmp/wave.wav");
}

mz_render_t az_render_ref = mz_hello;
