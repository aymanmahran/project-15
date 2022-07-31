#include<bits/stdc++.h>
#include "ArrayList.h"

using namespace std;

template <typename Node, typename Key>
class BPlusNode {
    public:
        bool leaf;
        Key* key;
        Node** data;
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
        void addItem(Node* data, Key key);
        ArrayList<Node*>* searchRange(Key start, Key end);
        void removeItem(Node* data, Key key);
};


template <typename Node, typename Key>
BPlusNode<Node, Key>::BPlusNode(int max_size) {
	key = new Key[max_size];
    data = new Node*[max_size];
	ptr = new BPlusNode<Node, Key>*[max_size + 1]{};
	cnt = 0;
}

template <typename Node, typename Key>
BPTree<Node, Key>::BPTree(int _max_size) {
	root = NULL;
	max_size = _max_size;
}

template <typename Node, typename Key>
BPlusNode<Node, Key>* BPTree<Node, Key>::searchItem(Key key) {
	if (root == NULL) {
        return NULL;
	}
	else {
		BPlusNode<Node, Key>* current = root;
		while (!current->leaf) {
            int i = 0;
            while(i < current->cnt && key > current->key[i]) i++;
            current = current->ptr[i];
		}

		for (int i = 0; i < current->cnt; i++) {
			if (current->key[i] == key) {
				return current->data[i];
			}
		}

		return NULL;
	}
}

template <typename Node, typename Key>
void BPTree<Node, Key>::addItem(Node* data, Key key) {
	if (root == NULL) {
		root = new BPlusNode<Node, Key>(max_size);
		root->key[0] = key;
		root->data[0] = data;
		root->leaf = true;
		root->cnt = 1;
	}

	else {
		BPlusNode<Node, Key>* current = root;
		BPlusNode<Node, Key>* parent;

		while(!current->leaf) {

			parent = current;

			int i = 0;
			while(i < current->cnt && key > current->key[i]) i++;
			current = current->ptr[i];
		}

		if (current->cnt < max_size) {
			int i = 0;
			while (key > current->key[i] && i < current->cnt) i++;

			for (int j = current->cnt; j > i; j--) {
				current->key[j] = current->key[j - 1];
				current->data[j] = current->data[j - 1];
			}

			current->key[i] = key;
			current->data[i] = data;
			current->cnt++;

			current->ptr[current->cnt] = current->ptr[current->cnt - 1];
			current->ptr[current->cnt - 1] = NULL;
		}

		else {

			BPlusNode<Node, Key>* new_leaf = new BPlusNode<Node, Key>(max_size);

			Key temp_key[max_size + 1];
			Node* temp_data[max_size + 1];

			for (int i = 0; i < max_size; i++) {
				temp_key[i] = current->key[i];
				temp_data[i] = current->data[i];
			}

			int i = 0;
			while (key > temp_key[i] && i < max_size) i++;

			for (int j = max_size; j > i; j--) {
				temp_key[j] = temp_key[j - 1];
				temp_data[j] = temp_data[j - 1];
			}

			temp_key[i] = key;
			temp_data[i] = data;

			new_leaf->leaf = true;
			current->cnt = (max_size + 1) / 2;
			new_leaf->cnt = max_size + 1 - (max_size + 1) / 2;

			current->ptr[current->cnt] = new_leaf;

			new_leaf->ptr[new_leaf->cnt] = current->ptr[max_size];

			current->ptr[max_size] = NULL;

			for (int i = 0; i < current->cnt; i++) {
				current->key[i] = temp_key[i];
                current->data[i] = temp_data[i];
			}

			for (int i = 0; i < new_leaf->cnt; i++) {
				new_leaf->key[i] = temp_key[current->cnt + i];
                new_leaf->data[i] = temp_data[current->cnt + i];
			}

			if (current == root) {

				BPlusNode<Node, Key>* new_root = new BPlusNode<Node, Key>(max_size);

				new_root->key[0] = new_leaf->key[0];
				new_root->ptr[0] = current;
				new_root->ptr[1] = new_leaf;
				new_root->leaf = false;
				new_root->cnt = 1;
				root = new_root;
			}
			else {
				insertInternal(new_leaf->key[0], parent, new_leaf);
			}
		}
	}
}

