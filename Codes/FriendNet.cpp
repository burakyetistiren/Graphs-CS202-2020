#include "FriendNet.h"
#include "Queue.h"
#include <iostream>
#include <fstream>
#include <math.h>
/**
* Author : Burak Yetistiren
* ID: 21802608
* Section : 1
* Assignment : 5
*/
#include <string>
using namespace std;
const int MAX_INT = 2147483647;

FriendNet::FriendNet(const FriendNet& aNet) // copy constructor
{
    people = new Person[aNet.getNumberOfPeople()];

    for( int i = 0; i < aNet.getNumberOfPeople(); ++i)
    {
        Person* p = new Person();
        *p = (aNet.getPeople())[i];
        people[i] = *p;
        numberOfPeople += 1;
    }

}

FriendNet::FriendNet(const string fileName) // constructor
{
    string s = "", newName = "";
    char* input = new char[fileName.size()];
    int noOfPeople = 0, temp = 0, valueToBeAdded = 0, count = 0,
    newId = 0, lengthCount = 0, numberOfFriends = 0, friendId = 0;
    unsigned int j = 0;

    for( unsigned int i = 0; i < fileName.size(); ++i)
        input[i] = fileName[i];

    ifstream inFile;
    inFile.open(input);
    if (!inFile)
    {
        cout << "Unable to open file";
        return;
    }

    else
    {
        getline( inFile, s);

        // Getting number of people in the network
        for( unsigned int i = 0; i < s.size() - 1; ++i)
        {
            temp = s[i] - '0';
            valueToBeAdded = ceil(temp * pow( 10, s.size() - (i + 2)));
            noOfPeople = noOfPeople + valueToBeAdded;
        }

        people = new Person[noOfPeople];
        numberOfPeople = noOfPeople;

        // 2D Array to store friends of people which will be added to them in the end
        //int** friends = new int*[noOfPeople];
        int friends[noOfPeople][noOfPeople];

        s = "";

        while(getline( inFile, s))
        {
            int count1 = 0, j = 0, newId = 0;

            // Initializing person to be added
            Person* p = new Person();

            // Skipping blank spaces if any
            while( s[j] == ' ')
                ++j;

            lengthCount = j;

            // Finding the length of id
            while( s[lengthCount] != ' ')
                ++lengthCount;

            lengthCount = lengthCount - j;

            // Converting id in string to int
            int countPow = 0;
            while( s[j] != ' ')
            {
                temp = s[j] - '0';
                valueToBeAdded = ceil(temp * pow( 10, lengthCount - (countPow + 1)));
                newId = newId + valueToBeAdded;
                ++countPow;
                ++j;
            }

            // Setting ID of the person
            p->setId(newId);

            lengthCount = 0;

            // Skipping blank spaces
            while( s[j] == ' ')
                ++j;

            // Getting the new name
            while( s[j] != ' ')
            {
                newName = newName + s[j];
                ++j;
            }

            // Setting the name of the person
            p->setName(newName);
            newName = "";

            // Skipping blank spaces
            while( s[j] == ' ')
                ++j;

            lengthCount = j;

            // Finding the length of noOfFriends
            while( s[lengthCount] != ' ')
                ++lengthCount;

            lengthCount = lengthCount - j;

            // Converting number of friends in string to int
            countPow = 0;
            while( s[j] != ' ')
            {
                temp = s[j] - '0';
                valueToBeAdded = ceil(temp * pow( 10, lengthCount - (countPow + 1)));
                numberOfFriends = numberOfFriends + valueToBeAdded;
                ++j;
                ++countPow;
            }

            lengthCount = 0;

            // Setting the number of friends of the person
            p->setNoOfFriends(numberOfFriends);
            numberOfFriends = 0;

            //friends[newId] = new int[numberOfFriends];

            // Skipping blank spaces
            while( s[j] == ' ')
                ++j;

            while( j < s.size() - 1)
            {

                // Skipping blank spaces
                while( s[j] == ' ')
                    ++j;

                lengthCount = j;

                // Finding the length of friends id
                while( s[lengthCount] != ' ')
                    ++lengthCount;

                lengthCount = lengthCount - j;


                // Converting friend id in string to int
                countPow = 0, friendId = 0;
                while( s[j] != ' ')
                {
                    temp = s[j] - '0';
                    valueToBeAdded = ceil(temp * pow( 10, lengthCount - (countPow + 1)));
                    friendId = friendId + valueToBeAdded;

                    ++j;
                    ++countPow;
                }

                lengthCount = 0;
                friends[newId][count1] = friendId;;
                count1++;
                ++j;
            }

            s = "";

            // Adding person to the list
            people[count] = *p;

            count++;
            delete p;
        }
        inFile.close();

        for( int i = 0; i < noOfPeople; ++i)
        {
            Person* cur = new Person();
            cur = &people[i];
            for( int k = 0; k < people[i].getNoOfFriends(); ++k)
            {
                Person* newPerson = new Person();

                if( people[i].getNoOfFriends() == 0)
                    people[i].setNextNull();
                else
                {
                    *newPerson = people[friends[i][k]];
                    newPerson->setNextNull();
                    cur->setNext(*newPerson);
                    cur = cur->getNext();
                }
                newPerson = NULL;
                delete newPerson;
            }
            cur = NULL;
            delete cur;
        }



    }
    delete [] input;

}

