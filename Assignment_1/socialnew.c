
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "myheader.h"

int name_limit = 50;

// maintain a head to the linked list
struct node *head;
struct link *lhead;

// char *string_input()
// {// function to get name input from user
//     char *str = (char *)malloc(name_limit * sizeof(char)); // initialise a char array
//     if (str == NULL)
//     { // check if memory allocation is successfull
//         printf("Memory allocation failed. Try again\n");
//         return NULL;
//     }
//     int size = 0; // a vairable which maintains the size
//     int max = name_limit;
//     while (1)
//     {
//         if (size == max)
//         { // Checking array has reached limit,increase its size
//             max += name_limit;
//             str = (char *)realloc(str, max * sizeof(char));
//             if (str == NULL)
//             { // if memory allocation fails
//                 printf("Memory allocation failed.Try again\n");
//                 free(str);
//                 return NULL;
//             }
//         }
//         char c; // consider Temp char ,take input from user
//         scanf("%c", &c);
//         if (c == '\n')
//         { // if terminating character is entered loop must break
//             str[size] = '\0';
//             break;
//         }
//         else
//             str[size] = c;
//         size++;
//     }
//     return str;
// }

struct node *create_node()
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    // if (new_node == NULL)
    // { // if memory allocation fails return null
    //     printf("Memory allocation failed,try again\n");
    //     return NULL;
    // }
    char fake_dummy; // fake_dummy variable to take input

    printf("Please enter name: "); // ask the user to enter the name
    scanf("%[^\n]s", new_node->name);

    printf("Please enter your ID: ");            // ask the user to enter the Id
    scanf("%d%c", &(new_node->id), &fake_dummy); // take the input

    printf("Enter type(Individual/Business/Group/Organiztion): "); // ask the user to enter the type
    scanf("%s", new_node->type);

    if (strcmp(new_node->type, "Individual") != 0 && strcmp(new_node->type, "Business") != 0 && strcmp(new_node->type, "Group") != 0 && strcmp(new_node->type, "Organization") != 0)
    {
        printf("Invalid type\n");
        free(new_node);
        return NULL;
    }
    printf("Enter creation date in ddmmyyyy form: "); // ask the input in ddmmyyy form
    scanf("%d%c", &(new_node->creation_date), &fake_dummy);

    printf("Enter the content: "); // content input
    new_node->content = string_input();

    // scanf("%[^\n]s",new_node->content);
    if (strcmp(new_node->type, "ind") == 0)
    { // specific characteristics for different nodes
        printf("Enter birthday in ddmmyyyy form: ");
        scanf("%d", &(new_node->birthday));
    }
    else if (strcmp(new_node->type, "Business") == 0 || strcmp(new_node->type, "Organization") == 0)
    {
        printf("Enter the 2D Coordinates: ");
        scanf("%f%f", &((new_node->point).x), &((new_node->point).y));
    }

    new_node->next = head; // update the head pointer
    head = new_node;
    return head;
}

// Part_3
void onehop_printer(struct node *node)
{ // function to print one hop nodes
    if (node == NULL)
    { // if the node is null return
        printf("Node not found\n");
        return;
    }
    printf("Id:%d\n", node->id);                       // print Id
    printf("name:%s\n", node->name);                   // print name
    printf("type:%s\n", node->type);                   // print type
    printf("creation date:%d\n", node->creation_date); // print birthday
    printf("content:%s\n", node->content);             // print content

    if (strcmp(node->type, "Individual") == 0)
    {
        printf("Birthday: %d\n", node->birthday); // if individual print birthday
    }
    else
    { // if business or organization print its 2D Coordinates
        if (strcmp(node->type, "Business") == 0 || strcmp(node->type, "Orginization") == 0)
        {
            printf("2D Coordinates: %f %f\nC", ((node->point).x), ((node->point).y));
        }
    }

    // traverseing through linkedlist of links to print all one hop nodes
    struct link *current_link = lhead; // current node which is initialised to head
    while (current_link != NULL)
    { // traverse through the linked list

        if (current_link->front->Id == node->Id)
        {
            printf("%s with Id-%d is linked\n", current_link->back->type, current_link->back->Id);
        }
        else if (current_link->back->Id == node->Id)
        {
            printf("%s with Id-%d is linked\n", current_link->front->type, current_link->front->Id);
        }
        current_link = current_link->next; // updating the current_node
    }
}

