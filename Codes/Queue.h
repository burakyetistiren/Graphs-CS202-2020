#ifndef __QUEUE_H
#define __QUEUE_H
#include "Person.h"
/**
* Author : Burak Yetistiren
* ID: 21802608
* Section : 1
* Assignment : 5
*/
#include <string>
using namespace std;

class Queue{
    public:
        Queue(int noOfPeople);
        ~Queue();
        bool isEmpty() const;
        bool isFull() const;
        int getSize() const;
        Person getFront() const;
        Person getBack() const;
        void enqueue(Person &p);
        void dequeue();
        void display();

    private:
        Person* queue;
        int numberOfPeople;
        int size;
};
#endif // __QUEUE_H
