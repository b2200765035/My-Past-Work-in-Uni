#include "Queue.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor to initialize an empty queue
Queue::Queue() {
    // TODO: Your code here
    front = -1;
    rear = -1;
}

// Adds a province to the end of the queue
void Queue::enqueue(int province) {
    // TODO: Your code here
    // Implement circular structure
    // Add the province
    if (isFull ()) {
        printf("\nQueue is Full");
        return;
    }
	if (front == -1) {
        // Inserting first element
	    front = 0;
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = province;
}

// Removes and returns the front province from the queue
int Queue::dequeue() {
    // TODO: Your code here
    int element;
    if (isEmpty()) {
        printf("\nQueue is Empty");
        return -1;
    }
    element = data[front];
	if (front == rear) {
	    front = -1;
	    rear = -1;
	} else {
	    front = (front + 1) % MAX_QUEUE_SIZE;
	}
	return element;
}

// Returns the front province without removing it
int Queue::peek() const {
    // TODO: Your code here
    int element;
    if (isEmpty()) {
        printf("\nQueue is Empty");
        return -1;
    }
    element = data[front];
	return element;
}

// Checks if the queue is full
bool Queue::isFull() const {
    return ((front == 0 && rear == MAX_QUEUE_SIZE - 1) || (rear == (front - 1) % (MAX_QUEUE_SIZE - 1)));
}

// Checks if the queue is empty
bool Queue::isEmpty() const {
    // TODO: Your code here
    return (front == -1);
}

// Add a priority neighboring province in a way that will be dequeued and explored before other non-priority neighbors
void Queue::enqueuePriority(int province) {
    // TODO: Your code here
    if (isFull ()) {
        printf("\nQueue is Full");
        return;
    }
    if (front == -1) {
        // Inserting first element
        front = 0;
        rear = (rear + 1) % MAX_QUEUE_SIZE;
        data[rear] = province;
    } else {
        front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
        data[front] = province;
    }
}

