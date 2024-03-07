// Creation Date: 2024-01-01 
// Last Modified: 2021-01-14 

/*
Name: Dadi Sasank Kumar
Roll N0:22CS10020
Department: Computer Science and Engineering
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure to represent 2D coordinates
struct coord {
    float x;
    float y;
};

// Structure to represent a node in the social network
struct node {
    int id;
    char name[50];
    char type[100];  // Assuming type is a short string (e.g., "Ind", "Org")
    int creation_date;
    char *content;
    union {
        int birthday;      // For Individual type
        struct coord point; // For Business type
    };
    struct node *next;
};

// Structure to represent a link between nodes in the social network
struct link {
    struct node *front;
    struct node *back;
    char c;  // Link type: 'm' for member, 'o' for owner, 'c' for customer
    struct link *next;
};

// Function to dynamically read a string input from the user
char *readInputString();

// Function to create a new node and add it to the linked list
struct node *New_Node();

// Function to print details of a node and its one-hop connections
void onehop_printer(struct node *node);

// Function to search for a node in the social network based on its ID
void Node_Search();

// Function to search for a node in the social network based on its ID and return a pointer to the node
struct node *finder(int id);

// Function to create a new link between nodes in the social network
void buildLink();

// Function to print nodes that are two hops away from a given Individual node
void print_twohop(struct node *node);

// Function to delete all links associated with a given node in the social network
void Delink(struct node *node);

// Function to delete a node from the social network based on the provided ID
void remove_Node();
