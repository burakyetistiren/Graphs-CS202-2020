#ifndef __FRIEND_NET_H
#define __FRIEND_NET_H
#include "Person.h"
/**
* Author : Burak Yetistiren
* ID: 21802608
* Section : 1
* Assignment : 5
*/
#include <string>
using namespace std;

class FriendNet{
    public:
        FriendNet(const string fileName); // constructor
        FriendNet(const FriendNet& aNet); // copy constructor
        ~FriendNet(); // destructor
        void listFriends(const string personName, const int hopNo);
        void displayAverageDegrees();
        void displayDiameters();
        int getNumberOfPeople() const;
        Person* getPeople() const;
        void dfs( bool visited[], const int iden, const int& hops,
                 string*& names, int &count);
        void dfs( bool*& visited, const int iden);
        void bfs( bool*& visited, const int iden, int *&distances);

    private:
        Person* people;
        int numberOfPeople;
};
#endif // __FRIEND_NET_H
