#pragma once

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/enveloper.h"

struct MzTransformUntil {
  mz_time_t time;
  mz_amplitude_t amplitude;
};

struct MzTransformResult {
  mz_bool_t disrupted;
  mz_time_t time;
  mz_amplitude_t amplitude;
};

typedef struct MzTransformUntil mz_transform_until_t;

typedef struct MzTransformResult mz_transform_result_t;

mz_transform_until_t mz_transform_until_release(mz_enveloper_t *enveloper,
                                                mz_wave_t *wave,
                                                mz_duration_t duration);

mz_transform_result_t
mz_transform(mz_wave_t *wave, mz_transformer_t transformer,
             mz_time_t start_time, mz_amplitude_t start_amplitude,
             mz_time_t end_time, mz_amplitude_t end_amplitude, mz_time_t limit);
