#include "PageTable.h"
#include <cstdlib>

PageTable::PageTable(int numPages, int pageSize)
    : page_size(pageSize) {
    pages.resize(numPages);
    for (auto &p : pages) {
        p.present = rand() % 2;
        if (p.present) p.frame_number = rand() % 100;
        p.protection = (rand() % 2) ? READ_WRITE : READ_ONLY;
    }
}

int PageTable::getFrameNumber(int pageNum, int time, Protection accessType) {
    if (pageNum < 0 || pageNum >= pages.size()) {
        std::cout << "Page Fault: Invalid page number " << pageNum << "\n";
        return -1;
    }
    if (!pages[pageNum].present) {
        std::cout << "Page Fault: Page " << pageNum << " not in memory\n";
        return -1;
    }
    if (accessType == READ_WRITE && pages[pageNum].protection == READ_ONLY) {
        std::cout << "Protection Violation: Cannot write to read-only page\n";
        return -1;
    }
    pages[pageNum].last_access = time;
    return pages[pageNum].frame_number;
}

void PageTable::setFrame(int pageNum, int frame, Protection prot, int time) {
    if (pageNum >= 0 && pageNum < pages.size()) {
        pages[pageNum].frame_number = frame;
        pages[pageNum].present = true;
        pages[pageNum].protection = prot;
        pages[pageNum].last_access = time;
    }
}
