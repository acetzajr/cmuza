#include "acetza/muza/main.h"

#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/enveloper.h"

#include <alloca.h>
#include <stdio.h>

void muza() {
  printf("Hello muza\n");
  mz_wave_t wave;
  mz_enveloper_wave(&mz_enveloper_default, &wave);
  mz_wave_save(&wave, "tmp/wave.wav");
}
