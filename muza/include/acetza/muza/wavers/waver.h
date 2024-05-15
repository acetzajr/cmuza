#pragma once

#include "acetza/muza/wave.h"

enum MzWaverType { MZ_BASIC, MZ_ENVELOPER };

typedef enum MzWaverType wv_type_t;

struct MzWaver {
  wv_type_t type;
  void *ptr;
};

typedef struct MzWaver mz_waver_t;

extern mz_waver_t mz_waver_default;

void mz_waver_build(mz_waver_t *waver, wv_type_t type, void *ptr);

void mz_waver_copy(mz_waver_t *waver, mz_waver_t *other);

void mz_waver_wave(mz_waver_t *waver, mz_wave_t *wave);
