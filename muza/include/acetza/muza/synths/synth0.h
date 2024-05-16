#pragma once

#include "acetza/muza/types.h"
#include "acetza/muza/wavers/basic.h"
#include "acetza/muza/wavers/enveloper.h"
#include "acetza/muza/wavers/harmonizer.h"
#include "acetza/muza/wavers/waver.h"

typedef struct {
  mz_basic_t basic;
  mz_harmonizer_t harmonizer;
  mz_enveloper_t enveloper;
  mz_waver_t waver0;
} mz_synth0_insides_t;

typedef struct {
  mz_synth0_insides_t insides;
  mz_frequency_t frequency;
  mz_duration_t duration;
  mz_amplitude_t amplitude;
} mz_synth0_t;

void mz_synth0_init(mz_synth0_t *synth);

void mz_synth0_wave(mz_synth0_t *synth);
