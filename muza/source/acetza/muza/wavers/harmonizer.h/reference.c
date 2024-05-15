#include "acetza/muza/wavers/harmonizer.h"

#include "acetza/muza/functions/numberers.h"
#include "acetza/muza/wavers/waver.h"

mz_harmonizer_t mz_harmonizer_ref = {.fundamental = &mz_waver_default,
                                     .harmonic = &mz_waver_default,
                                     .depth = 7,
                                     .numberer = mz_numberers_saw};
