#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct element{ char name[50]; char symbol[10]; double weight; } element;
typedef struct list{ element data; struct list *next; } list;

// Initialize a single element list
list* create_list(element e)
{
    list* head = malloc(sizeof(list));
    head -> data = e;
    head -> next = NULL;
    return head;
}

// Add element to list
list* add_to_front(element e, list* h)
{
    list* head = create_list(e);
    head -> next = h;
    return head;
}

// Print elements in list
void print_list(list* h)
{
    while(h != NULL){
        element e = h -> data;
        printf(" Name: %s\n", e.name);
        printf(" Symbol: %s\n", e.symbol);
        printf(" Weight: %f\n\n", e.weight);

        // print_element(e);

        h = h -> next;
    }
}

void print_element(element e)
{
    printf(" Name: %s\n", e.name);
    printf(" Symbol: %s\n", e.symbol);
    printf(" Weight: %f\n\n", e.weight);
}

int main(void)
{
    int size = 10;
    element e0 = {"Neon", "Ne", 20.180};
    element e1 = {"Fluorine", "F", 	18.998};
    element e2 = {"Oxygen", "O", 15.999};
    element e3 = {"Nitrogen", "N", 14.007};
    element e4 = {"Carbon", "C", 12.011};
    element e5 = {"Boron", "B", 10.811};
    element e6 = {"Beryllium", "Be", 9.012};
    element e7 = {"Lithium", "Li", 6.941};
    element e8 = {"Helium", "He", 4.003};
    element e9 = {"Hydrogen", "H", 1.008};
    
    element array_elements[10] = {e0, e1, e2, e3, e4, e5, e6, e7, e8, e9};

    list* head = create_list(array_elements[0]);
    int i;
    for (i=1; i<size; i++)
    {
        head = add_to_front(array_elements[i], head);
    }

    printf("Element list :\n\n");
    print_list(head);
    return 0;
}
