#include<bits/stdc++.h>
using namespace std;

template <typename Node, typename Key>
class BPlusNode {
    bool leaf;
    Key *key;
    Node *data;
    int cnt;
    BPlusNode<Node, Key>** ptr;
    BPlusNode(int max_size);

};

template <typename Node, typename Key>
class BPTree {
	BPlusNode<Node, Key>* root;
	int max_size;
	void insertInternal(Key, BPlusNode<Node, Key>*, BPlusNode<Node, Key>*);
	BPlusNode<Node, Key>* findParent(BPlusNode<Node, Key>*, BPlusNode<Node, Key>*);

    public:
        BPTree(int _max_size);
        BPlusNode<Node, Key>* searchItem(Key key);
        void insertItem(Node data, Key key);
        void displayTree(BPlusNode<Node, Key>*);
};