// Part_5
void Search()// function to Search a node based on Id
{ 
    int Temp;
    printf("Enter the ID you want to Search for: ");

    scanf("%d", &Temp);
    struct node *curr_node = head; // initialise a curr_node to head
    while (curr_node != NULL)
    {                              // loop untill the list ends
        if (curr_node->Id == Temp) // check the Id
        {
            printf("\nNode Found\n");  // if present
            onehop_printer(curr_node); // print the one hop nodes
            return;                    // return
        }
        curr_node = curr_node->next;
    }
    printf("\nNode Not Found\n"); // if not present
    return;
}

struct node *search_pointer(int Id)
{                                  // function to return a node based on Id
    struct node *curr_node = head; // initialise a curr_node to head
    while (curr_node != NULL)
    { // loop untill the list ends
        if (curr_node->Id == Id)
        {                     // check the Id
            return curr_node; // if present return the pointer
        }
        curr_node = curr_node->next; // update the curr_node
    }
    return NULL; // if not present return NULL
}

void add_links()
{ // function to add links
    struct link *new_link = (struct link *)malloc(sizeof(struct link));
    printf("Enter the Id you want to link: ");   // ask the user to enter the Id
    int Temp;                                    // take the input
    scanf("%d", &Temp);                          // initialise it to Temp
    struct node *linker1 = search_pointer(Temp); // initialise the node you want to link as linker 1
    if (linker1 == NULL)                         // if the entered Id is unavailable
    {
        printf("Entered Id is unavailable\n");
        return;
    }
    if (strcmp(linker1->type, "Individual") == 0) // if linker 1 is a type of individual
    {
        printf("Enter the Id of Group/Business/Organization you want this individual as a part of:");
        int temp2;                                    // ask the user to enter the Id of grp/bus/org
        scanf("%d", &temp2);                          // initialise it to temp2
        struct node *linker2 = search_pointer(temp2); // initialise it to linker2
        if (linker2 == NULL)                          // if the entered Id is unavailable
        {
            printf("Entered Id is not found\n");
            return;
        }
        if (strcmp(linker2->type, "Individual") == 0)
        { // link between 2 individuals not possible
            printf("Link not possible\n");
            return;
        }
        _->c = 'm'; // by default link is a type of member
        if (strcmp(linker2->type, "Business") == 0)
        { // if linker 2 is a type of business
            printf("Is the lndividual owner->1 or customer->2 : ");
            int temp3; // ask the user to enter the type of link
            scanf("%d", &temp3);
            if (temp3 == 1)
                _->c = 'o'; // owner
            else
                _->c = 'c'; // customer
        }
        _->front = linker1; // make sure that always,if ind is a part of link its always present at front
        _->back = linker2;
        _->next = lhead;
        lhead = _; // header update
    }
    else if (strcmp(linker1->type, "Business") == 0)
    { // if linker 1 is a type of business, ask the user to give Id of individual
        printf("Enter the Id of individual or group you want to link to this business: ");
        int temp2;
        scanf("%d", &temp2);
        struct node *linker2 = search_pointer(temp2); // initialise linker 2
        if (linker2 == NULL)                          // if the entered Id is unavailable
        {
            printf("Entered Id is unavailable\n");
            return;
        }
        if (strcmp(linker2->type, "Organization") == 0 || strcmp(linker2->type, "Business") == 0)
        { // these types of links are not valid
            printf("Link not possible\n");
            return;
        }
        {
            printf("Link not possible\n");
            return;
        }
        if (strcmp(linker2->type, "Individual") == 0) // if linker2 is of type individual
        {
            printf("Is the lndividual owner->1 or customer->2 : "); // ask the user to enter the type of link
            int temp3;
            scanf("%d", &temp3);
            if (temp3 == 1)
                _->c = 'o'; // owner
            else
                _->c = 'c'; // customer
        }
        _->front = linker2; // make sure that always,if Individual is a part of link its always present at front
        _->back = linker1;
        _->next = lhead;
        lhead = _;
    }
    else if (strcmp(linker1->type, "Organization") == 0) // if linker 1 is a type of organization
    {
        printf("Enter the Id of individual or group you want to link to this organization: "); // ask the user to give Id of individual
        int temp2;
        scanf("%d", &temp2);
        struct node *linker2 = search_pointer(temp2); // initialise linker 2
        if (linker2 == NULL)                          // if the entered Id is unavailable
        {
            printf("Entered Id is unavailable\n");
            return;
        }
        if (strcmp(linker2->type, "Organization") == 0 || strcmp(linker2->type, "Business") == 0)
        { // these types of links are not valid
            printf("Link not possible\n");
            return;
        }
        if (strcmp(linker2->type, "Individual") == 0) // if linker2 is of type individual
        {
            printf("Is the lndividual owner->1 or customer->2 : "); // ask the user to enter the type of link
            int temp3;
            scanf("%d", &temp3);
            if (temp3 == 1)
                _->c = 'o'; // owner
            else
                _->c = 'c'; // customer
        }
        _->front = linker2; // make sure that always,if Individual is a part of link its always present at front
        _->back = linker1;
        _->next = lhead;
        lhead = _;
    }
    else if (strcmp(linker1->type, "Group") == 0) // if linker 1 is a type of group
    {
        printf("Enter the Id of individual you want to link to this organisation: ");
        int temp2;
        scanf("%d", &temp2);
        struct node *linker2 = search_pointer(temp2); // initialise linker 2
        if (linker2 == NULL)                          // if the entered Id is unavailable
        {
            printf("Entered Id is unavailable\n");
            return;
        }
        if (strcmp(linker2->type, "Individual") != 0) // these types of links are not valid
        {
            printf("Link not possible\n");
            return;
        }
        { // organisation can only link with ind
            printf("Link is not possible\n");
            return;
        }
        _->c = 'm'; // bydefault its a member
        // updating the linked list
        _->front = linker2;
        _->back = linker1;
        _->next = lhead;
        lhead = _;
    }
    else
    {
        printf("Enter the Id of individual or business you want to link to this group: "); // if linker 1 is a type of group
        int temp2;
        scanf("%d", &temp2);
        struct node *linker2 = search_pointer(temp2); // initialise linker 2
        if (linker2 == NULL)
        { // if entered Id is unavailable
            printf("Entered Id is unavailable\n");
            return;
        }
        if (strcmp(linker2->type, "Group") == 0 || strcmp(linker2->type, "Organization") == 0) // these types of links are not valid
        { 
            printf("Link not possible\n");
            return;
        }
        _->c = 'm'; // default
        // updating the linked list
        _->front = linker2;
        _->back = linker1;
        _->next = lhead;
        lhead = _;
    }
}

