#include "Stack.h"
#include <iostream>

// Constructor to initialize an empty stack
Stack::Stack() {
    // TODO: Your code here
    top = -1;
}

// Adds a province to the top of the stack
void Stack::push(int province) {
    // TODO: Your code here
    if (getSize() < MAX_SIZE) {
            data[++top] = province;
        } else {
            return;
        }
}

// Removes and returns the top province from the stack
int Stack::pop() {
    // TODO: Your code here
    if (isEmpty()) {
        return -1;
    }
    return data[top--];
}

// Returns the top province without removing it
int Stack::peek() const {
    // TODO: Your code here
    if (isEmpty()) {
        return -1;
    }
    return data[top];
}

// Checks if the stack is empty
bool Stack::isEmpty() const {
    // TODO: Your code here
    return (top < 0);
}

// Function to get the current size of the stack
int Stack::getSize() const {
    // TODO: Your code here
    return (top + 1);
}
