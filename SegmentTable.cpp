#include "SegmentTable.h"
#include <iostream>
#include <cstdlib>

SegmentTable::SegmentTable(int numFrames)
    : physMem(numFrames) {}

void SegmentTable::addSegment(int id, int base, int limit, Protection prot, int pageDirEntries, int pagesPerTable) {
    segments.push_back({base, limit, prot});
    for (int pd = 0; pd < pageDirEntries; ++pd) {
        int pagesInTable = std::min(pagesPerTable, limit - pd * pagesPerTable);
        if (pagesInTable > 0)
            directoryTables[id][pd] = PageTable(pagesInTable, 4);
    }
}

int SegmentTable::translateAddress(int segNum, int pageDir, int pageNum, int offset,
                                   Protection accessType, bool useLRU) {
    time++;
    if (segNum < 0 || segNum >= segments.size()) {
        std::cout << "Segmentation Fault: Invalid segment " << segNum << "\n";
        return -1;
    }
    Segment &seg = segments[segNum];
    if (accessType == READ_WRITE && seg.protection == READ_ONLY) {
        std::cout << "Protection Violation: Cannot write to read-only segment\n";
        return -1;
    }

    auto &dir = directoryTables[segNum];
    if (dir.find(pageDir) == dir.end()) {
        std::cout << "Page Fault: Page directory not present\n";
        return -1;
    }
    PageTable &pt = dir[pageDir];

    int frame = pt.getFrameNumber(pageNum, time, accessType);
    if (frame == -1) frame = physMem.allocateFrame(useLRU);

    pt.setFrame(pageNum, frame, accessType, time);
    return seg.base_address + frame * pt.page_size + offset;
}

void SegmentTable::printMemoryMap() {
    std::cout << "\nMemory Map:\n";
    for (size_t i = 0; i < segments.size(); ++i) {
        const auto &seg = segments[i];
        std::cout << "Segment " << i << " Base=" << seg.base_address
                  << " Limit=" << seg.limit
                  << " Prot=" << (seg.protection == READ_ONLY ? "RO" : "RW") << "\n";
        auto &dir = directoryTables[i];
        for (auto &pd : dir) {
            std::cout << "  PageDir " << pd.first << ": ";
            for (size_t p = 0; p < pd.second.pages.size(); ++p) {
                const auto &page = pd.second.pages[p];
                std::cout << "[" << p << ":";
                if (!page.present) std::cout << "NP";
                else std::cout << "F" << page.frame_number;
                std::cout << "]";
            }
            std::cout << "\n";
        }
    }
    std::cout << "Physical Memory Utilization: " << physMem.utilization() << "%\n";
}
