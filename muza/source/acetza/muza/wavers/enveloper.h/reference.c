#include "acetza/muza/wavers/enveloper.h"

#include "acetza/muza/functions/transformers.h"
#include "acetza/muza/wavers/waver.h"

mz_enveloper_initializer_t mz_enveloper_initializer = {
    .attack = 1.0 / 16.0,
    .hold = 1.0 / 12.0,
    .decay = 1.0 / 8.0,
    .sustain = 1.0 / 2.0,
    .release = 1.0 / 4.0,
    .attack_transformer = mz_transformers_smooth,
    .decay_transformer = mz_transformers_smooth,
    .release_transformer = mz_transformers_smooth};
