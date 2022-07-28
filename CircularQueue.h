#include<bits/stdc++.h>

template <typename Node>
class CircularQueue {
	public:
  	int rear;
    int front;
    int size;
    Node *arr;
    CircularQueue(int n);
    void enqueue(Node value);
    Node dequeue();
    void printQueue();
};
