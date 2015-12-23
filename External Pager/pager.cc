#include <cstdlib>
#include <stdlib.h>
#include <queue>
#include <map>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include "vm_pager.h"
#include <vector>
#include <new>

using namespace std;

#define VM_ARENA_BASEADDR_VALUE ((unsigned long int) VM_ARENA_BASEADDR)
#define VM_PAGESIZE_INT ((unsigned int) VM_PAGESIZE)
#define VM_ARENA_SIZE_INT ((unsigned int) VM_ARENA_SIZE)

struct pageStruct {
    int zeroBit;
    int refBit;
    int modBit;
    pid_t processID;
    unsigned int virtualPage;
    unsigned int allocatedDiskBlockIndex;
    int residentBit;
    
} ;

queue<pageStruct*> clockQueue;

struct processStruct {
    pid_t processPID;
    page_table_t *pageTable;
    unsigned long int maxValidVirtualAddress;
    vector<pageStruct*> validVirtualPages;
    
} ;

unsigned int ppageEmptyVal;

map<pid_t, processStruct*> processTable;

queue<unsigned int> freeBlocks;
queue<unsigned int> freePhysicalPages;

pid_t currentprocessPID = 0;

void vm_init(unsigned int memory_pages, unsigned int disk_blocks) {
    
    ppageEmptyVal = (VM_ARENA_SIZE_INT / VM_PAGESIZE_INT) + 1;
    
    for (unsigned int i = 0; i < disk_blocks; i++) {
        freeBlocks.push(i);
        
    }
    
    for (unsigned int i = 0; i < memory_pages; ++i) {
        freePhysicalPages.push(i);

    }
    
}

void vm_create(pid_t processPID) {

    unsigned int numPageTableEntries = VM_ARENA_SIZE_INT / VM_PAGESIZE_INT;
    
    processStruct *newProcess = new (nothrow) processStruct;

    if (newProcess == NULL) {
        return;

    }
    
    newProcess->processPID = processPID;
    
    newProcess->pageTable = new (nothrow) page_table_t;

    if (newProcess->pageTable == NULL) {
        return;

    }
    
    page_table_entry_t *entry = new (nothrow) page_table_entry_t;

    if (entry == NULL) {
        return;

    }
    
    for (unsigned int i = 0; i < numPageTableEntries; i++) {
        entry = &newProcess->pageTable->ptes[i];
        entry->ppage = ppageEmptyVal;
        entry->read_enable = 0;
        entry->write_enable = 0;
        
    }
    
    newProcess->maxValidVirtualAddress = VM_ARENA_BASEADDR_VALUE;
    processTable.insert(pair<pid_t, processStruct*>(newProcess->processPID, newProcess) );
    
}

void vm_switch(pid_t processPID) {
    
    currentprocessPID = processPID;
    page_table_base_register = processTable[processPID]->pageTable;
    
}

void newPage(unsigned int newIndex , unsigned int newBlock) {
    
    pageStruct *newVirtualPage = new (nothrow) pageStruct;
    
    if (newVirtualPage == NULL) {
        return;

    }
    
    newVirtualPage->zeroBit = 0;
    newVirtualPage->refBit = 0;
    newVirtualPage->modBit = 0;
    newVirtualPage->processID = currentprocessPID;
    newVirtualPage->virtualPage = newIndex;
    newVirtualPage->allocatedDiskBlockIndex = newBlock;
    newVirtualPage->residentBit = 0;

    processTable[currentprocessPID]->validVirtualPages.push_back(newVirtualPage);
    
}

unsigned int addressToIndexConversion(unsigned long int address) {
    
    unsigned long int hexIndex =  (address - VM_ARENA_BASEADDR_VALUE) / VM_PAGESIZE_INT;
    unsigned int correspondingIndex = (unsigned int)hexIndex;
    
    return correspondingIndex;
    
}

