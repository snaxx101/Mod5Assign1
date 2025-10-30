#ifndef SEGMENT_H
#define SEGMENT_H

#include "Protection.h"

struct Segment {
    int base_address;
    int limit; // number of pages
    Protection protection;
};

#endif
