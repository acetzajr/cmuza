#pragma once

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/basic.h"
#include "acetza/muza/wavers/enveloper.h"
#include "acetza/muza/wavers/harmonizer.h"
#include "acetza/muza/wavers/waver.h"

typedef struct {
  mz_basic_t basic;
  mz_harmonizer_t harmonizer;
  mz_enveloper_t enveloper;
} mz_synth0_wavers_t;

typedef struct {
  mz_waver_t basic;
  mz_waver_t harmonizer;
  mz_waver_t enveloper;
} mz_synth0_generics_t;

typedef struct {
  mz_synth0_generics_t generics;
  mz_synth0_wavers_t wavers;
  mz_frequency_t frequency;
  mz_duration_t duration;
  mz_amplitude_t amplitude;
} mz_synth0_t;

void mz_synth0_init(mz_synth0_t *synth);

void mz_synth0_wave(mz_synth0_t *synth, mz_wave_t *wave);