unsigned int addressToOffsetConversion(unsigned long int address) {
    
    unsigned long int hexIndex =  ((address - VM_ARENA_BASEADDR_VALUE) % VM_PAGESIZE_INT);
    unsigned int correspondingOffset = (unsigned int)hexIndex;
    
    return correspondingOffset;
    
}

void zeroFillFunction(pageStruct* newPage, unsigned int pageTableIndex) {

    if (newPage->zeroBit == 0) {           
        unsigned long int memoryBlock = ((processTable[currentprocessPID]->pageTable->ptes[pageTableIndex].ppage) * (VM_PAGESIZE_INT));
        memset ((char*)pm_physmem + memoryBlock, 0, VM_PAGESIZE_INT);

    }
        
    else {
        unsigned int readBlock = newPage->allocatedDiskBlockIndex;
        unsigned int readPPage = processTable[currentprocessPID]->pageTable->ptes[pageTableIndex].ppage;
        disk_read(readBlock, readPPage);
    
    }

}

void * vm_extend() {

    if (freeBlocks.size() == 0) {
        return NULL;

    }
    
    else if ((processTable[currentprocessPID]->maxValidVirtualAddress + VM_PAGESIZE_INT) > (VM_ARENA_BASEADDR_VALUE + VM_ARENA_SIZE_INT)) {
        return NULL;  

    }

    unsigned int vacantDiskBlock = freeBlocks.front();
    freeBlocks.pop();
    
    unsigned long int lowestByte;
    
    if (processTable[currentprocessPID]->maxValidVirtualAddress == VM_ARENA_BASEADDR_VALUE) {
        lowestByte = VM_ARENA_BASEADDR_VALUE;

    }
    
    else {
        lowestByte = processTable[currentprocessPID]->maxValidVirtualAddress + 1;

    }

    processTable[currentprocessPID]->maxValidVirtualAddress = lowestByte + VM_PAGESIZE_INT - 1;
        
    unsigned int virtualPageIndex = addressToIndexConversion(lowestByte);
    
    newPage(virtualPageIndex, vacantDiskBlock);
    
    unsigned long int *lowBytePtr;
    lowBytePtr = (unsigned long int*)lowestByte;
    void* returnPointer = (void*)lowBytePtr;
    
    return returnPointer;
    
}

int vm_fault(void *addr, bool write_flag) {

    unsigned long int hexVirtualAddress = (unsigned long int)addr;
    
    if (hexVirtualAddress > processTable[currentprocessPID]->maxValidVirtualAddress || hexVirtualAddress < VM_ARENA_BASEADDR_VALUE) {
        return -1;

    }
    
    unsigned int pageTableIndex = addressToIndexConversion(hexVirtualAddress);
    
    page_table_entry_t *tableEntry = &processTable[currentprocessPID]->pageTable->ptes[pageTableIndex];
    
    if (processTable[currentprocessPID]->validVirtualPages[pageTableIndex]->residentBit == 0) {    //non-resident
        
        pageStruct *newPage = processTable[currentprocessPID]->validVirtualPages[pageTableIndex];
        
        if (freePhysicalPages.size() == 0) {  //Need to evict a page
                        
            bool foundPageToEvict = false;
            
            pageStruct *clockPage;
    
            page_table_entry_t *auxTableEntry; 
                        
            while (!foundPageToEvict) {                
                clockPage = clockQueue.front();
                clockQueue.pop();
                
                auxTableEntry = &processTable[clockPage->processID]->pageTable->ptes[clockPage->virtualPage];
                
                if (clockPage->refBit == 1) {
                    auxTableEntry->read_enable = 0;
                    auxTableEntry->write_enable = 0;
                    clockPage->refBit = 0;
                    clockQueue.push(clockPage);
                    
                }
                
                else {
                    foundPageToEvict = true;

                }
                
            }
            
            if (clockPage->modBit == 1) {
                clockPage->modBit = 0;
                unsigned int blockIndex = clockPage->allocatedDiskBlockIndex;
                disk_write(blockIndex, auxTableEntry->ppage);
                
            }
            
            tableEntry->ppage = auxTableEntry->ppage;
            auxTableEntry->ppage = ppageEmptyVal;
            clockPage->residentBit = 0;
            
            zeroFillFunction(newPage, pageTableIndex);

            if (write_flag) {
                tableEntry->write_enable = 1;
                newPage->modBit = 1;
                newPage->zeroBit = 1;
                
            }
            
            tableEntry->read_enable = 1;
            newPage->refBit = 1;
            newPage->residentBit = 1;
            
        }
        
        else {
            tableEntry->ppage = freePhysicalPages.front();
            freePhysicalPages.pop();

            zeroFillFunction(newPage, pageTableIndex);
            
            if (write_flag) {
                tableEntry->write_enable = 1;
                newPage->modBit = 1;
                newPage->zeroBit = 1;
                
            }
            
            tableEntry->read_enable = 1;
            newPage->refBit = 1;
            newPage->residentBit = 1;
            
        }
        
        clockQueue.push(newPage);
        
    }

    else {
        
        pageStruct *residentPage = processTable[currentprocessPID]->validVirtualPages[pageTableIndex];

        if (write_flag) {
            tableEntry->write_enable = 1;
            residentPage->modBit = 1;
            residentPage->zeroBit = 1;
            
        }
        
        else {
            if (residentPage->modBit == 1) {
                tableEntry->write_enable = 1;

            }

        }
            
        tableEntry->read_enable = 1;
        residentPage->refBit = 1;
        
    }

    return 0;
    
}

