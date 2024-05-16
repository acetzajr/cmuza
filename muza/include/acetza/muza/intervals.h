#pragma once

#include "acetza/math.h"

void mz_print_intervals();

/*
> (11) intervals
[  1/  1] [256/243] [  9/  8] [ 32/ 27] [ 81/ 64] [  4/  3]
[  3/  2] [128/ 81] [ 27/ 16] [ 16/  9] [243/128] [  2/  1]
*/
extern az_rational_t mzx01___1___1;
extern az_rational_t mzx02_256_243;
extern az_rational_t mzx03___9___8;
extern az_rational_t mzx04__32__27;
extern az_rational_t mzx05__81__64;
extern az_rational_t mzx06___4___3;
extern az_rational_t mzx07___3___2;
extern az_rational_t mzx08_128__81;
extern az_rational_t mzx09__27__16;
extern az_rational_t mzx10__16___9;
extern az_rational_t mzx11_243_128;
extern az_rational_t mzx12___2___1;

extern az_rational_t *mzx_intervals[12];
