#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "social.h"

int maxNameLength = 50;

struct PersonNode *personHead;
struct ConnectionNode *connectionHead;

char *readInputString() {
    char *str = (char *)malloc(maxNameLength * sizeof(char));
    if (str == NULL) {
        printf("Memory allocation failed. Try again\n");
        return NULL;
    }

    int size = 0;
    int maxLength = maxNameLength;

    while (1) {
        if (size == maxLength) {
            maxLength += maxNameLength;
            str = (char *)realloc(str, maxLength * sizeof(char));
            if (str == NULL) {
                printf("Memory allocation failed. Try again\n");
                free(str);
                return NULL;
            }
        }

        char c;
        scanf("%c", &c);

        if (c == '\n') {
            str[size] = '\0';
            break;
        } else {
            str[size] = c;
            size++;
        }
    }

    if (size == 0) {
        free(str);
        return NULL;
    }

    return str;
}

struct PersonNode *createPersonNode() {
    struct PersonNode *newNode = (struct PersonNode *)malloc(sizeof(struct PersonNode));
    char dummyChar;

    printf("Enter id: ");
    scanf("%d%c", &(newNode->id), &dummyChar);

    printf("Enter the name: ");
    scanf("%[^\n]s", newNode->name);

    printf("Enter type as Individual/Business/Group/Organization: ");
    scanf("%s", newNode->type);

    if (strcmp(newNode->type, "Individual") != 0 &&
        strcmp(newNode->type, "Business") != 0 &&
        strcmp(newNode->type, "Group") != 0 &&
        strcmp(newNode->type, "Organization") != 0) {
        printf("Invalid type\n");
        free(newNode);
        return NULL;
    }

    printf("Enter creation date in DDMMYY form: ");
    scanf("%d%c", &(newNode->creationDate), &dummyChar);

    printf("Enter the content: ");
    newNode->content = readInputString();

    if (strcmp(newNode->type, "Individual") == 0) {
        printf("Enter birthday in DDMMYY form: ");
        scanf("%d", &(newNode->birthday));
    } else if (strcmp(newNode->type, "Business") == 0 || strcmp(newNode->type, "Organization") == 0) {
        printf("Enter coordinates: ");
        scanf("%f%f", &(newNode->coordinates.x), &(newNode->coordinates.y));
    }

    newNode->next = personHead;
    personHead = newNode;

    return personHead;
}

void printOneHop(struct PersonNode *person) {
    if (person == NULL) {
        printf("Person not found\n");
        return;
    }

    printf("Id: %d\n", person->id);
    printf("Name: %s\n", person->name);
    printf("Creation Date: %d\n", person->creationDate);
    printf("Content: %s\n", person->content);
    printf("Type: %s\n", person->type);

    if (strcmp(person->type, "Individual") == 0) {
        printf("Birthday: %d\n", person->birthday);
    } else if (strcmp(person->type, "Business") == 0 || strcmp(person->type, "Organization") == 0) {
        printf("Coordinates: %f %f\n", (person->coordinates).x, (person->coordinates).y);
    }

    struct ConnectionNode *currentConnection = connectionHead;
    while (currentConnection != NULL) {
        if (currentConnection->personA->id == person->id) {
            printf("%s with id-%d is linked\n", currentConnection->personB->type, currentConnection->personB->id);
        } else if (currentConnection->personB->id == person->id) {
            printf("%s with id-%d is linked\n", currentConnection->personA->type, currentConnection->personA->id);
        }
        currentConnection = currentConnection->next;
    }
}

void searchPerson() {
    printf("Enter the search criteria (1 for ID, 2 for Type, 3 for Birthday): ");
    int searchCriteria;
    scanf("%d", &searchCriteria);

    printf("Enter the value to search: ");
    if (searchCriteria == 1 || searchCriteria == 3) {
        int temp;
        scanf("%d", &temp);

        struct PersonNode *currentPerson = personHead;
        while (currentPerson != NULL) {
            if ((searchCriteria == 1 && currentPerson->id == temp) ||
                (searchCriteria == 3 && currentPerson->birthday == temp)) {
                printf("\nFound person :)\n\n");
                printOneHop(currentPerson);
                return;
            }
            currentPerson = currentPerson->next;
        }
    } else if (searchCriteria == 2) {
        char temp[20];
        scanf("%s", temp);

        struct PersonNode *currentPerson = personHead;
        while (currentPerson != NULL) {
            if (strcmp(currentPerson->type, temp) == 0) {
                printf("\nFound person :)\n\n");
                printOneHop(currentPerson);
                return;
            }
            currentPerson = currentPerson->next;
        }
    } else {
        printf("\nInvalid search criteria\n");
        return;
    }

    printf("\nData not found\n");
}

// Add other functions here...

int main() {
    printf("Hi there! What do you want to do?\n");

    while (1) {
        printf("\n1. Create Person Node\n");
        printf("2. Print One Hop\n");
        printf("3. Search Person\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createPersonNode();
                break;
            case 2:
                printf("Enter the id of the person: ");
                int id;
                scanf("%d", &id);
                printOneHop(findPersonById(id));
                break;
            case 3:
                searchPerson();
                break;
            case 4:
                // Add cleanup code here if needed
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
