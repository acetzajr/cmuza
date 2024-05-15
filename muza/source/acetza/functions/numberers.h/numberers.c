#include "acetza/muza/functions/numberers.h"

#include "acetza/muza/types.h"

mz_index_t mz_numberers_saw(mz_index_t index) { return index; }

mz_index_t mz_numberers_sqr(mz_index_t index) { return 2 * index - 1; }
