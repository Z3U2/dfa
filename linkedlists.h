//
// Created by Seed on 27/10/2017.
//

#ifndef DFA_LINKEDLISTS_H
#define DFA_LINKEDLISTS_H
typedef struct node{
    int data[2];
    struct node* next;
}node ;

typedef struct nodeN {
    int key;
    struct node* values;
    struct nodeN* next;
}nodeN;

typedef void (*callback)(node* data);


node* create(int data[],node* next);
node* prepend(node* head,int data[]);
node* append(node* head, int data[]);
node* insert_after(node *head, int data[], node* prev);
node* insert_before(node *head, int data[], node* nxt);
void traverse(node* head,callback f);
node* remove_front(node* head);
node* remove_back(node* head);
node* remove_any(node* head,node* nd);
void display(node* n);
node* search(node* head,int data);
void dispose(node *head);
int count(node *head);
node* reverse(node* head);
nodeN* searchN(nodeN* head,int);
nodeN* createN(int key,node* values,nodeN* next);


#endif //DFA_LINKEDLISTS_H
