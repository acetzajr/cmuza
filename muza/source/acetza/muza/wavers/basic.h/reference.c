#include "acetza/muza/wavers/basic.h"

#include "acetza/muza/functions/primitives.h"

mz_basic_initializer_t mz_basic_initializer = {.primitive = mz_primitives_sin,
                                               .frequency = 360.0,
                                               .duration = 1.0,
                                               .channels = 2,
                                               .frame_rate = 44'100};
