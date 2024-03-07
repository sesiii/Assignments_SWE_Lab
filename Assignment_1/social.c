// Creation Date: 2024-01-01 
// Last Modified: 2021-01-14 

/*
Name: Dadi Sasank Kumar
Roll N0:22CS10020
Department: Computer Science and Engineering
*/



#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "social.h"
#include<stdbool.h>

int limit = 50;

// maintain a head to the linked list
struct node *head;
struct link *Top;


/************* Function Declarations *************/
/**
 * @brief Function to get a string input from the user dynamically.
 *
 * This function allocates memory for a character array and reads user input character by character,
 * dynamically resizing the array if needed. It ensures that the user's input does not exceed the
 * specified limit, preventing buffer overflow.
 *
 * @return A pointer to the dynamically allocated character array containing the user's input.
 *         Returns NULL in case of memory allocation failure or if the input is empty.
 */

char *readInputString() {
    char *str = (char *)malloc(limit * sizeof(char)); // Initialize a character array
    if (str == NULL) {
        // Check if memory allocation is successful
        printf("Unable to allocate memory. Retry the operation\n");
        return NULL;
    }

    int size = 0; // Variable to maintain the size of the string
    int max = limit;

    while (1) {
        if (size == max) {
            // Check if the array has reached its limit, increase its size
            max += limit;
            str = (char *)realloc(str, max * sizeof(char));
            if (str == NULL) {
                // If memory allocation fails during resizing
                printf("Unable to allocate memory. Retry the operation\n");
                free(str);
                return NULL;
            }
        }

        char c; // Temporary character to take input from the user
        scanf("%c", &c);

        if (c == '\n') {
            // If the terminating character is entered, break the loop
            str[size] = '\0';
            break;
        } else {
            str[size] = c;
            size++;
        }
    }

    if (size == 0) {
        // If the user entered an empty string
        free(str);
        return NULL;
    }

    return str;
}

/**
 * @brief Creates a new node and adds it to the linked list.
 *
 * This function prompts the user to input information for a new node, allocates memory for the node,
 * and adds it to the linked list. It supports different types of nodes (Individual, Business, Group, Organization),
 * and handles input validation for the type. Memory is allocated dynamically for the node's content using the
 * `readInputString` function. The user is prompted to enter the ID, name, type, creation date, content,
 * birthday (for Individuals), or coordinates (for Businesses and Organizations).
 *
 * @return A pointer to the head of the linked list after adding the new node.
 *         Returns NULL in case of memory allocation failure or if the type entered is invalid.
 *
 * @note The caller is responsible for managing the linked list and freeing the allocated memory when necessary.
 */
struct node *New_Node() {
    struct node *new_Node = (struct node *)malloc(sizeof(struct node)); // Allocate memory for a new node
    char DumChar; // Dummy character to handle newline characters after entering an integer

    // Prompt the user to enter information for the new node
    printf("Enter id: ");
    scanf("%d%c", &(new_Node->id), &DumChar);

    printf("Enter the name: ");
    scanf("%[^\n]s", new_Node->name);

    printf("Enter type as Individual/Business/Group/Organization: ");
    scanf("%s", new_Node->type);

    // Validate the entered type
    if (strcmp(new_Node->type, "Individual") != 0 &&
        strcmp(new_Node->type, "Business") != 0 &&
        strcmp(new_Node->type, "Group") != 0 &&
        strcmp(new_Node->type, "Organization") != 0) {
        printf("Invalid type\n");
        free(new_Node);
        return NULL;
    }

    printf("Enter creation date YYDDMM format ");
    scanf("%d%c", &(new_Node->creation_date), &DumChar);

    printf("Enter the content: ");
    new_Node->content = readInputString(); // Allocate memory for content using readInputString function

// printf("Enter the content: ");
// new_Node->content = readInputString(); // Allocate memory for content using readInputString function

// // Check if a node with the same content already exists
// if (nodeExists(head, new_Node->content)) {
//     printf("Error: Duplicate content.\n");
//     free(new_Node->content);
//     free(new_Node);
//     return NULL;
// }



    // For Individual type, prompt for birthday; for Business and Organization types, prompt for coordinates
    if (strcmp(new_Node->type, "Individual") == 0) {
        printf("Enter birthday YYDDMM format ");
        scanf("%d", &(new_Node->birthday));
    } else if (strcmp(new_Node->type, "Business") == 0 || strcmp(new_Node->type, "Organization") == 0) {
        printf("Enter co-ordinates: ");
        scanf("%f%f", &((new_Node->point).x), &((new_Node->point).y));
    }

