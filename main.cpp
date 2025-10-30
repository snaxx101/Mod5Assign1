#include <iostream>
#include <cstdlib>
#include "SegmentTable.h"

int main() {
    int frames, pageSize, numSegments;
    std::cout << "Enter number of physical frames: ";
    std::cin >> frames;
    std::cout << "Enter page size: ";
    std::cin >> pageSize;
    std::cout << "Enter number of segments: ";
    std::cin >> numSegments;

    SegmentTable segTable(frames);

    // Random initialization
    for (int i = 0; i < numSegments; ++i) {
        int base = i * 10000;
        int limit = 5 + rand() % 5; // 5–9 pages
        Protection prot = (rand() % 2) ? READ_WRITE : READ_ONLY;
        segTable.addSegment(i, base, limit, prot, 2, 3);
    }

    segTable.printMemoryMap();

    // Interactive / batch input
    while (true) {
        int s, pd, p, o, access;
        std::cout << "Enter (segment, pageDir, page, offset, access[0=R,1=W]) or -1 to stop: ";
        std::cin >> s;
        if (s == -1) break;
        std::cin >> pd >> p >> o >> access;

        int phys = segTable.translateAddress(s, pd, p, o, access == 0 ? READ_ONLY : READ_WRITE, true);
        if (phys != -1)
            std::cout << "Physical Address: " << phys << " | Latency: " << segTable.time << "\n";
    }

    segTable.printMemoryMap();
    return 0;
}
