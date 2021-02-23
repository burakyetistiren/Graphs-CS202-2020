#ifndef __PERSON_H
#define __PERSON_H
/**
* Author : Burak Yetistiren
* ID: 21802608
* Section : 1
* Assignment : 5
*/
#include <string>
using namespace std;

class Person{
    public:
        Person();
        Person(int id, int noOfFriends, string name, Person* next);
        ~Person();
        void operator=(const Person& right);
        int getId();
        int getNoOfFriends();
        string getName();
        Person* getNext();
        void setId( int newId);
        void setNoOfFriends( int newNoOfFriends);
        void setName( string newName);
        void setNext( Person &p);
        void setNextNull();

    private:
        int id;
        int noOfFriends;
        string name;
        Person* next;

};
#endif // __PERSON_H