    new_Node->next = head; // Update the head pointer
    head = new_Node; // Update the head of the linked list

    return head;
}
// #include <string.h> // for strcmp

// bool nodeExists(struct node* head, char* content) {
//     struct node* current = head;
//     while (current != NULL) {
//         if (strcmp(current->content, content) == 0) {
//             return true;
//         }
//         current = current->next;
//     }
//     return false;
// }
// int nodeExists(struct node *head, char *content)
// {
//     struct node *current = head;
//     while (current != NULL)
//     {
//         if (strcmp(current->content, content) == 0)
//         {
//             return 1;
//         }
//         current = current->next; // Update the current pointer
//     }
//     return 0;
// }

/**
 * @brief Prints details of a node and its one-hop connections in the social network.
 *
 * This function takes a node as input and prints its attributes such as ID, name, creation date,
 * content, type, and additional details based on the node type (birthday for Individuals, coordinates
 * for Businesses and Organizations). It then traverses the linked list of links to identify and print
 * all one-hop connections to other nodes.
 *
 * @param node A pointer to the node whose details and one-hop connections are to be printed.
 *
 * @note If the input node is NULL, it prints a message indicating that the node is not found.
 *       The function assumes a global variable `Top` representing the head of the linked list of links.
 */
void onehop_printer(struct node *node) {
    if (node == NULL) {
        // If the input node is NULL, print a message and return
        printf("Node not found\n");
        return;
    }

    // Print basic node attributes
    printf("Id: %d\n", node->id);
    printf("Name: %s\n", node->name);
    printf("Creation Date: %d\n", node->creation_date);
    printf("Content: %s\n", node->content);
    printf("Type: %s\n", node->type);

    // Print additional details based on the node type
    if (strcmp(node->type, "Individual") == 0) {
        printf("Birthday: %d\n", node->birthday);
    } else if (strcmp(node->type, "Business") == 0 || strcmp(node->type, "Organization") == 0) {
        printf("Coordinates: %f %f\n", (node->point).x, (node->point).y);
    }

    // Traverse the linked list of links to print one-hop connections
    struct link *current_link = Top; // Current link initialized to the head
    while (current_link != NULL) {
        // If the current node is linked to the input node, print the link details
        if (current_link->front->id == node->id) {
            printf("%s with id-%d is linked\n", current_link->back->type, current_link->back->id);
        } else if (current_link->back->id == node->id) {
            printf("%s with id-%d is linked\n", current_link->front->type, current_link->front->id);
        }
        current_link = current_link->next; // Update the current link
    }
}

/**
 * @brief Searches for a node in the social network based on its ID.
 *
 * This function prompts the user to enter the ID of the node they want to search. It then iterates
 * through the linked list of nodes, comparing the input ID with the ID of each node. If a match is found,
 * it prints the details of the found node using the `onehop_printer` function. If no match is found,
 * it prints a message indicating that the data is not found.
 *
 * @note The function assumes the existence of a global variable `head` representing the head of the linked list of nodes.
 *       It uses the `onehop_printer` function to print the details of the found node.
 */
void Node_Search() {
    // printf("Enter the ID of the node you want to search: ");
    // int temp;
    // scanf("%d", &temp);

    // struct node *current_node = head; // Create a new pointer initialized to the head
    // while (current_node != NULL) {
    //     // Loop until the end of the linked list
    //     if (current_node->id == temp) {
    //         // If the ID matches, print the details of the found node
    //         printf("\nFound node :)\n\n");
    //         onehop_printer(current_node);
    //         return; // Return as the ID is unique
    //     }
    //     current_node = current_node->next;
    // }

    // // If no match is found
    // printf("\nData not found\n");
    // return;
    printf("Enter the search criteria (1 for ID, 2 for Type, 3 for Birthday): ");
    int searchCriteria;
    scanf("%d", &searchCriteria);

    printf("Enter the value to search: ");
    if (searchCriteria == 1 || searchCriteria == 3) {
        int temp;
        scanf("%d", &temp);

        struct node *current_node = head;
        while (current_node != NULL) {
            if ((searchCriteria == 1 && current_node->id == temp) ||
                (searchCriteria == 3 && current_node->birthday == temp)) {
                printf("\nFound person :)\n\n");
                onehop_printer(current_node);
                return;
            }
            else{
                printf("\nFound not person :)\n\n");
            }
            current_node = current_node->next;
        }
    } else if (searchCriteria == 2) {
        char temp[20];
        scanf("%s", temp);

        struct node *current_node = head;
        while (current_node != NULL) {
            if (strcmp(current_node->type, temp) == 0) {
                printf("\nFound person :)\n\n");
                onehop_printer(current_node);
                return;
            }
            else{
                printf("\nFound not person :)\n\n");
            }
            current_node = current_node->next;
        }
    } else {
        printf("\nInvalid search criteria\n");
        return;
    }

    printf("\nData not found\n");

    
}


