#include "PhysicalMemory.h"
#include <iostream>

PhysicalMemory::PhysicalMemory(int frames)
    : num_frames(frames) {
    free_frames.resize(frames, true);
    last_access.resize(frames, 0);
}

int PhysicalMemory::allocateFrame(bool useLRU) {
    // First try free frames
    for (int i = 0; i < num_frames; ++i) {
        if (free_frames[i]) {
            free_frames[i] = false;
            fifo_queue.push_back(i);
            last_access[i] = time;
            return i;
        }
    }

    // Replacement
    int frame = -1;
    if (!useLRU) { // FIFO
        frame = fifo_queue.front();
        fifo_queue.pop_front();
        fifo_queue.push_back(frame);
    } else { // LRU
        int oldest_time = time + 1;
        for (int i = 0; i < num_frames; ++i) {
            if (last_access[i] < oldest_time) {
                oldest_time = last_access[i];
                frame = i;
            }
        }
    }

    last_access[frame] = time;
    return frame;
}

void PhysicalMemory::freeFrame(int frame) {
    if (frame >= 0 && frame < num_frames) free_frames[frame] = true;
}

double PhysicalMemory::utilization() const {
    int used = std::count(free_frames.begin(), free_frames.end(), false);
    return (double)used / num_frames * 100.0;
}

void PhysicalMemory::updateAccess(int frame, int t) {
    if (frame >= 0 && frame < num_frames) last_access[frame] = t;
}
