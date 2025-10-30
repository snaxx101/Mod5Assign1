# Mod5Assign1

## Overview

This C++ project simulates a segmented, paged memory system with **protection checks**, **page replacement**, **multi-level page tables**, and **dynamic memory configuration**.
The simulator allows users to input logical addresses and observe how they are translated to physical memory, including handling page faults, protection violations, and memory utilization.

Key features:

* **Segment Table**: Maps segments to base addresses, limits, and protection flags.
* **Page Table**: Maps pages to physical frames and tracks last access for LRU/FIFO replacement.
* **Two-Level Page Tables**: Supports page directories for large address spaces.
* **Memory Protection**: Enforces read/write permissions per segment and page.
* **Page Fault Handling**: Allocates frames dynamically when a page is not in memory.
* **Physical Memory Management**: Tracks allocated frames and utilization.
* **Simulation Metrics**: Reports latency, page faults, and memory utilization.

---

## Requirements

* **C++17** or later
* Standard C++ compiler (`g++` recommended)
* No external dependencies

---

## File Structure

```
project/
│  ├─ main.cpp
│  ├─ Page.h/cpp
│  ├─ PageTable.h/cpp
│  ├─ PageTable.h/cpp
│  ├─ SegmentTable.h/cpp
│  ├─ Segment.h/cpp
│  ├─ PhysicalMemory.h/cpp
|  ├─ Utils.h/cpp
│  └─ Protection.h
├─ README.md
```

---

## Compilation

Open a terminal in the project root directory and run:

```bash
g++ -std=c++17 main.cpp Segment.cpp SegmentTable.cpp Page.cpp PageTable.cpp PhysicalMemory.cpp Utils.cpp -o simulator

```

This will generate an executable called `simulator`.

---

## Running the Simulator

Execute the program:

```bash
./simulator
```

The program will prompt you for:

1. **Number of physical frames**
2. **Page size**
3. **Number of segments**

It will then display the **initial memory map**, including segments and their pages.

You can enter logical addresses in the format:

```
(segment, pageDir, page, offset, access)
```

* **segment**: Segment number
* **pageDir**: Page directory index (for multi-level page tables)
* **page**: Page number within the directory
* **offset**: Offset within the page
* **access**: `0 = read`, `1 = write`

Example input:

```
0 0 0 1 0   # Segment 0, PageDir 0, Page 0, Offset 1, Read
1 0 2 0 1   # Segment 1, PageDir 0, Page 2, Offset 0, Write
-1          # Stop entering addresses
```

After each input, the simulator outputs:

* Physical address or error (page fault, protection violation, segmentation fault)
* Simulated **latency**
* Updated **memory map** at the end

---

## Example Session

```
Enter number of physical frames: 16
Enter page size: 4
Enter number of segments: 3

Memory Map:
Segment 0 Base=0 Limit=8 Prot=RO
Segment 1 Base=10000 Limit=6 Prot=RW
Segment 2 Base=20000 Limit=7 Prot=RW
Physical Memory Utilization: 0%

Enter (segment, pageDir, page, offset, access[0=R,1=W]) or -1 to stop: 0 0 0 0 0
Physical Address: 60 | Latency: 1

Enter (segment, pageDir, page, offset, access[0=R,1=W]) or -1 to stop: -1
Memory Map:
Segment 0 Base=0 Limit=8 Prot=RO
Segment 1 Base=10000 Limit=6 Prot=RW
Segment 2 Base=20000 Limit=7 Prot=RW
Physical Memory Utilization: 6.25%
```

---

## Notes

* **Page Faults**: Occur when a page is not present; the simulator will allocate a physical frame automatically.
* **Protection Violations**: Writing to a read-only page or segment will be blocked.
* **Segmentation Faults**: Accessing an invalid segment triggers an error.
* **Latency Simulation**: Each access is assigned a random latency (1–5 units) to model real memory delays.

---

## Extending the Simulator

* **Add multi-threading** to simulate concurrent memory accesses.
* **Implement LRU vs FIFO** page replacement comparison.
* **Stress Testing**: Generate random logical addresses to measure memory utilization and page fault rates.
* **Visualization**: Display Gantt-like timelines of address translations.
