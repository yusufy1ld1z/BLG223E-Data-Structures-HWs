/* @Author
Student Name: Yusuf YILDIZ
Student ID : 150210006
Date: 26.10.2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
    this->mpHead = NULL;
    this->mpTail = NULL;
}

FIFORep::FIFORep(ProcessRep *head)
{
    this->mpHead = head;
    this->mpTail = head;
}

FIFORep::~FIFORep()
{
    ProcessRep *current = this->getHead(); // delete allocated objects and set deleted pointers to null.
    while (current != NULL)
    {
        ProcessRep *next = current->getNext();
        delete current;
        current = next;
    }
    this->mpHead = NULL;
    this->mpTail = NULL;
}

void FIFORep::setHead(ProcessRep *head)
{
    this->mpHead = head;
}

ProcessRep *FIFORep::getHead()
{
    return this->mpHead;
}

void FIFORep::setTail(ProcessRep *tail)
{
    this->mpTail = tail;
}

ProcessRep *FIFORep::getTail()
{
    return this->mpTail;
}

void FIFORep::queue(ProcessRep *p)
{
    /*
        The function add a process to the tail of the queue.
    */
    if (this->mpHead == NULL) // if it contains no item then initialize head and tail to coming object.
    {
        this->mpHead = p;
        this->mpTail = p;
    }
    else
    {
        this->mpTail->setNext(p);
        this->mpTail = this->mpTail->getNext();
    }
}

ProcessRep *FIFORep::dequeue()
{
    /*
        The function remove a process from the head of the queue and returns it.
    */
    if (this->mpHead == NULL)
    {
        this->mpTail = NULL;
        return NULL;
    }
    ProcessRep *oldRep = this->mpHead;
    this->mpHead = this->mpHead->getNext();
    if (this->mpHead == NULL) // if there is just one item and no more, then change tail and head with null
    {
        this->mpTail = NULL;
    }
    oldRep->setNext(NULL);

    return oldRep;
}

ProcessRep *FIFORep::searchID(int id)
{
    /*
        The function search a process by id and returns it if it exist otherwise returns NULL.
    */
    if (this->mpHead == NULL)
        return NULL;

    ProcessRep *temp = this->getHead();
    while (temp != NULL)
    {
        if (temp->getProcessID() == id)
            return temp;
        else
            temp = temp->getNext();
    }

    return NULL;
}

void FIFORep::printFIFO()
{
    /*
        The function prints the proceses in the queue starting from Head to tail.
    */
    ProcessRep *temp = this->mpHead;
    while (temp != NULL)
    {
        cout << temp->getProcessType() << temp->getProcessID() << " " << temp->startTime << " " << temp->endTime << " ";
        temp = temp->getNext();
    }
}