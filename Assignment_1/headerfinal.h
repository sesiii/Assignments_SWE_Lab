// Creation Date: 2024-01-01 
// Last Modified: 2021-01-14 

/*
Name: Dadi Sasank Kumar
Roll N0:22CS10020
Department: Computer Science and Engineering
*/


#include<stdlib.h>
#include<string.h>
#include<time.h>

//***********************************************************************************
// Structure representing a node in the social network
struct node {
    int id;                 // Unique identifier for the node
    char name[500];         // Name of the node
    char type[200];         // Type of the node (individual, group, business, or organization)
    int creation_date;      // Creation date of the node
    char content[500];      // Content uploaded or posted by the node
    int birthday;           // Birthday (if applicable, for individuals)
    float x;                // X-coordinate (for businesses and organizations)
    float y;                // Y-coordinate (for businesses and organizations)
    struct node* next;      // Pointer to the next node in the linked list
};

// Structure representing links between nodes in the social network
struct all_links {
    struct node* first;     // Pointer to the first node in the link
    struct node* second;    // Pointer to the second node in the link
    struct all_links* next; // Pointer to the next link in the linked list
};
//***********************************************************************************

// Function to create a new node in the social network
struct node* create_node();

// Function to print the details of nodes directly connected (1-hop) to a given node
void onehop_printer(struct node* node);

// Function to search for a node by its unique identifier
void Search();

// Function to retrieve a pointer to a node based on its unique identifier
struct node* search_pointer(int id);

// Function to add links between nodes in the social network
void add_links();

// Function to print details of nodes indirectly connected (2-hop) to a given node
void print_twohop(struct node* node);

// Function to delete a link between two nodes
void Delete_Link(struct node* node);

// Function to delete a node from the social network
void Delete_a_Node();