/**
 * @brief Searches for a node in the social network based on its ID and returns a pointer to the node.
 *
 * This function takes an integer parameter representing the ID of the node to be searched. It then iterates
 * through the linked list of nodes, comparing the input ID with the ID of each node. If a match is found,
 * it returns a pointer to that node. If no match is found, it returns NULL.
 *
 * @param id The unique ID of the node to be searched.
 * @return Pointer to the node with the specified ID if found, otherwise returns NULL.
 *
 * @note The function assumes the existence of a global variable `head` representing the head of the linked list of nodes.
 */
struct node *finder(int id) {
    struct node *current_node = head; // Create a new pointer initialized to the head
    while (current_node != NULL) {
        // Loop until the end of the linked list
        if (current_node->id == id) {
            // If the ID matches, return a pointer to the node
            return current_node;
        }
        current_node = current_node->next;
    }

    // If no match is found
    return NULL;
}


/**
 * @brief Creates a new link between nodes in the social network.
 *
 * This function allows the user to establish a connection between two nodes in the social network. It prompts
 * the user to enter the ID of the first node (front), and based on the type of that node, it then prompts for
 * the ID of the second node (back) and the nature of the connection. The function performs various checks to
 * ensure the validity of the link and handles different cases such as linking Individuals to groups or businesses,
 * businesses to Individuals, Organizations to Individuals, and Individuals to groups.
 *
 * @note The function assumes the existence of global variables `head` representing the head of the linked list of nodes
 * and `Top` representing the head of the linked list of links.
 */
