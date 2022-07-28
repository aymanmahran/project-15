#include "CircularQueue.h"
using namespace std;

template <typename Node>
CircularQueue<Node>::CircularQueue(int n) {
  front = -1;
  rear = -1;
  size = n;
  arr = new Node[n];
}

template <typename Node>
void CircularQueue<Node>::enqueue(Node value) {
  if ((front == 0 && rear == size - 1) ||
      (rear == (front - 1)%(size - 1))) {
    dequeue();
  }

  else if (front == -1) {
    front = 0;
    rear = 0;
    arr[rear] = value;
  }

  else if (rear == size - 1 && front != 0) {
    rear = 0;
    arr[rear] = value;
  }

  else {
    rear++;
    arr[rear] = value;
  }
}

template <typename Node>
Node CircularQueue<Node>::dequeue() {
  if (front == -1) {
    return NULL;
  }

  int data = arr[front];
  arr[front] = NULL;
  if (front == rear) {
    front = -1;
    rear = -1;
  }
  else if (front == size - 1)
    front = 0;
  else
    front++;

  return data;
}

template <typename Node>
void CircularQueue<Node>::printQueue() {
  if (front == -1) {
    return;
  }

  if (rear >= front) {
    for (int i = front; i <= rear; i++)
      cout << arr[i] << endl;
  }
  else {
    for (int i = front; i < size; i++)
      cout << arr[i] << endl;

    for (int i = 0; i <= rear; i++)
      cout << arr[i] << endl;
  }
}
