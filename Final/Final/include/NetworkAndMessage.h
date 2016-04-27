#ifndef NETWORKANDMESSAGE_H
#define NETWORKANDMESSAGE_H
#include <iostream>
using namespace std;

struct city{
    string Name;
    string message;
    int pdist;
    int ndist;
    city *next;
    city *previous;

    city(){};

    city(string initName, city *initNext, string initMessage){
        Name = initName;
        next = initNext;
        message = initMessage;
    }
};



class NetworkAndMessage
{
    public:
        NetworkAndMessage();
        ~NetworkAndMessage();

        //network functions
        void sendMessage(string destination);
        int distance(string destination);
        void printNetwork();
        void printCurrent();
        bool searchNetwork(string city);

        //queue/message functions
        void buildQueue(int qs);
        void enqueue(string word);
        void editqueue(int index);
        void deleteQueue();
        void printQueue();
        void dataLoss(int x);
        void printQueueWithIndex();
        bool queueIsFull();
        bool queueIsEmpty();
        int currPoints;

        //game/earn points functions
        void easyMath(int problems);
        bool addition();
        bool subtraction();

        void mediumMath(int problems);
        bool multiplication();
        bool divisoin();

        void hardMath(int problems);
        bool solveForX();


    protected:
    private:
        city *head;
        city *tail;
        city *current;

        int queueSize;
        int queueHead;
        int queueTail;
        int queueCount;
        string *arrayQueue;
};

#endif  // NETWORKANDMESSAGE_H