void buildLink() {
    struct link *newlink = (struct link *)malloc(sizeof(struct link));
    printf("Enter the ID you want to link: ");
    int temp; // take a temporary variable to take input from the user
    scanf("%d", &temp);
    struct node *front = finder(temp); // initialize the node you want to link as front

    if (front == NULL) { // if entered ID is unavailable, return
        printf("Entered ID is unavailable\n");
        return;
    }

    if (strcmp(front->type, "Individual") == 0) { // if front is an Individual type
        printf("Enter the ID of the group or business or organization you want this Individual to be a part of: ");
        int temp2;
        scanf("%d", &temp2);
        struct node *back = finder(temp2); // initialize the second node as back

        if (back == NULL) { // if entered ID is unavailable, return
            printf("Entered ID is unavailable\n");
            return;
        }

        if (strcmp(back->type, "Individual") == 0) { // link between two Individuals not possible
            printf("Link not possible\n");
            return;
        }

        newlink->c = 'm'; // by default, the link is a type of member

        if (strcmp(back->type, "Business") == 0) { // if one of the linkers is a business, ask the user whether it is an owner or customer
            printf("Is the Individual an owner->1 or customer->2: ");
            int temp3;
            scanf("%d", &temp3);

            if (temp3 == 1)
                newlink->c = 'o'; // owner
            else
                newlink->c = 'c'; // customer
        }

        newlink->front = front; // make sure that always, if an Individual is a part of a link, it's always present at the front
        newlink->back = back;
        newlink->next = Top;
        Top = newlink; // header update
    } else if (strcmp(front->type, "Business") == 0) { // if front is a type of business
        printf("Enter the ID of the Individual or group you want to link to this business: ");
        int temp2;
        scanf("%d", &temp2);
        struct node *back = finder(temp2); // initialize it as back

        if (back == NULL) { // if the entered ID is unavailable
            printf("Entered ID is unavailable\n");
            return;
        }

        if (strcmp(back->type, "Organization") == 0 || strcmp(back->type, "Business") == 0) { // link to businesses and Organizations is not possible
            printf("Link not possible\n");
            return;
        }

        if (strcmp(back->type, "Individual") == 0) { // only when back is of type Individual
            printf("Is the Individual an owner->1 or customer->2: "); // whether the Individual is an owner or customer
            int temp3;
            scanf("%d", &temp3);

            if (temp3 == 1)
                newlink->c = 'o'; // owner
            else
                newlink->c = 'c'; // customer
        }

        newlink->front = back; // updating the linked list
        newlink->back = front;
        newlink->next = Top;
        Top = newlink;
    } else if (strcmp(front->type, "Organization") == 0) { // if front is a type of Organization
        printf("Enter the ID of the Individual you want to link to this Organization: ");
        int temp2;
        scanf("%d", &temp2);
        struct node *back = finder(temp2); // initialize linker 2

        if (back == NULL) { // if the entered ID is unavailable
            printf("Entered ID is unavailable\n");
            return;
        }

        if (strcmp(back->type, "Individual") != 0) { // Organizations can only link with Individuals
            printf("Link is not possible\n");
            return;
        }

        newlink->c = 'm'; // by default, it's a member

        // updating the linked list
        newlink->front = back;
        newlink->back = front;
        newlink->next = Top;
        Top = newlink;
    } else { // if front is a type of group
        printf("Enter the ID of the Individual or Business you want to link to this group: ");
        int temp2;
        scanf("%d", &temp2);
        struct node *back = finder(temp2); // initialize linker 2

        if (back == NULL) { // if entered ID is unavailable
            printf("Entered ID is unavailable\n");
            return;
        }

        if (strcmp(back->type, "Group") == 0 || strcmp(back->type, "Organization") == 0) { // these types of links are not valid
            printf("Link not possible\n");
            return;
        }

        newlink->c = 'm'; // default
        // updating the linked list
        newlink->front = back;
        newlink->back = front;
        newlink->next = Top;
        Top = newlink;
    }
}

/**
 * @brief Prints nodes that are two hops away from a given Individual node.
 *
 * This function prints the nodes that are two hops away from a given Individual node in the social network.
 * It first checks if the input node is of type "Individual" and then traverses through the linked list of links
 * to find the Groups, Organizations, or Businesses the input Individual is a part of. For each such group, it
 * prints all the Individuals (excluding the input node) that are two hops away from the original Individual.
 *
 * @param node A pointer to the Individual node for which two-hop nodes need to be printed.
 *
 * @note The function assumes the existence of a global variable `Top` representing the head of the linked list of links.
 */
void print_twohop(struct node *node) {
    if (strcmp(node->type, "Individual") != 0) { // this function is only possible for Individual type
        printf("Entered ID does not correspond to an Individual type node\n");
        return;
    }

    struct link *current_link = Top; // initialize a current node to the header

    while (current_link != NULL) { // traverse through the linked list and find the Group/Organization/Business this Individual is a part of
        if (current_link->front->id == node->id) { // if found, as Individuals are always present at the front
            struct node *temp = current_link->back; // store the Group/Organization/Business
            struct link *current_link2 = Top;

            while (current_link2 != NULL) { // traverse through the link again and print all the nodes that are part of the earlier Group/Organization/Business
                if (current_link2->back->id == temp->id && strcmp(current_link2->front->type, "Individual") == 0 && current_link2->front->id != node->id) {
                    // the same node may be printed, so an extra condition is added
                    printf("Individual with id-%d is two-hopped with your Individual with id-%d\n", current_link2->front->id, node->id);
                }

                current_link2 = current_link2->next;
            }
        }

        current_link = current_link->next;
    }
}


/**
 * @brief Deletes all links associated with a given node in the social network.
 *
 * This function deletes all links (connections) associated with a given node in the social network.
 * It traverses through the linked list of links and removes any link where the provided node is either
 * at the front or at the back of the link. The function ensures that memory allocated for the deleted links
 * is properly freed.
 *
 * @param node A pointer to the node for which links need to be deleted.
 *
 * @note The function assumes the existence of a global variable `Top` representing the head of the linked list of links.
 */
