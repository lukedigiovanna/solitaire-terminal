#include "mathutils.h"

int wrap(int v, int lo, int hi) {
    if (v < lo) return hi;
    if (v > hi) return lo;
    return v;
}