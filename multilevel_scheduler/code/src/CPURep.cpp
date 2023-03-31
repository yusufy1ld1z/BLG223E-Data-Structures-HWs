/* @Author
Student Name: Yusuf YILDIZ
Student ID : 150210006
Date: 26.10.2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
    this->mFinishedProcess = new FIFORep();
}

CPURep::~CPURep()
{
    delete this->mFinishedProcess; // delete allocated variables with new.
    this->mFinishedProcess = NULL;
}

ProcessRep *CPURep::runCPU(ProcessRep *p, int time)
{
    if (p->remainingTime == p->getProcessTime()) // if it is first arrival
        p->startTime = time;

    p->remainingTime--; // run the process.
    if (p->remainingTime <= 0)
    {
        p->endTime = time + 1;
        this->mFinishedProcess->queue(p); // if process is done then add it to finished process.
        return NULL;
    }
    else
        return p;
}

FIFORep *CPURep::getFinishedProcess()
{
    return this->mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep *finishedProcess)
{
    this->mFinishedProcess = finishedProcess;
}