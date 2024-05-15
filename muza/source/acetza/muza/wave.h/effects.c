#include "acetza/muza/wave.h"

#include "acetza/muza/types.h"
#include "acetza/types.h"

// RECOMMENDED: iterations = 7, delay = 1.0 / 12.0, decay = 2.0 / 3.0
void mz_wave_reverb(mz_wave_t *wave, mz_bool_t extend, mz_count_t iterations,
                    mz_time_t delay, mz_amplitude_t decay) {
  static f64_t array[] = {1.0, 1.235, 2.357, 3.571};
  mz_wave_t clone;
  mz_wave_clone(wave, &clone);
  for (mz_index_t index = 0; index < 4; ++index) {
    mz_time_t delay_cpy = delay * array[index];
    mz_amplitude_t decay_cpy = decay;
    mz_time_t time = delay_cpy;
    for (mz_index_t iteration = 0; iteration < iterations; ++iteration,
                    time += delay_cpy, delay_cpy *= delay_cpy,
                    decay_cpy *= decay_cpy) {
      if (extend) {
        mz_wave_add(wave, &clone, time, decay_cpy);
      } else {
        mz_wave_add_mod(wave, &clone, time, decay_cpy);
      }
    }
  }
}