Person* FriendNet::getPeople() const {return people;}

FriendNet::~FriendNet() { delete [] people;}// destructor

void FriendNet::listFriends(const string personName, const int hopNo)
{
    int index = 0, count = 0;
    bool found = false;
    string* names = new string[getNumberOfPeople()];

    for( int i = 0; i < numberOfPeople; ++i)
        if( people[i].getName() == personName)
        {
           found = true;
           index = i;
        }
    for( int j = 0; j < getNumberOfPeople(); ++j)
        names[j] = "";

    if( !found)
        cout << personName << " does not exist in the network." << endl;
    else
    {
        cout << "People accessible from " << people[index].getName() << " within "
        << hopNo << " hops: ";
        if( people[index].getNoOfFriends() == 0 || hopNo <= 0)
        {
            cout << "NOBODY" << endl;
            return;
        }
        else
        {
            bool visited[getNumberOfPeople()];
            for( int i = 0; i < getNumberOfPeople(); ++i)
                visited[i] = false;
            dfs( visited, index, hopNo, names, count);
        }

    }
    cout << endl;
    delete [] names;
}

void FriendNet::displayAverageDegrees()
{
    int count = 0, totalDegree = 0, noOfVertex = 0;
    int vertexValues[getNumberOfPeople() + 1];
    int degreeValues[getNumberOfPeople() + 1];
    double averages[getNumberOfPeople() + 1];
    bool* visited = new bool[getNumberOfPeople()];

    for( int i = 0; i < getNumberOfPeople(); ++i)
    {
        visited[i] = false;
        vertexValues[i] = 0;
        degreeValues[i] = 0;
        averages[i] = 0;
    }


    for( int m = 0; m < getNumberOfPeople(); ++m)
    {
        if(!visited[m])
        {
            dfs( visited, m);
            count += 1;

            for( int k = 0; k < getNumberOfPeople(); ++k)
            {
                if( visited[k])
                {
                    noOfVertex += 1;
                    totalDegree = totalDegree + people[k].getNoOfFriends();
                }
            }
            vertexValues[count] = noOfVertex;
            degreeValues[count] = totalDegree;

            noOfVertex = noOfVertex - vertexValues[count - 1];
            totalDegree = totalDegree - degreeValues[count - 1];
            averages[count - 1] = ((double)totalDegree / noOfVertex);

        }
        noOfVertex = 0;
        totalDegree = 0;
    }
    cout << "There are " << count << " " <<
    "connected components. The average degrees are:" << endl;

    for( int n = 0; n < count; ++n)
    {
        cout << "For component " << n << ": " << averages[n] << endl;
    }
    delete [] visited;
}

