#ifndef PAGE_H
#define PAGE_H

#include "Protection.h"


struct Page {
    int frame_number = -1;
    bool present = false;
    int last_access = 0; // For LRU
    Protection protection = READ_WRITE;
};

#endif
