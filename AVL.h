#include <bits/stdc++.h>

template <typename Node, typename Key>
class AVLNode {
  public:
    Key key;
    int height;
    Node *data;
};

template <typename Node, typename Key>
class AVL {
  public:
    void addItem(Node *data, Key key);
    void removeItem(Key key);

  private:
    AVLNode<Node, Key> *root;
    AVLNode<Node, Key> *insertNode(AVLNode<Node, Key> *node, Node *data, Key key);
    AVLNode<Node, Key> *rotateRight(AVLNode<Node, Key> *node);
    AVLNode<Node, Key> *rotateLeft(AVLNode<Node, Key> *node);
    int height(AVLNode<Node, Key> *node);
    AVLNode<Node, Key> *createNode(Node *data, Key key);
    bool search(AVLNode<Node, Key>* node, Key key);
    AVLNode<Node, Key> *deleteNode(AVLNode<Node, Key> *node, Key key);
    AVLNode<Node, Key> *getMinVal(AVLNode<Node, Key> *node);

};