void print_twohop(struct node *node)  // a function to print 2-hop nodes
{
    if (strcmp(node->type, "Individual") != 0)// this function is only possible for ind type
    { 
        printf("Entered Id is not a ind type node\n");
        return;
    }
    struct link *current_link = lhead; // initialise a current node to header

    while (current_link != NULL) // traverse thorugh the linked list and find the grp/bus/org this ind is a part of
    {
        if (current_link->front->id == node->id) 
        {
            struct node *Temp = current_link->back; // initialise a Temp to the back of the link
            struct link *currlink2 = lhead;         // initialise a currlink2 to header
            while (currlink2 != NULL)               // traverse through the linked list
            {
                if (currlink2->back->id == Temp->id && strcmp(currlink2->front->type, "Individual") == 0 && currlink2->front->id != node->id)
                { // the same node may be printed so extra condition is added
                    printf("Individual with Id-%d is two hoped with your ind with Id-%d\n", currlink2->front->id, node->id);
                }
                currlink2 = currlink2->next;
            }
        }
        current_link = current_link->next;
    }
}

void Delete_Link(struct node *node) // a function to delete links
{
    struct link *curr_node;    // take a curr_node
    curr_node = lhead;         // take a currentnode initialise it to lhead
    if (lhead == NULL)         // if there are no links
        return;                // if there are no links
    struct link *prev = lhead; // consider a prev element
    while (curr_node != NULL)
    { // traverse through the linked list
        if (curr_node->front->id == node->id || curr_node->back->id == node->id)
        { // if any one of the node is our target node
            if (curr_node == lhead)
            {                                    // if its present at head
                struct link *fake_dummy = lhead; // take a fake_dummy linke
                curr_node = curr_node->next;
                prev = prev->next;
                lhead = lhead->next;
                fake_dummy->next = NULL;
                free(fake_dummy); // after operations free it
            }
            else
            { // if its present at middle
                struct link *fake_dummy = curr_node;
                curr_node = curr_node->next;
                prev->next = curr_node;
                fake_dummy->next = NULL;
                free(fake_dummy);
            }
        }
        else
        { // if it is not found in the curr_node update
            if (curr_node == lhead)
                curr_node = curr_node->next; // to make prev one node behind of curr_node
            else
            {
                curr_node = curr_node->next;
                prev = prev->next;
            }
        }
    }
}

