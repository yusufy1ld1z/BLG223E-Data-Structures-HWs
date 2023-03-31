/* @Author
Student Name: Yusuf YILDIZ
Student ID : 150210006
Date: 26.10.2022
*/
#ifndef _FIFOREP
#define _FIFOREP

#include <iostream>
#include <stdio.h>
#include "ProcessRep.h"
class FIFORep
{
    /*
        The class construct a FIFO queue.
    */

private:
    ProcessRep *mpHead;
    ProcessRep *mpTail;

public:
    FIFORep();
    FIFORep(ProcessRep *);
    ~FIFORep();

    void setHead(ProcessRep *);
    ProcessRep *getHead();

    void setTail(ProcessRep *);
    ProcessRep *getTail();

    void queue(ProcessRep *);
    ProcessRep *dequeue();

    ProcessRep *searchID(int);
    void printFIFO();
};

#endif