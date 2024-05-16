#pragma once

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/waver.h"

typedef struct {
  mz_waver_t *fundamental;
  mz_waver_t *harmonic;
} mz_harmonizer_wavers_t;

typedef struct {
  mz_harmonizer_wavers_t wavers;
  mz_depth_t depth;
  mz_numberer_t numberer;
} mz_harmonizer_t;

typedef struct {
  mz_depth_t depth;
  mz_numberer_t numberer;
} mz_harmonizer_initializer_t;

extern mz_harmonizer_initializer_t mz_harmonizer_initializer;

void mz_harmonizer_init(mz_harmonizer_t *harmonizer, mz_waver_t *fundamental,
                        mz_waver_t *harmonic);

void mz_harmonizer_wave(mz_harmonizer_t *harmonizer, mz_wave_t *wave);