void Delete_a_Node() // a function to delete node
{ 
    printf("Enter the Id of node you want to delete: "); // ask the user to enter the 
    
    int temp1;                                          // take the input
    scanf("%d", &temp1);

    struct node *Temp = search_pointer(temp1); // find the pointer and initialise it to a temp
    if (Temp == NULL)
    { // if Id is not found
        printf("Entered Id is not found\n");
        return;
    }
    _(Temp); // first all the links connected to the node
    struct node *curr_node;
    struct node *prev;
    curr_node = head;
    prev = head;
    while (curr_node != NULL)
    { // traverse through the linked list
        if (curr_node->id == temp1)
        { // if found
            if (curr_node == head)
            {                                   // if its at head position
                struct node *fake_dummy = head; // initialise a fake_dummy to head
                curr_node = curr_node->next;
                prev = prev->next;
                head = head->next;
                fake_dummy->next = NULL;
                free(fake_dummy); // after operations free it
                return;           // return
            }
            else
            { // if its at some random position
                struct node *fake_dummy = curr_node;
                curr_node = curr_node->next;
                prev->next = curr_node;
                fake_dummy->next = NULL;
                free(fake_dummy);
                return; // when found return
            }
        }
        else
        { // if the curr_node is not the target node
            if (curr_node == head)
                curr_node = curr_node->next; // to make prev node a step behind of curr_node
            else
            {
                curr_node = curr_node->next;
                prev = prev->next;
            }
        }
    }
}

int main()
{
    while (1) // loop untill the user wants to terminate the process
    {
        printf("What do you want to do: ");
        printf("\n");
        printf("Enter your choice as given below:");
        printf("create_node-1,search_node-2,print_one_hop-3,print_two_hop-4,Delete_a_Node-5,add_links-6,terminate_process-7\n");

        int user_input; // take the input
        scanf("%d", &user_input);

        if (user_input == 1)
        {
            create_node();
        }
        else if (user_input == 2)
        {
            Search();
        }
        else if (user_input == 3)
        {
            printf("Enter the Id:");
            int Id;
            scanf("%d", &Id);
            onehop_printer(search_pointer(Id));
        }
        else if (user_input == 4)
        {
            printf("Enter the Id:");
            int Id;
            scanf("%d", &Id);
            print_twohop(search_pointer(Id));
        }
        else if (user_input == 5)
        {
            Delete_a_Node();
        }
        else if (user_input == 6)
        {
            add_links();
        }
        else{
            printf("Process Terminated\n");
        printf("\n");
        }
    
    }
    return 0;
}