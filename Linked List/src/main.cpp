#include <iostream>
struct flat{
    int flat_ID = 0;
    int initial_Bandwidth = 0;
    bool is_Empty = false;

    // Points to the next flat.
    struct flat* next = NULL;
    // Points to the previous flat.
    struct flat* prev = NULL;
};

struct apartment{
    char apartment_ID = ' ';
    int max_Bandwidth = 0;
    int curr_Bandwidth = 0;
    bool is_Head = false;
    bool is_Tail = false;
    struct flat* flat_List = NULL;

    // Points to the next apartment.
    struct apartment* next;
};

struct apartment* addHead(struct apartment* tail, char apartment_ID, int max_Bandwidth){
    // Creating a node dynamically.
    auto* temp = (struct apartment*)malloc(sizeof(struct apartment));

    // Assigning the data.
    temp->apartment_ID = apartment_ID;
    temp->max_Bandwidth = max_Bandwidth;
    temp->curr_Bandwidth = 0;
    temp->is_Head = true;
    temp->is_Tail = true;
    tail = temp;


    // Note : list was empty. We link single node to itself.
    temp->next = tail;

    return tail;
}

struct apartment* addAfter(struct apartment* tail, char apt, char apartment_ID, int max_Bandwidth){
    struct apartment *temp, *p;
    p = tail->next;

    //Searching
    do {
        if (p->apartment_ID == apt) {
            // Creating a node dynamically.
            temp = (struct apartment*)malloc(sizeof(struct apartment));

            // Assigning the data.
            temp->apartment_ID = apartment_ID;
            temp->max_Bandwidth = max_Bandwidth;
            temp->curr_Bandwidth = 0;
            temp->is_Head = false;

            if (p->is_Tail){
                // Assigning the data.
                p->is_Tail = false;
                temp->is_Tail = true;

                // Adjusting the links.
                temp->next = tail->next;
                tail->next = temp;
                tail = temp;

            } else {
                // Assigning the data.
                temp->is_Tail = false;

                // Adjusting the links.
                temp->next = p->next;

                // Adding newly allocated node after p.
                p->next = temp;
            }
            // Checking for the last node.
            if (p == tail)
                tail = temp;

            return tail;
        }
        p = p->next;
    } while (p != tail->next);

    std::cout << apt << " not present in the list." << std::endl;
    return tail;
}

struct apartment* addBefore(struct apartment* tail, char apt, char apartment_ID, int max_Bandwidth){
    struct apartment *temp, *p;
    p = tail->next;
    int pos = 0;

    //Searching
    while(p->apartment_ID != apt){
        p = p->next;
        pos++;
    }

    //Returning to start
    p = tail->next;
    while(pos > 1){
        p = p->next;
        pos--;
    }

    // Creating a node dynamically.
    temp = (struct apartment*)malloc(sizeof(struct apartment));

    // Assigning the data.
    temp->apartment_ID = apartment_ID;
    temp->max_Bandwidth = max_Bandwidth;
    temp->curr_Bandwidth = 0;
    temp->is_Tail = false;

    if(p->is_Head){
        p->is_Head = false;
        temp->is_Head = true;
        temp -> next = tail -> next;
        tail -> next = temp;
    }else{
        // Assigning the data.
        temp->is_Head = false;
        temp -> next = p -> next;
        p -> next = temp;
    }
    return tail;
}

struct apartment* addFlat(struct apartment* tail, char apartment_ID, int index, int initial_Bandwidth, int flat_ID){
    struct apartment *p;
    struct flat *f, *f2;
    p = tail->next;

    //Finding the apartment
    while(p->apartment_ID != apartment_ID){
        p = p->next;
    }

    // Creating a node dynamically.
    auto* temp = (struct flat*)malloc(sizeof(struct flat));

    // Assigning the data.
    temp->flat_ID = flat_ID;
    if(p->max_Bandwidth > p->curr_Bandwidth){
        temp->is_Empty = true;
        int i = p->max_Bandwidth - p->curr_Bandwidth;
        if(i > initial_Bandwidth){
            temp->initial_Bandwidth = initial_Bandwidth;
            p->curr_Bandwidth += initial_Bandwidth;
        } else {
            temp->initial_Bandwidth = i;
            p->curr_Bandwidth += i;
        }
    }else{
        temp->initial_Bandwidth = 0;
        temp->is_Empty = true;
    }

    //p is now the apartment
    f = p->flat_List;

    //Finding the new flat's position
    while(index != 1){
        f = f -> next;
        index--;
    }
    if (f -> next == NULL){
        f -> next = temp;
        temp -> prev = f;
    }else{
        f2 = f -> next;
        f -> next = temp;
        f2 -> prev = temp;
        temp -> prev = f;
        temp -> next = f2;
    }

    return tail;
}



int main() {
    struct apartment* tail = NULL;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
