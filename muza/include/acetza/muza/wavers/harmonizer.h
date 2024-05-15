#pragma once

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/waver.h"

typedef struct {
  mz_waver_t *fundamental;
  mz_waver_t *harmonic;
  mz_depth_t depth;
  mz_numberer_t numberer;
} mz_harmonizer_t;

extern mz_harmonizer_t mz_harmonizer_ref;

void mz_harmonizer_init(mz_harmonizer_t *harmonizer);

void mz_harmonizer_wave(mz_harmonizer_t *harmonizer, mz_wave_t *wave);
