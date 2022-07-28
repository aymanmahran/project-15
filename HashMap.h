#include <bits/stdc++.h>

template<typename Node>
class HashMap {
    public:
        int capacity;
        Node* table;
        HashMap(int n);
        int hashFunction(int key);
        void insertItem(Node item, int key);
        void HashDisplay();

};
