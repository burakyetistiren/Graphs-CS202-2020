#include "Queue.h"
#include <iostream>
/**
* Author : Burak Yetistiren
* ID: 21802608
* Section : 1
* Assignment : 5
*/
#include <string>
using namespace std;

Queue::Queue(int noOfPeople)
{
    size = noOfPeople;
    numberOfPeople = 0;
    queue = new Person[noOfPeople];
}

Queue::~Queue()
{
    delete [] queue;
}

bool Queue::isEmpty() const { return numberOfPeople == 0;}

bool Queue::isFull() const { return numberOfPeople == size;}

int Queue::getSize() const{ return numberOfPeople;}

Person Queue::getFront() const{return queue[0];}

Person Queue::getBack() const{return queue[numberOfPeople - 1];}

void Queue::enqueue(Person &p)
{
    Person* newPerson = new Person();
    *newPerson = p;

    if( !isFull())
    {
        queue[numberOfPeople] = *newPerson;
        numberOfPeople += 1;
    }
    else
        cout <<  "Queue is full" << endl;

    delete newPerson;
}

void Queue::dequeue()
{
    if( !isEmpty())
    {
        for( int i = 0; i < getSize() - 1; ++i)
            queue[i] = queue[i + 1];
        numberOfPeople -= 1;
    }
    else
        cout << "Queue is empty" << endl;
}

void Queue::display()
{
    if( numberOfPeople == 0)
        cout << "Queue is empty, nothing to display." << endl;
    else
        for( int i = 0; i < numberOfPeople; ++i)
            cout << i << ") " << queue[i].getName() << endl;
    cout << endl;
}