void FriendNet::dfs(bool*& visited, const int iden)
{
    visited[iden] = true;
    for( Person* cur = people[iden].getNext(); cur; cur = cur->getNext())
        if(!visited[cur->getId()])
            dfs(visited, cur->getId());
}

void FriendNet::dfs(bool visited[], const int iden, const int & hops, string*& names, int &count)
{
    int decremented = hops;
    bool found = false;

    if( decremented == 0)
        return;
    visited[iden] = true;
    for( Person* cur = people[iden].getNext(); cur; cur = cur->getNext())
    {
        if(!visited[cur->getId()])
        {
            if( decremented > 0)
            {
                for( int i = 0; i < getNumberOfPeople(); ++i)
                    if( cur->getName() == names[i])
                        found = true;
                if( !found)
                {
                    names[count] = cur->getName();
                    if(count == 0)
                        cout << cur->getName();
                    else
                        cout << ", " << cur->getName();
                    count += 1;
                }

                decremented--;
                found = false;
            }
        dfs(visited, cur->getId(), decremented, names, count);
        decremented++;
        }
    }
}

void FriendNet::bfs( bool*& visited, const int source, int *&distances)
{
    Queue* q = new Queue(getNumberOfPeople());

    for( int i = 0; i < getNumberOfPeople(); i++)
    {
        visited[i] = false;
        distances[i] = MAX_INT;
    }

    visited[source] = true;
    distances[source] = 0;
    q->enqueue(people[source]);;

    while(!(q->isEmpty()))
    {
        Person p;
        p = people[q->getFront().getId()];
        q->dequeue();

        for( Person* cur = people[p.getId()].getNext(); cur; cur = cur->getNext())
        {

            if( !visited[cur->getId()])
            {
                visited[cur->getId()] = true;
                distances[cur->getId()] = distances[p.getId()] + 1;
                q->enqueue(*cur);
            }

        }
    }
    delete q;



}

void FriendNet::displayDiameters()
{
    int count = 0, increment = 0;
    bool* visited = new bool[getNumberOfPeople()];
    bool* bfsVisited = new bool[getNumberOfPeople()];
    int* distances = new int[getNumberOfPeople()];

    for( int i = 0; i < getNumberOfPeople(); ++i)
        visited[i] = false;


    for( int j = 0; j < getNumberOfPeople(); ++j)
    {
        if(!visited[j])
        {
            dfs( visited, j);
            count += 1;
        }
    }
    int locations[count];
    int diameters[count];
    for( int k = 0; k < count; ++k)
    {
        diameters[k] = -1;
    }

    for( int l = 0; l < getNumberOfPeople(); ++l)
        visited[l] = false;

    for( int m = 0; m < getNumberOfPeople(); ++m)
    {
        if(!visited[m])
        {
            dfs( visited, m);
            locations[increment] = m;
            increment += 1;
        }

    }

    increment = 0;

    for(int n = 0; n < count; ++n)
    {
        for( int s = 0; s < getNumberOfPeople(); ++s)
            visited[s] = false;
        dfs( visited, locations[n]);
        for( int o = 0; o < getNumberOfPeople(); ++o)
        {
            if( visited[o])
            {
                bfs(bfsVisited, o, distances);
                for( int p = 0; p < getNumberOfPeople(); ++p)
                {
                    if( distances[p] != MAX_INT)
                    {
                        if( distances[p] > diameters[n])
                            diameters[n] = distances[p];
                    }
                }
            }
        }

    }

    cout << "There are " << count << " " <<
    "connected components. The diameters are:" << endl;

    for( int r = 0; r < count; ++r)
    {
        cout << "For component " << r << ": " << diameters[r] << endl;
    }
    delete [] visited;
    delete [] bfsVisited;
    delete [] distances;
}

int FriendNet::getNumberOfPeople() const { return numberOfPeople;}

