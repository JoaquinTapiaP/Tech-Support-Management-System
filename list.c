#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node {
    void * data;
    struct Node * next;
} Node;

typedef struct List {
    Node * head;
    Node * current;
} List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    if (new == NULL) return NULL;

    new->data = data;
    new->next = NULL;
    return new;
}

List * createList() {
    List * list = (List *)malloc(sizeof(List));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;

    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL) return NULL;

    list->current = list->current->next;
    if (list->current != NULL)
        return list->current->data;
    
    return NULL;
}

void pushFront(List * list, void * data) {
    if (list == NULL) return;

    Node * newNode = createNode(data);
    if (newNode == NULL) return;

    newNode->next = list->head;
    list->head = newNode;
}

void pushBack(List * list, void * data) {
    if (list == NULL) return;

    Node * newNode = createNode(data);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node * aux = list->head;
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = newNode;
    }
}

void pushCurrent(List* list, void* data) {
    if (list == NULL || list->current == NULL) {
        return;  // Lista no inicializada o current es NULL
    }

    // Crear nuevo nodo
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    // Insertar después del current
    newNode->next = list->current->next;  // Nuevo nodo apunta al siguiente de current
    list->current->next = newNode;        // Current ahora apunta al nuevo nodo
}

void * popFront(List * list) {
    if (list == NULL || list->head == NULL)
        return NULL;

    Node * nodeToRemove = list->head;
    void * data = nodeToRemove->data;
    list->head = nodeToRemove->next;
    free(nodeToRemove);
    return data;
}

void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL)
        return NULL;

    Node * temp = list->head;
    Node * prev = NULL;

    while (temp != NULL && temp != list->current) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return NULL; // current no estaba en la lista

    void * data = temp->data;

    if (prev == NULL) {
        // es el head
        list->head = temp->next;
    } else {
        prev->next = temp->next;
    }

    list->current = temp->next;
    free(temp);
    return data;
}

void cleanList(List * list) {
    if (list == NULL) return;

    while (list->head != NULL) {
        popFront(list);
    }
}