int vm_syslog(void *message, unsigned int len) {
    
    unsigned long int hexVirtualAddress = (unsigned long int)message;
    
    if (len <= 0) {  
        return -1;
        
    }
    
    else if (hexVirtualAddress < VM_ARENA_BASEADDR_VALUE || (hexVirtualAddress + len - 1) > processTable[currentprocessPID]->maxValidVirtualAddress) {
        return -1;
        
    }

    string s;

    for (unsigned int i = 0; i < len; i++) {

        unsigned int virtualPageNumber = addressToIndexConversion(hexVirtualAddress);
        unsigned int pageOffset = addressToOffsetConversion(hexVirtualAddress);

        if (processTable[currentprocessPID]->pageTable->ptes[virtualPageNumber].read_enable == 0) {
            if (vm_fault ((void*)hexVirtualAddress, false) == -1) {
                return -1;

            }

        }

        unsigned int frame = (unsigned int)(processTable[currentprocessPID]->pageTable->ptes[virtualPageNumber].ppage);
        unsigned int physicalIndex = (frame * VM_PAGESIZE_INT) + pageOffset;

        s += ((char*)pm_physmem)[physicalIndex];

        hexVirtualAddress += 1;
  
    }
    
    cout << "syslog \t\t\t" << s << endl;
    
    return 0;
    
}

void vm_destroy() {

    int queueSize = clockQueue.size();

    pageStruct *auxPage = new (nothrow) pageStruct;
    
    if (auxPage == NULL) {
        return;
        
    }
    
    for (int i = 0; i < queueSize; i++) {
        
        auxPage = clockQueue.front();
        clockQueue.pop();
        
        if (auxPage->processID == currentprocessPID) {
            unsigned int tempVirtPage = auxPage->virtualPage;
            freePhysicalPages.push(processTable[currentprocessPID]->pageTable->ptes[tempVirtPage].ppage);
            
        }
        
        else {
            clockQueue.push(auxPage);
            
        }
        
    }
    
    delete processTable[currentprocessPID]->pageTable;
    
    int numProcessBlocks = processTable[currentprocessPID]->validVirtualPages.size();
    
    for (int i = 0; i < numProcessBlocks; i++) {
        freeBlocks.push(processTable[currentprocessPID]->validVirtualPages[i]->allocatedDiskBlockIndex);
        delete processTable[currentprocessPID]->validVirtualPages[i];
        
    }    
    
    delete processTable[currentprocessPID];

}
