#include <bits/stdc++.h>
#include "ArrayList.h"

template<typename Node>
class HashMap {
    public:
        int capacity;
        ArrayList<int>** table;
        ArrayList<Node>** data;
        HashMap(int n);
        int hashFunction(int key);
        void insertItem(Node item, int key);
        Node getItem(int key);
        void updateItem(int key, Node node);
        ArrayList<Node>** getAll();
};


template<typename Node>
HashMap<Node>::HashMap(int n) {
    table = new ArrayList<int>*[n]{};
    data = new ArrayList<Node>*[n]{};
    for(int i = 0; i < n; i++) {
        table[i] = new ArrayList<int>(1000);
        data[i] = new ArrayList<Node>(1000);
    }
    capacity = n;
}

template<typename Node>
int HashMap<Node>::hashFunction(int key) {
    return (key % capacity);
}

template<typename Node>
void HashMap<Node>::insertItem(Node item, int key) {
    int index = hashFunction(key);
    table[index]->insertItem(key);
    data[index]->insertItem(item);
}

template<typename Node>
Node HashMap<Node>::getItem(int key) {
    int index = hashFunction(key);

    int arr_size = table[index]->getSize();
    for(int i = 0; i < arr_size; i++) {
        if(table[index]->getItem(i) == key) {
            return data[index]->getItem(i);
        }
    }
    return NULL;
}

template<typename Node>
void HashMap<Node>::updateItem(int key, Node node) {
    int index = hashFunction(key);

    int arr_size = table[index]->getSize();
    for(int i = 0; i < arr_size; i++) {
        if(table[index]->getItem(i) == key) {
            data[index]->updateItem(i, node);
            return;
        }
    }
}

template<typename Node>
ArrayList<Node>** HashMap<Node>::getAll() {
    return data;
}
