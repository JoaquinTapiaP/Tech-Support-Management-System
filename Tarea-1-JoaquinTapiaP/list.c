#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List*) malloc(sizeof(List));
    list->head = NULL;
    list->tail = 0;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    list->current = list->head;
    if (list->current != NULL) 
        return list->current->data;
    return NULL;
}

void * nextList(List * list) {
    if (list->current != NULL)
        list->current = list->current->next;
    
    if (list->current != NULL)
        return list->current->data;
    
    return NULL;
}

void * lastList(List * list) {
    list->current = list->head;
    while (list->current->next != NULL) {
        list->current = list->current->next;
    }
    return list->current->data;
}

void * prevList(List * list) {
    if (list->current != NULL)
        list->current = list->current->prev;
    
    if (list->current != NULL)
        return list->current->data;
    
    return NULL;
}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data);
    
    //list->head = newNode;
    //list->head->prev = newNode;

    newNode->next = list->head;

    if (list->head != NULL) 
        list->head->prev = newNode;
    else   
        list->tail = newNode;
    
    list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list == NULL || list->current == NULL) 
        return;
    Node* newNode = createNode(data);
    
    newNode->prev = list->current;
    newNode->next = list->current->next;

    newNode->prev->next = newNode;

    if (newNode->next != NULL)
        newNode->next->prev = newNode;
    else 
        list->tail = newNode;


}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {

    if (list == NULL || list->current == NULL) 
        return NULL;
    

    Node *izquierda = list->current->prev;
    Node *derecha = list->current->next;

    if (izquierda == NULL) {
        list->head = derecha;
    } else {
        izquierda->next = derecha;
    }

    
    if (derecha == NULL) {
        list->tail = izquierda;
    } else {
        derecha->prev = izquierda;
    }
    

    void *data = list->current->data;
    
    free(list->current->data);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}