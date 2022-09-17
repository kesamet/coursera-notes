#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct list{ int data; struct list *next; } list;

int is_empty(const list *l)
{
    return (l == NULL);
}

// Print elements in list
void print_list(list* h)
{
    while(h != NULL){
        printf("%d :", h -> data);
        h = h -> next;
    }
}

int main(void)
{
    list list_of_int;
    list *head = NULL;
    head = malloc(sizeof(list));
    head -> data = 5;
    head -> next = NULL;
    print_list(head);
    printf("\n\n");
    return 0;
}
