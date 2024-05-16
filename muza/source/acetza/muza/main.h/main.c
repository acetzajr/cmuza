#include "acetza/muza/renders.h"

#include "acetza/muza/synths/synth0.h"

#include <stdio.h>

void mz_hello() { printf("Hello muza\n"); }

void mz_renderx0() {
  mz_synth0_t synth;
  mz_synth0_init(&synth);
}

mz_render_t az_render_ref = mz_hello;
