#ifndef PHYSICALMEMORY_H
#define PHYSICALMEMORY_H

#include <vector>
#include <deque>
#include <algorithm>

class PhysicalMemory {
public:
    int num_frames;
    std::vector<bool> free_frames;
    std::deque<int> fifo_queue;   // FIFO replacement
    std::vector<int> last_access; // For LRU
    int time = 0;

    PhysicalMemory(int frames = 16);

    int allocateFrame(bool useLRU = false);
    void freeFrame(int frame);
    double utilization() const;
    void updateAccess(int frame, int time);
};

#endif
