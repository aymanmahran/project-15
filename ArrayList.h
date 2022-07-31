#ifndef ARRAYLIST_H_INCLUDED
#define ARRAYLIST_H_INCLUDED

#include<bits/stdc++.h>

using namespace std;

template<typename Node>
class ArrayList {
    private:
        Node* arr;
        int array_size;
        int cnt;

    public:
        ArrayList(int n);
        void insertItem(Node node);
        void deleteItem(Node node);
        Node getItem(int index);
        void updateItem(int index, Node node);
        int getSize();
};

template<typename Node>
ArrayList<Node>::ArrayList(int n) {
    arr = new Node[n]{};
    array_size = n;
    cnt = 0;
}

template<typename Node>
void ArrayList<Node>::insertItem(Node node) {
    if(cnt == array_size) {
        Node* new_arr = new Node[array_size * 2];
        for(int i = 0; i < array_size; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
        array_size *= 2;
    }

    arr[cnt] = node;
    cnt++;
    return;
}


template<typename Node>
void ArrayList<Node>::deleteItem(Node node) {
    for(int i = 0; i < cnt; i++){
        if(arr[i] == node) {
            for(int j = i; j < cnt - 1; j++) {
                arr[j] = arr[j+1];
            }
            cnt--;
            return;
        }
    }
}

template<typename Node>
Node ArrayList<Node>::getItem(int index) {
    if(index < cnt) return arr[index];
    return NULL;
}

template<typename Node>
void ArrayList<Node>::updateItem(int index, Node node) {
    if(index < cnt) arr[index] = node;
}

template<typename Node>
int ArrayList<Node>::getSize() {
    return cnt;
}

#endif
