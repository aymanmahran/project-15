#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

#include <bits/stdc++.h>
using namespace std;

template <typename Node, typename Key>
class PQNode {
public:
    Node* value;
    Key priority;
    PQNode<Node, Key>* next;
};

template <typename Node, typename Key>
class PriorityQueue {
    private:
        PQNode<Node, Key>* head;
    public:
        PriorityQueue();
        PQNode<Node, Key>* createPQNode(Node* value, Key pr);
        void push(Node* value, Key pr);
        void pop();
        Node* peek();
};

template <typename Node, typename Key>
PriorityQueue<Node, Key>::PriorityQueue() {
    head = NULL;
}

template <typename Node, typename Key>
PQNode<Node, Key>* PriorityQueue<Node, Key>::createPQNode(Node* data, Key pr) {
    PQNode<Node, Key>* new_node= new PQNode<Node, Key>();
    new_node->priority=pr;
    new_node->value=data;
    new_node->next=NULL;
    return new_node;
}

template <typename Node, typename Key>
void PriorityQueue<Node, Key>::push(Node* data, Key pr) {
    PQNode<Node,Key>* new_node = createPQNode(data, pr);
    PQNode<Node,Key>* temp = head;

    if (head == NULL || temp->priority > pr) {
        new_node->next = temp;
        head = new_node;
        return;
    }

    while (temp->next != NULL && temp->next->priority < pr) {
        temp = temp->next;
    }

    new_node->next = temp->next;
    temp->next = new_node;
    return;
}

template <typename Node, typename Key>
Node* PriorityQueue<Node, Key>::peek() {
    return head->value;
}

template <typename Node, typename Key>
void PriorityQueue<Node, Key>::pop() {
    PQNode<Node, Key>* temp = head;
    head = temp->next;
    free(temp);
}

#endif
