#pragma once
#include "TemporaryEmployee.h"
using namespace std;

class CircularArrayLinkedList
{
public:
    Employee* Carray[20];
    int Size = 20;
    int front = -1; 
    int back = -1;
    CircularArrayLinkedList(){}

    int isFull() {
        if ((front == back + 1) || (front == 0 && back == (Size - 1))) {
            return 1;
        }
        return 0;
    }
    int isEmpty() {
        if (front == -1) { 
            return 1; }
        return 0;
    }

    void addTEmployee(TemporaryEmployee te)
    {
        if (front == -1) {
            front = 0;
        }
        back = (back + 1) % Size;
        Carray[back] = &te;
    }

    Employee* deleteTemployee(int ID)
    {
        Employee* out{};
        if (isEmpty()) {
            cout << "You can't delete because you don't have any Temporary Employee" << endl;
        }
        if (front == back) {
            front = -1;
            back = -1;
        }
        else {
            int i;
            for (i = front; i != back; i = (i + 1) % Size) {
                if (Carray[i]->getID() == ID) {
                    out = Carray[i];
                    for (i; i != back; i = (i + 1) % Size) {
                        Carray[i] = Carray[i + 1];
                    }
                    back = (back - 1) % Size;
                }
            }
        }
        cout << "Employee has been sucsessfully deleted" << endl;
        return out;
    }

    void findTemployee(int ID) {
        int i;
        for (i = front; i != back; i = (i + 1) % Size) {
            if (Carray[i]->getID() == ID) {
                cout << Carray[i];
            }
        }
    }

    void List() {
        int i;
        for (i = front; i != back; i = (i + 1) % Size) {
            cout << Carray[i];
        }
        cout << Carray[i];
    }
};