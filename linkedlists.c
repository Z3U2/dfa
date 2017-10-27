//
// Created by Seed on 27/10/2017.
//

#include <malloc.h>
#include <stdio.h>
#include "linkedlists.h"


/*
    create a new node
    initialize the data and next field

    return the newly created node
*/
node* create(int data[],node* next)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->data[0] = data[0];
    new_node->data[1]=data[1];
    new_node->next = next;

    return new_node;
}

/*
    add a new node at the beginning of the list
*/
node* prepend(node* head,int data[])
{
    node* new_node = create(data,head);
    head = new_node;
    return head;
}

/*
    add a new node at the end of the list
*/
node* append(node* head, int data[])
{
    if(head == NULL)
        return NULL;
    /* go to the last node */
    node *cursor = head;
    while(cursor->next != NULL)
        cursor = cursor->next;

    /* create a new node */
    node* new_node =  create(data,NULL);
    cursor->next = new_node;

    return head;
}

/*
    insert a new node after the prev node
*/
node* insert_after(node *head, int data[], node* prev)
{
    if(head == NULL || prev == NULL)
        return NULL;
    /* find the prev node, starting from the first node*/
    node *cursor = head;
    while(cursor != prev)
        cursor = cursor->next;

    if(cursor != NULL)
    {
        node* new_node = create(data,cursor->next);
        cursor->next = new_node;
        return head;
    }
    else
    {
        return NULL;
    }
}

/*
    insert a new node before the nxt node
*/
node* insert_before(node *head, int data[], node* nxt)
{
    if(nxt == NULL || head == NULL)
        return NULL;

    if(head == nxt)
    {
        head = prepend(head,data);
        return head;
    }

    /* find the prev node, starting from the first node*/
    node *cursor = head;
    while(cursor != NULL)
    {
        if(cursor->next == nxt)
            break;
        cursor = cursor->next;
    }

    if(cursor != NULL)
    {
        node* new_node = create(data,cursor->next);
        cursor->next = new_node;
        return head;
    }
    else
    {
        return NULL;
    }
}

/*
    traverse the linked list
*/
void traverse(node* head,callback f)
{
    node* cursor = head;
    while(cursor != NULL)
    {
        f(cursor);
        cursor = cursor->next;
    }
}
/*
    remove node from the front of list
*/
node* remove_front(node* head)
{
    if(head == NULL)
        return NULL;
    node *front = head;
    head = head->next;
    front->next = NULL;
    /* is this the last node in the list */
    if(front == head)
        head = NULL;
    free(front);
    return head;
}

/*
    remove node from the back of the list
*/
node* remove_back(node* head)
{
    if(head == NULL)
        return NULL;

    node *cursor = head;
    node *back = NULL;
    while(cursor->next != NULL)
    {
        back = cursor;
        cursor = cursor->next;
    }

    if(back != NULL)
        back->next = NULL;

    /* if this is the last node in the list*/
    if(cursor == head)
        head = NULL;

    free(cursor);

    return head;
}

/*
    remove a node from the list
*/
node* remove_any(node* head,node* nd)
{
    if(nd == NULL)
        return NULL;
    /* if the node is the first node */
    if(nd == head)
        return remove_front(head);

    /* if the node is the last node */
    if(nd->next == NULL)
        return remove_back(head);

    /* if the node is in the middle */
    node* cursor = head;
    while(cursor != NULL)
    {
        if(cursor->next == nd)
            break;
        cursor = cursor->next;
    }

    if(cursor != NULL)
    {
        node* tmp = cursor->next;
        cursor->next = tmp->next;
        tmp->next = NULL;
        free(tmp);
    }
    return head;

}
/*
    display a node
*/
void display(node* n)
{
    if(n != NULL)
        printf("%d,%d ", n->data[0],n->data[1]);
}

/*
    Search for a specific node with input data

    return the first matched node that stores the input data,
    otherwise return NULL
*/
node* search(node* head,int data)
{

    node *cursor = head;
    while(cursor!=NULL)
    {
        if(cursor->data[0] == data)
            return cursor;
        cursor = cursor->next;
    }
    return NULL;
}

/*
    remove all element of the list
*/
void dispose(node *head)
{
    node *cursor, *tmp;

    if(head != NULL)
    {
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}
/*
    return the number of elements in the list
*/
int count(node *head)
{
    node *cursor = head;
    int c = 0;
    while(cursor != NULL)
    {
        c++;
        cursor = cursor->next;
    }
    return c;
}

/*
    reverse the linked list
*/
node* reverse(node* head)
{
    node* prev    = NULL;
    node* current = head;
    node* next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

nodeN* searchN(nodeN* head,int data){
    nodeN *cursor = head;
    while(cursor!=NULL)
    {
        if(cursor->key== data)
            return cursor;
        cursor = cursor->next;
    }
    return NULL;
}

nodeN* createN(int key,node* values,nodeN* next){
    nodeN* new_node = (nodeN*)malloc(sizeof(nodeN));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->key = key;
    new_node->values = values;
    new_node->next = next;

    return new_node;
}
