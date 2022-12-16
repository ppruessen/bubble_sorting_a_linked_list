/* Use the linear linked list code to store a randomly generated set of         */
/* 100 integers.  Now write a routine that will rearrange the list in sorted    */
/* order of these values. Note you might want to use bubble sort to do this.    */
/* Print these values in rows of 5 on the screen.                               */
/* How will this work? Compare two adjacent list elements and if they are out   */
/* of order swap them. After a first pass the largest element will have bubbled */
/* to the end of the list. Each pass can look at one less element as the end    */
/* of a list stays sorted.                                                      */

/* Including necessary libraries */
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

/* Creating the structure of list elements */
typedef struct list {
    int number;
    struct list *next;
} list;

/* Function create a new list element */
list *create_list_element(int number)
{
    list *new_head;
    
    new_head = malloc(sizeof(list));
    if (new_head == NULL)
        return NULL;
    new_head->number = number;
    return (new_head);
}

/* Function creates and adds a list element at the front of a list */
/* Returns the new start of the list */
list *add_to_front(int number, list *head)
{
    list *new_head;
    
    new_head = create_list_element(number);
    new_head->next = head;
    return (new_head);
}

/* Function prints the content of a list */
void print_list(list *head)
{
    int i;
    
    i = 0;
    while (head != NULL)
    {
        printf("%d\t", head->number);
        head = head->next;
        i++;
        if (i % 5 == 0)
            printf("\n");
    }
}

/* Function calculates the number of elements in a list and returns it*/
int num_of_list_elements(list *head)
{
    int i;
    
    i = 0;
    while (head != NULL)
    {
        i++;
        head = head->next;
    }
    return (i);
}

/* Function swaps two list elements, first element becomes the second and */
/* second element becomes first */
/* Returns pointer to the first element after swapping */
list *swap(list* ptr1, list* ptr2)
{
   list* tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
}

/* Function to bubble sort a single linked list */
/* Returns nothing. The function uses a double pointer pointing to the variable */
/* where the address of the head is stored */
/* After sorting, this variable has the value of the new head */
void bubble_sort(list** head, int count)
{
    list** temp_head;
    int i, j, swapped;
    
    for (i = 0; i <= count; i++) {
  
        temp_head = head;
        swapped = 0;
  
        for (j = 0; j < count - i - 1; j++)
        {
  
            list* p1 = *temp_head;
            list* p2 = p1->next;
  
            if (p1->number > p2->number)
            {
                *temp_head = swap(p1, p2);
                swapped = 1;
            }
            temp_head = &(*temp_head)->next;
        }
        if (swapped == 0)
            break;
    }
}

/* Function to free the list */
void free_list(list *head)
{
    list *temp;
    
    while (head != NULL)
    {
        temp = head->next;
        free(head);
        head = temp;
    }
}

/* Program to create 100 random integers and store them in a single linked list */
/* Printing them out before and after bubble sorting them */
int main()
{
    list    *head;
    int     i;
    int     count;
    
    head = NULL;
    srand(time(NULL));
    for (i = 0; i < 100; i++)
    {
        head = add_to_front(rand() % 1000, head);
    }
    count = num_of_list_elements(head);
    printf("\n--------------- Original list: ---------------\n");
    print_list(head);
    printf("\n--------------- Sorted list: ---------------\n");
    bubble_sort(&head, count);
    print_list(head);
    free_list(head);
    return 0;
}
