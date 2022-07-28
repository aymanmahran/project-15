#include "HashMap.h"
using namespace std;

template<typename Node>
HashMap<Node>::HashMap(int n) {
    table = new Node[n];
    capacity = n;
}

template<typename Node>
int HashMap<Node>::hashFunction(int key) {
    return (key % capacity);
}

template<typename Node>
void HashMap<Node>::insertItem(Node item, int key) {
    int index = hashFunction(key);
    table[index] = item;
}

template<typename Node>
void HashMap<Node>::HashDisplay() {
    for (int i = 0; i < capacity; i++)
      cout << table[i] << endl;
}
