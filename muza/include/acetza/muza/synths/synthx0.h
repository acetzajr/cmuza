#pragma once

#include "acetza/muza/wavers/basic.h"
#include "acetza/muza/wavers/enveloper.h"
#include "acetza/muza/wavers/harmonizer.h"

typedef struct {
  mz_basic_t basic;
  mz_harmonizer_t harmonizer;
  mz_enveloper_t enveloper;
} mz_synthx0_t;

void mz_synthx0_wave(mz_synthx0_t *synth);
