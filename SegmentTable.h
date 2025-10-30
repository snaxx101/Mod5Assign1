#ifndef SEGMENTTABLE_H
#define SEGMENTTABLE_H

#include <map>
#include <vector>
#include "Segment.h"
#include "PageTable.h"
#include "PhysicalMemory.h"

class SegmentTable {
public:
    std::vector<Segment> segments;
    std::map<int, std::map<int, PageTable>> directoryTables; // 2-level paging
    PhysicalMemory physMem;
    int time = 0;

    SegmentTable(int numFrames = 16);

    void addSegment(int id, int base, int limit, Protection prot, int pageDirEntries = 2, int pagesPerTable = 5);
    int translateAddress(int segNum, int pageDir, int pageNum, int offset, Protection accessType, bool useLRU = false);
    void printMemoryMap();
};

#endif
