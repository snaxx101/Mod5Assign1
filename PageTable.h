#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <vector>
#include <iostream>
#include "Page.h"

class PageTable {
public:
    std::vector<Page> pages;
    int page_size;

    PageTable(int numPages = 0, int pageSize = 4);

    int getFrameNumber(int pageNum, int time, Protection accessType);
    void setFrame(int pageNum, int frame, Protection prot, int time);
};

#endif
