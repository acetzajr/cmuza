#pragma once

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"

typedef enum { MZ_WAVER, MZ_BASIC, MZ_ENVELOPER, MZ_HARMONIZER } wv_type_t;

typedef struct {
  wv_type_t type;
  void *waver;
} mz_waver_t;

void mz_waver_init(mz_waver_t *waver, wv_type_t type, void *ptr);

void mz_waver_wave(mz_waver_t *waver, mz_wave_t *wave);

mz_frequency_t mz_waver_frequency(mz_waver_t *waver);

void mz_waver_set_frequency(mz_waver_t *waver, mz_frequency_t frequency);

void mz_waver_set_duration(mz_waver_t *waver, mz_duration_t duration);