void Delink(struct node *node) {
    struct link *current_node;
    current_node = Top; // take a current node, initialize it to Top

    if (Top == NULL) {
        return; // if there are no links
    }

    struct link *prev = Top; // consider a previous element

    while (current_node != NULL) { // traverse through the linked list
        if (current_node->front->id == node->id || current_node->back->id == node->id) {
            // if either the front or back of the link is the target node
            if (current_node == Top) { // if it's present at the head
                struct link *DumChar = Top; // take a dummy link
                current_node = current_node->next;
                prev = prev->next;
                Top = Top->next;
                DumChar->next = NULL;
                free(DumChar); // after operations, free it
            } else { // if it's present in the middle
                struct link *DumChar = current_node;
                current_node = current_node->next;
                prev->next = current_node;
                DumChar->next = NULL;
                free(DumChar);
            }
        } else { // if it is not found in the current node, update
            if (current_node == Top) {
                current_node = current_node->next; // to make prev one node behind the current node
            } else {
                current_node = current_node->next;
                prev = prev->next;
            }
        }
    }
}


/**
 * @brief Deletes a node from the social network based on the provided ID.
 *
 * This function deletes a node from the social network based on the given ID. It first deletes all the
 * links associated with the node using the `Delink` function. After that, it traverses through the
 * linked list of nodes and removes the node with the specified ID. Memory allocated for the deleted node
 * is properly freed. The function returns when the deletion is completed.
 *
 * @note The function assumes the existence of a global variable `head` representing the head of the linked list of nodes.
 */
void remove_Node() {
    printf("Enter the ID of the node you want to delete: ");

    int temp1;
    scanf("%d", &temp1);

    struct node *temp = finder(temp1); // find the pointer and initialize it to a temp
    if (temp == NULL) { // if the ID is not found
        printf("Entered ID is not found\n");
        return;
    }

    Delink(temp); // first delete all the links connected to the node

    struct node *current_node;
    struct node *prev;
    current_node = head;
    prev = head;

    while (current_node != NULL) { // traverse through the linked list
        if (current_node->id == temp1) { // if the current node is the target node
            if (current_node == head) { // if it's at the head position
                struct node *DumChar = head; // initialize a dummy to head
                current_node = current_node->next;
                prev = prev->next;
                head = head->next;
                DumChar->next = NULL;
                free(DumChar); // after operations, free it
                return; // return
            } else { // if it's at some random position
                struct node *DumChar = current_node;
                current_node = current_node->next;
                prev->next = current_node;
                DumChar->next = NULL;
                free(DumChar);
                return; // when found, return
            }
        } else { // if the current node is not the target node
            if (current_node == head) {
                current_node = current_node->next; // to make prev node a step behind the current node
            } else {
                current_node = current_node->next;
                prev = prev->next;
            }
        }
    }
}



/**
 * @brief Main function to interact with the social network management system.
 *
 * This function provides a simple console-based interface for managing a social network. It presents a menu
 * to the user with options to create a node, search for a node, print one-hop or two-hop nodes, delete a node,
 * add links between nodes, or terminate the process. The user can enter the corresponding option number to
 * perform the desired operation. The menu is displayed in an infinite loop until the user chooses to terminate
 * the process.
 *
 * @note The function assumes the existence of global variables `head` representing the head of the linked list of nodes,
 * `Top` representing the head of the linked list of links.
 *
 * @return Returns 0 on successful execution.
 */

/************* Main Function *************/
int main() {

    printf("Greetings!\n");
    while (1>0) {
       
         printf("\n1. Create a node\n");
        printf("2. Node_Search a node\n");
        printf("3. Print one hop node\n");
        printf("4. Print Two hop node\n");
        printf("5. Delete a node\n");
        printf("6. Add links\n");
        printf("7. Terminate the process\n");
        printf("Enter your choice: ");

        int temp; // take a temp variable to take input from the user
        scanf("%d", &temp);
        if (temp == 1) {
            New_Node();
        } else if (temp == 2) {
            Node_Search();
        } else if (temp == 3) {
            printf("Enter the ID: ");
            int id;
            scanf("%d", &id);
            onehop_printer(finder(id));
        } else if (temp == 4) {
            printf("Enter the ID: ");
            int id;
            scanf("%d", &id);
            print_twohop(finder(id));
        } else if (temp == 5) {
            remove_Node();
        } else if (temp == 6) {
            buildLink();
        } else {
            printf("Process Ended by User\n");
            printf("\n");
            break;
        }
    }
    return 0;
}
