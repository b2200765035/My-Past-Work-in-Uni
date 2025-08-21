#pragma once
#include "PermanentEmployee.h"
using namespace std;

//I've decided to store employee here as I'll sort and print from here
class DoubleLinkedDynamicList
{
public:
    struct node {
        struct node* prev;
        Employee* employee;
        struct node* next;
    };
    typedef struct node* NODEPTR;

    NODEPTR getnode()
    {
        NODEPTR p;
        p = new node;
        return p;
    }

    void freenode(NODEPTR p)
    {
        delete p;
    }

    void insertfront(NODEPTR head, Employee employee)
    {
        NODEPTR nnode;
        nnode = getnode();

        nnode->employee = &employee;

        nnode->next = (head);
        nnode->prev = NULL;

        (head) = nnode;
    }

    void deleteNode(NODEPTR* head_ref, NODEPTR del)
    {
        if (*head_ref == NULL || del == NULL)
            return;

        if (*head_ref == del)
            *head_ref = del->next;

        if (del->next != NULL)
            del->next->prev = del->prev;

        if (del->prev != NULL)
            del->prev->next = del->next;

        free(del);
    }

    void deleteTemp(NODEPTR* head_ref)
    {
        if ((*head_ref) == NULL) {
            return;
        }

        NODEPTR current = *head_ref;
        NODEPTR next;

        while (current != NULL) {

            if (current->employee->getPermanancy() == false) {

                next = current->next;

                deleteNode(head_ref, current);

                current = next;
            }

            else
                current = current->next;
        }
    }

    NODEPTR deleteID(NODEPTR* head_ref, int ID)
    {
        NODEPTR next{};
        if ((*head_ref) == NULL) {
            cout << "There is no employee with that ID" << endl;
            return next;
        }


        NODEPTR current = *head_ref;
        

        while (current != NULL) {

            if (current->employee->getID() == ID) {
                next = current->next;
                return current;
                deleteNode(head_ref, current);
                current = next;
            }

            else
                current = current->next;
        }
        return current;
    }

    int search(NODEPTR* head_ref, int ID)
    {
        NODEPTR temp = *head_ref;

        int pos = 0;

        while (temp->employee->getID() != ID && temp->next != NULL) {
            pos++;
            temp = temp->next;
        }

        if (temp->employee->getID() != ID)
            return -1;

        return 0;
    }


    void IDsort(NODEPTR head) {
        NODEPTR n1;
        NODEPTR n2;
        for (n1 = head; n1->next != head; n1 = n1->next) {
            for (n2 = n1->next; n2 != head; n2 = n2->next) {
                if (n1->employee->getID() < n2->employee->getID()) {
                    NODEPTR X1;
                    NODEPTR X2;
                    X1 = n1->prev;
                    X2 = n1->next->next;
                    n2 = n1->next;
                    n2->prev = n1->prev;
                    n1->prev = n1->next;
                    n1->next = n2->next;
                    n2->next = n1;
                    X1->next = n1->prev;
                    X2->prev = n1;
                }
            }
        }
    }

    void Appointsortntoo(NODEPTR head) {
        NODEPTR n1;
        NODEPTR n2;
        for (n1 = head; n1->next != head; n1 = n1->next) {
            for (n2 = n1->next; n2 != head; n2 = n2->next) {
                if (n1->employee->getAppointment() < n2->employee->getAppointment()) {
                    NODEPTR X1;
                    NODEPTR X2;
                    X1 = n1->prev;
                    X2 = n1->next->next;
                    n2 = n1->next;
                    n2->prev = n1->prev;
                    n1->prev = n1->next;
                    n1->next = n2->next;
                    n2->next = n1;
                    X1->next = n1->prev;
                    X2->prev = n1;
                }
            }
        }
    }

    void Appointsortoton(NODEPTR head) {
        NODEPTR n1;
        NODEPTR n2;
        for (n1 = head; n1->next != head; n1 = n1->next) {
            for (n2 = n1->next; n2 != head; n2 = n2->next) {
                if (n1->employee->getAppointment() > n2->employee->getAppointment()) {
                    NODEPTR X1;
                    NODEPTR X2;
                    X1 = n1->prev;
                    X2 = n1->next->next;
                    n2 = n1->next;
                    n2->prev = n1->prev;
                    n1->prev = n1->next;
                    n1->next = n2->next;
                    n2->next = n1;
                    X1->next = n1->prev;
                    X2->prev = n1;
                }
            }
        }
    }

    void displayList(NODEPTR node) {
        NODEPTR last;

        while (node != NULL) {
            cout << node->employee;
            last = node;
            node = node->next;
        }
        if (node == NULL)
            cout << "NULL";
    }

    void displayAppoint(NODEPTR node, Date appointment) {
        NODEPTR last;

        while (node != NULL) {
            if (node->employee->getAppointment() > appointment) {
                cout << node->employee;
            }
            last = node;
            node = node->next;
        }
        if (node == NULL)
            cout << "NULL";
    }

    void displayYear(NODEPTR node, int year) {
        NODEPTR last;

        while (node != NULL) {
            if (node->employee->getAppointYear() == year) {
                cout << node->employee;
            }
            last = node;
            node = node->next;
        }
        if (node == NULL)
            cout << "NULL";
    }

    void displayBirth(NODEPTR node, Date birth) {
        NODEPTR last;

        while (node != NULL) {
            if (node->employee->getBirth() < birth) {
                cout << node->employee;
            }
            last = node;
            node = node->next;
        }
        if (node == NULL)
            cout << "NULL";
    }

    void displayMonth(NODEPTR node, int month) {
        NODEPTR last;

        while (node != NULL) {
            if (node->employee->getBrithMonth() == month) {
                cout << node->employee;
            }
            last = node;
            node = node->next;
        }
        if (node == NULL)
            cout << "NULL";
    }
};

