/* @Author
Student Name: Yusuf YILDIZ
Student ID : 150210006
Date: 26.10.2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
    this->totalTime = 0; // initialize all values
    this->timeSliceCount = 0;
    this->pCpuObj = new CPURep();
    for (int i = 0; i < 3; i++)
    {
        mpProcessFIFO[i] = new FIFORep();
    }
}
SchedulerRep::~SchedulerRep()
{
    delete pCpuObj; // delete all attributes allocated with new.
    pCpuObj = NULL;
    for (int i = 0; i < 3; i++)
    {
        delete this->mpProcessFIFO[i];
        this->mpProcessFIFO[i] = NULL;
    }
    delete this->mpRunningProcess;
    this->mpRunningProcess = NULL;
}

FIFORep *SchedulerRep::getProcessFIFO(int index)
{
    return this->mpProcessFIFO[index];
}

void SchedulerRep::setProcessFIFO(FIFORep *fifo, int index)
{
    this->mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep *p)
{
    this->mpRunningProcess = p;
}

ProcessRep *SchedulerRep::getRunningProcess()
{
    return this->mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep *p)
{
    string type = p->getProcessType(); // add the process to FIFO with respect to its process type.
    if (type == "A")
        this->getProcessFIFO(0)->queue(p);
    else if (type == "B")
        this->getProcessFIFO(1)->queue(p);
    else if (type == "C")
        this->getProcessFIFO(2)->queue(p);
    else
        return;
}

ProcessRep *SchedulerRep::popProcess()
{
    ProcessRep *temp = this->getProcessFIFO(0)->dequeue(); // get process from FIFO according to the priority rules.

    if (temp)
    {
        return temp;
    }
    else
    {
        temp = this->getProcessFIFO(1)->dequeue(); // if there is no job A then look for job B.
    }

    if (temp)
    {
        return temp;
    }
    else
    {
        temp = this->getProcessFIFO(2)->dequeue(); // if there is no job B then look for job C.
    }
    if (temp)
    {
        return temp;
    }

    return NULL; // if there is no job then return NULL.
}

bool SchedulerRep::checkTimeSlice()
{
    ProcessRep *current = this->getRunningProcess();
    if (current != NULL) // if there is a running process then control if it is reached to time limit.
    {
        string currentProcType = current->getProcessType();
        if (currentProcType == "A")
        {
            if (this->timeSliceCount == 2) // time limit is 2 for type A.
                return true;
        }
        else if (currentProcType == "B") // time limit is 4 for type B.
        {
            if (this->timeSliceCount == 4)
                return true;
        }
        else if (currentProcType == "C") // time limit is 8 for type C.
        {
            if (this->timeSliceCount == 8)
                return true;
        }
    }
    return false; // return false either no job reaches to time limit or there is no running process.
}

ProcessRep *SchedulerRep::sendProcessToCPU(ProcessRep *p)
{
    this->mpRunningProcess = this->pCpuObj->runCPU(p, this->totalTime); // it runs the process
    if (this->mpRunningProcess == NULL)                                 // if the running process reaches the end
    {
        this->mpRunningProcess = popProcess(); // take a new process from fifo.
        this->timeSliceCount = 0;
    }
    else
        this->timeSliceCount += 1; // if running process continues run in cpu, increase time slice by one.
    return this->mpRunningProcess;
}

void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{
    /*
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run.
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will
                be put back to the queue first.


    */
    ProcessRep *process = new ProcessRep(type, id, arrivalTime, processTime);
    int currentPriority, newPriority;

    this->pushProcess(process);         // add new process to fifo.
    if (this->mpRunningProcess == NULL) // if there is no running process take a new process from fifo.
        this->mpRunningProcess = this->popProcess();
    else
    {
        if (this->checkTimeSlice())
        {                                                // if the process gets limit
            this->pushProcess(this->mpRunningProcess);   // add to fifo again
            this->mpRunningProcess = this->popProcess(); // take new process from fifo
            this->timeSliceCount = 0;                    // set quantum 0 again
        }
        else
        {
            string newProcType = process->getProcessType();
            string curProcType = this->getRunningProcess()->getProcessType();
            if (newProcType == "A")
                newPriority = 2;
            else if (newProcType == "B")
                newPriority = 1;
            else if (newProcType == "C")
                newPriority = 0;
            // determine the priority level for both current process and new process.
            if (curProcType == "A")
                currentPriority = 2;
            else if (curProcType == "B")
                currentPriority = 1;
            else if (curProcType == "C")
                currentPriority = 0;

            if (newPriority > currentPriority) // if priority of new process higher than current, change each other.
            {                                  // change the process
                this->pushProcess(this->mpRunningProcess);
                this->mpRunningProcess = this->popProcess();
                this->timeSliceCount = 0;
            }
        }
    }
    if (this->getRunningProcess() != NULL)
    {
        this->sendProcessToCPU(this->getRunningProcess()); // if running process is not null then we can send it to cpu
                                                           // if it is still null than there is no process to run in cpu just increase total time.
    }

    this->totalTime += 1;
}
void SchedulerRep::schedule(ProcessRep *p)
{
    /*
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run.
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will
                be put back to the queue first.


    */
    if (this->mpRunningProcess == NULL)
        this->mpRunningProcess = this->popProcess(); // take process from fifo
    else
    {
        if (this->checkTimeSlice()) // control whether running process gets time limit.
        {
            this->pushProcess(this->mpRunningProcess);
            this->mpRunningProcess = this->popProcess();
            this->timeSliceCount = 0;
        }
    }
    if (this->getRunningProcess() != NULL)
    {
        this->sendProcessToCPU(this->getRunningProcess()); // if there is a process to run then send it to cpu.
    }

    this->totalTime += 1;
}