template <typename Node, typename Key>
void BPTree<Node, Key>::insertInternal(Key key, BPlusNode<Node, Key>* current, BPlusNode<Node, Key>* child) {

	if (current->cnt < max_size) {
		int i = 0;

		while (key > current->key[i] && i < current->cnt) i++;

		for (int j = current->cnt; j > i; j--) {
			current->key[j] = current->key[j - 1];
		}

		for (int j = current->cnt + 1; j > i + 1; j--) {
			current->ptr[j] = current->ptr[j - 1];
		}

		current->key[i] = key;
		current->cnt++;
		current->ptr[i + 1] = child;
	}

	else {
		BPlusNode<Node, Key>* new_node = new BPlusNode<Node, Key>(max_size);
        Key temp_key[max_size + 1];
        BPlusNode<Node, Key>* temp_ptr[max_size + 2];

        for (int i = 0; i < max_size; i++) {
            temp_key[i] = current->key[i];
            temp_ptr[i] = current->ptr[i];
        }
        temp_ptr[max_size] = current->ptr[max_size];

		int i = 0;
        while (key > temp_key[i] && i < max_size) i++;

        for (int j = max_size; j > i; j--) {
            temp_key[j] = temp_key[j - 1];
        }

		temp_key[i] = key;


		for (int j = max_size + 1; j > i + 1; j--) {
            temp_ptr[j] = temp_ptr[j - 1];
		}

		temp_ptr[i + 1] = child;
		new_node->leaf = false;
		current->cnt = (max_size + 1) / 2;

		new_node->cnt = max_size - (max_size + 1) / 2;

		for (int i = 0; i < new_node->cnt; i++) {
			new_node->key[i] = temp_key[current->cnt + 1 + i];
		}

		for (int i = 0; i < new_node->cnt + 1; i++) {
			new_node->ptr[i] = temp_ptr[current->cnt + 1 + i];
		}

		if (current == root) {

			BPlusNode<Node, Key>* new_root = new BPlusNode<Node, Key>(max_size);

			new_root->key[0] = current->key[current->cnt];
			new_root->ptr[0] = current;
			new_root->ptr[1] = new_node;
			new_root->leaf = false;
			new_root->cnt = 1;
			root = new_root;
		}

		else {

			insertInternal(current->key[current->cnt], findParent(root, current), new_node);
		}
	}
}

template <typename Node, typename Key>
BPlusNode<Node, Key>* BPTree<Node, Key>::findParent(BPlusNode<Node, Key>* current, BPlusNode<Node, Key>* child) {
    BPlusNode<Node, Key>* parent;

    if (current->leaf || (current->ptr[0])->leaf) {
        return NULL;
    }

    for (int i = 0; i < current->cnt + 1; i++) {
        if (current->ptr[i] == child) {
            parent = current;
            return parent;
        }

        else {
            parent = findParent(current->ptr[i], child);
            if (parent != NULL)
                return parent;
        }
    }

    return parent;
}

template <typename Node, typename Key>
ArrayList<Node*>* BPTree<Node, Key>::searchRange(Key start, Key end) {

    if (root == NULL) {
        cout << "Not found" << endl;
    }

    else {
        ArrayList<Node*>* result = new ArrayList<Node*>(10000);

        BPlusNode<Node, Key>* current = root;

        while (current->leaf == false) {
            int i = 0;
            while (i < current->cnt && start > current->key[i]) i++;
            current = current->ptr[i];
        }

        while(current != NULL && current->cnt != 0) {
            for (int i = 0; i < current->cnt; i++) {
                if (current->key[i] >= start && current->key[i] <= end) {
                    if(current->data[i] != NULL) {
                        result->insertItem(current->data[i]);
                    }
                }
            }
            current = current->ptr[current->cnt];
        }

        return result;
    }
}

template <typename Node, typename Key>
void BPTree<Node, Key>::removeItem(Node* data, Key key) {
    if (root == NULL) {
        return;
	}
	else {
		BPlusNode<Node, Key>* current = root;
		while (!current->leaf) {
            int i = 0;
            while(i < current->cnt && key > current->key[i]) i++;
            current = current->ptr[i];
		}

		for (int i = 0; i < current->cnt; i++) {
			if (current->key[i] == key && current->data[i] == data) {
				current->data[i] = NULL;
				return;
			}
		}
		return;
	}
}
