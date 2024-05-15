#pragma once

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/waver.h"

struct WvHarmonizer {
  mz_waver_t *fundamental;
  mz_waver_t *harmonic;
  mz_depth_t depth;
  mz_numberer_t numberer;
};

typedef struct WvHarmonizer mz_harmonizer_t;

extern mz_harmonizer_t mz_harmonizer_default;

void mz_harmonizer_build(mz_harmonizer_t *harmonizer, mz_waver_t *fundamental,
                         mz_waver_t *harmonic, mz_depth_t depth,
                         mz_numberer_t numberer);

void mz_harmonizer_wave(mz_harmonizer_t *harmonizer, mz_wave_t *wave);
