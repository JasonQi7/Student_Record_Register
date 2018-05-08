/*  Student Record Register
 *  Author: Jason Qi
 *  UCL Electronic and Electrical Engineering
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// File name used for saving records
#define myFile "test_1.txt"

// Structure of date
struct date
{
    int day;
    int month;
    int year;
};

// Structure of student record, 2-byte padding to align 4-byte addresses
struct student
{
    double mark;
    struct student *next;
    struct date birthday;
    int ID;
    char name[30];
};

// Define structure type shortcuts
typedef struct date Date;
typedef struct student Student;

// Function prototypes
int saveToFile(Student *);
int insertStudent(Student **);
int removeStudent(Student **);
int retrieveFromFile(Student **);
void swap(Student *);
void printOne(Student *);
void printAll(Student *);
void freeList(Student **);
void bubbleSort(Student **);
void reverseList(Student **);


int main(int argc, char *argv[])
{
    // Head of the linked list of student records
    Student *head = NULL;
    
    // To save user's selection
    unsigned short select = 0;
    
    // Main routine
    while (select != 8)
    {
        // Show available functionalities, ask user for choice
        printf("\n1) Introduce new student\n2) Remove student\n3) Search Student\n");
        printf("4) Print all \n5) Save to file\n6) Retrieve data from file\n7) Reverse Order\n8) Exit\n\n");
        scanf("%hu", &select);
        
        switch(select)
        {
            case 1:
                printf("Insertion %s", insertStudent(&head) ? "Failed\n\n" : "Succeeded\n\n");
                break;
            case 2:
                printf("Removal %s", removeStudent(&head) ? "Failed\n\n" : "Succeeded\n\n");
                break;
            case 3:
                printOne(head);
                break;
            case 4:
                printAll(head);
                break;
            case 5:
                printf("Save %s", saveToFile(head) ? "Failed\n\n" : "Succeeded\n\n");
                break;
            case 6:
                printf("Retrieve %s", retrieveFromFile(&head) ? "Failed\n\n" : "Succeeded\n\n");
                break;
            case 7:
                reverseList(&head);
                break;
            case 8:
                freeList(&head);
                return 0;
            default:
                continue;
        }
    }
}


// Swap the data between the pointed struct and the next struct
void swap (Student *currentNode)
{
    // Temporary variables
    int ID = currentNode->ID;
    char tempName[30];
    strcpy(tempName, currentNode->name);
    double tempMark = currentNode->mark;
    Date tempDate = currentNode->birthday;
    
    // Overwrite currentNode's content
    currentNode->ID = currentNode->next->ID;
    strcpy(currentNode->name, currentNode->next->name);
    currentNode->mark = currentNode->next->mark;
    currentNode->birthday = currentNode->next->birthday;
    
    // Overwrite nextNode's content
    currentNode->next->ID = ID;
    strcpy(currentNode->next->name,tempName);
    currentNode->next->mark = tempMark;
    currentNode->next->birthday = tempDate;
}


// Sorting link nodes based on ID number
void bubbleSort (Student **pHead)
{
    bool flag = false;
    Student *currentNode = *pHead;
    do
    {
        flag = false;
        for (currentNode = *pHead; currentNode->next != NULL; currentNode = currentNode->next)
        {
            if (currentNode->ID > currentNode->next->ID)
            {
                // swap data and raise the flag of swapping
                swap(currentNode);
                flag = true;
            }
        }
    }
    while(flag);
}


// Create a new student record
int insertStudent (Student **pHead)
{
    // Allocate memory for new student record
    Student *pStudent = NULL;
    pStudent = (Student *) malloc(sizeof(Student));
    if (pStudent == NULL)
        return 1;
    pStudent->next = NULL;
    
    // Collect user input
    printf("Student ID: ");
    scanf("%d", &pStudent->ID);
    printf("Student Name: ");
    scanf("%s", &pStudent->name[0]);
    printf("Student Mark: ");
    scanf("%lf", &pStudent->mark);
    printf("Student Birth-day: ");
    scanf("%d", &pStudent->birthday.day);
    printf("Student Birth-month: ");
    scanf("%d", &pStudent->birthday.month);
    printf("Student Birth-year: ");
    scanf("%d", &pStudent->birthday.year);
    
    // Insert into NULL list
    if (*pHead == NULL)
        *pHead = pStudent;
    else
    {
        // If list not NULL, add to head
        pStudent->next = *pHead;
        *pHead = pStudent;
       
        // Sort list based on ID
        bubbleSort(pHead);
    }
    return 0;
}


// Remove a selected student record from the list
int removeStudent(Student **pHead)
{
    // If empty list, return
    if (*pHead == NULL)
        return 1;
    
    // Ask for student ID
    int key = 0;
    printf("Remove which ID: ");
    scanf("%d", &key);
    
    // Search ID
    Student *previousNode = *pHead, *currentNode = *pHead;
    while (currentNode->ID != key && currentNode->next != NULL)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    
    // If key is found, free the node and return 0
    if (currentNode->ID == key)
    {
        if (currentNode == *pHead)
            *pHead = currentNode->next;
        else
            previousNode->next = currentNode->next;
        free(currentNode);
        currentNode = NULL;
        return 0;
    }
    
    // If key not found, return 1
    return 1;
}


// Print a selected student record
void printOne(Student *head)
{
    // Empty list
    if (head == NULL)
        return;
    
    // Ask for student ID as search key
    int key = 0;
    printf("Search which ID: ");
    scanf("%d", &key);
    
    // Search ID and print
    for (Student *currentNode = head; currentNode != NULL; currentNode = currentNode->next)
    {
        if (currentNode->ID == key)
        {
            printf("\nID:       %d",currentNode->ID);
            printf("\nName:     %s",currentNode->name);
            printf("\nMark:     %lf",currentNode->mark);
            printf("\nBirthday: %d.%d.%d\n",currentNode->birthday.day, currentNode->birthday.month, currentNode->birthday.year);
        }
        
    }
}


// Print records for all students
void printAll(Student *head)
{
    // NULL list
    if (head == NULL)
        return;
    
    // Print all entries
    for (Student *currentNode = head; currentNode != NULL; currentNode = currentNode->next)
    {
        printf("\nID:       %d",currentNode->ID);
        printf("\nName:     %s",currentNode->name);
        printf("\nMark:     %lf",currentNode->mark);
        printf("\nBirthday: %d.%d.%d\n",currentNode->birthday.day, currentNode->birthday.month, currentNode->birthday.year);
    }
}


// Reverse the order of linked list
void reverseList (Student **pHead)
{
    // No reverse if less than two nodes
    if (*pHead == NULL || (*pHead)->next == NULL)
        return;
    
    // Initialise temporary pointers
    Student *previousNode = NULL, *currentNode = *pHead, *nextNode = NULL;
    while (currentNode != NULL)
    {
        // Reverse pointers
        nextNode = currentNode->next;
        currentNode->next = previousNode;
        previousNode = currentNode;
        currentNode = nextNode;
    }
    *pHead = previousNode;
    nextNode = NULL;
}


// Save student records to a file
int saveToFile(Student *head)
{
    // Open file stream, discard previous content
    FILE *pFile = fopen(myFile, "w");
    
    // If fopen failed, return 1
    if (pFile == NULL)
        return 1;
    
    // Write list to file
    for(Student *currentNode = head; currentNode != NULL; currentNode = currentNode->next)
        fwrite(currentNode, sizeof(Student), 1, pFile);
    
    // Close file stream
    fclose(pFile);
    pFile = NULL;
    
    return 0;
}


// Free/delete all student records in RAM
void freeList(Student **pHead)
{
    Student *currentNode = *pHead, *nextNode = NULL;
    while (currentNode != NULL)
    {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    
    // Prevent dangling pointer
    *pHead = NULL;
}


// Retrieve student records from the file
int retrieveFromFile(Student **pHead)
{
    // Discard existing list
    freeList(pHead);
    
    // Create temporary pointers to student struct
    Student *previousNode = *pHead;
    Student *currentNode = NULL;
    
    // Open file stream for read only
    FILE *pFile = fopen(myFile, "r");
    
    // If fopen failed, return 1
    if (pFile == NULL)
        return 1;
    
    // Indicator of first interation in the following loop
    bool firstInteration = true;
    
    // Dynamically allocate memory for data, node by node
    do
    {
        currentNode = (Student *) malloc(sizeof(Student));
        fread(currentNode, sizeof(Student), 1, pFile);
        
        // Adjust linked list pointers
        if (firstInteration)
        {
            *pHead = currentNode;
            firstInteration = false;
        }
        else
            previousNode->next = currentNode;
        previousNode = currentNode;
    }
    while (currentNode->next != NULL);

    // Close file stream
    fclose(pFile);
    pFile = NULL;
    
    return 0;
}
