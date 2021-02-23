#include "Person.h"
#include <iostream>
/**
* Author : Burak Yetistiren
* ID: 21802608
* Section : 1
* Assignment : 5
*/
#include <string>
using namespace std;

Person::Person()
{
    id = -1;
    noOfFriends = 0;
    name = "";
    next = NULL;
}

Person::Person(int id, int noOfFriends, string name, Person* next)
{
    this->id = id;
    this->noOfFriends = noOfFriends;
    this->name = name;
    this->next = next;
}

Person::~Person()
{
//    delete next;
}

void Person::operator=(const Person& right)
{
    id = right.id;
    noOfFriends = right.noOfFriends;
    name = right.name;

    Person* cur = right.next;
    next = cur;
    while(cur)
    {
        Person* newPerson = new Person( cur->getId(), cur->getNoOfFriends(),
                                        cur->getName(), cur->getNext());
        cur = newPerson;
        cur = cur->next;

        cur = NULL;
        newPerson = NULL;
        delete newPerson;
        delete cur;
    }

}

int Person::getId(){ return id;}

int Person::getNoOfFriends(){ return noOfFriends;}

string Person::getName(){ return name;}

Person* Person::getNext(){ return next;}

void Person::setId( int newId){ id = newId;}

void Person::setNoOfFriends( int newNoOfFriends){ noOfFriends = newNoOfFriends;}

void Person::setName( string newName){ name = newName;}

void Person::setNext( Person &p){ next = &p;}

void Person::setNextNull(){ next = NULL;}

