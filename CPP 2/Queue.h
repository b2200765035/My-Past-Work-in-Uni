#ifndef QUEUE_H
#define QUEUE_H

#include <string>

#define MAX_QUEUE_SIZE 200  // // TO DO: Define a maximum size for the queue to control memory usage considering the problem at hand
//81 seems to makes sense sice it is the number of provinces we have but is that really the expected answer?

class Queue {

public:
    int front, rear;          // Indices for the front and rear elements of the queue
    int data[MAX_QUEUE_SIZE]; // Static array to store provinces as integers (province IDs) 
    
    Queue();                  // Constructor to initialize the queue

    // Adds a province to the end of the queue
    void enqueue(int province);

    // Removes and returns the front province from the queue
    int dequeue();

    // Returns the front province without removing it
    int peek() const;

    // Checks if the queue is full
    bool isFull() const;

    // Checks if the queue is empty
    bool isEmpty() const;

    // Add a priority province
    void enqueuePriority(int province);
};

#endif // QUEUE_H
