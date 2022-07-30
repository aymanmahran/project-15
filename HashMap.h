#include <bits/stdc++.h>

template<typename Node>
class HashMap {
    public:
        int capacity;
        Node** table;
        HashMap(int n);
        int hashFunction(int key);
        void insertItem(Node* item, int key);
        Node* getItem(int key);
        Node** getAll();
        void HashDisplay();
};


template<typename Node>
HashMap<Node>::HashMap(int n) {
    table = new Node*[n]{};
    capacity = n;
}

template<typename Node>
int HashMap<Node>::hashFunction(int key) {
    return (key % capacity);
}

template<typename Node>
void HashMap<Node>::insertItem(Node* item, int key) {
    int index = hashFunction(key);
    table[index] = item;
}

template<typename Node>
Node* HashMap<Node>::getItem(int key) {
    int index = hashFunction(key);
    return table[index];
}

template<typename Node>
Node** HashMap<Node>::getAll() {
    return table;
}

template<typename Node>
void HashMap<Node>::HashDisplay() {
    for (int i = 0; i < capacity; i++)
      cout << table[i] << endl;
}
