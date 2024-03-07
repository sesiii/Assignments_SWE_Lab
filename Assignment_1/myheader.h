#include<stdlib.h>
#include<string.h>
#include<time.h>

//***********************************************************************************
struct node{
    int id;
    char name[50];
    char type[4];
    int creation_date;
    char content[500];
    int birthday;
    float x;
    float y;
    struct node* next;
};
 

struct all_links{
    struct node* first;
    struct node* second;
    struct all_links* next;
};

//***********************************************************************************

//char* string_input();
struct node* create_node();
void onehop_printer(struct node* node);
void Search();
struct node* search_pointer(int id);
void add_links();
void print_twohop(struct node* node);
void Delete_Link(struct node* node);
void Delete_a_Node();