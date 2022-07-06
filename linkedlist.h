#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H
struct Node{
    pid_t ppid;
    char name[1005];
    struct Node* next;
};

typedef struct Node* node;
extern int numprocess;
char* deleteprocess();
void addprocess();
void printList();
void deleteList();
#endif