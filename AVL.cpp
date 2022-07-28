#include "AVL.h"
using namespace std;

template <typename Node, typename Key>
void AVL<Node, Key>::addItem(Node *data, Key key) {
  insertNode(root, data, key);
  return;
}

template <typename Node, typename Key>
void AVL<Node, Key>::removeItem(Key key) {
  deleteNode(root, key);
  return;
}

template <typename Node, typename Key>
AVLNode<Node, Key>* AVL<Node, Key>::insertNode(AVLNode<Node, Key> *node, Node *data, Key key) {
  if (node == NULL) {
    return createAVLNode(data);
  }

  else if (key < node->key) {
    node->left = insertNode(node->left, data, key);
  } else if (key >= node->key) {
    node->right = insertNode(node->right, data, key);
  }

  node->height = 1 + max(height(node->left), height(node->right));

  int balance = height(node->left) - height(node->right);

  if (balance > 1 && key < node->left->key) {
    return rotateRight(node);
  }

  else if (balance < -1 && key >= node->right->key) {
    return rotateLeft(node);
  }

  else if (balance > 1 && key >= node->left->key) {
    node->left = rotateLeft(node->left);
    rotateRight(node);
  }

  else if (balance < -1 && key < node->right->key) {
    node->right = rotateRight(node->right);
    rotateLeft(node);
  }

  return node;
}

template <typename Node, typename Key>
AVLNode<Node, Key>* AVL<Node, Key>::rotateRight(AVLNode<Node, Key> *node) {
  AVLNode<Node, Key> *left = node->left;
  AVLNode<Node, Key> *leftRight = left->right;

  left->right = node;
  node->left = leftRight;

  node->height = max(height(node->left), height(node->right));
  left->height = max(height(left->left), height(left->right));

  return left;
}

template <typename Node, typename Key>
AVLNode<Node, Key>* AVL<Node, Key>::rotateLeft(AVLNode<Node, Key> *node) {
  AVLNode<Node, Key> *right = node->right;
  AVLNode<Node, Key> *rightLeft = right->left;

  right->left = node;
  node->right = rightLeft;

  node->height = max(height(node->left), height(node->right));
  right->height = max(height(right->left), height(right->right));

  return right;
}

template <typename Node, typename Key>
int AVL<Node, Key>::height(AVLNode<Node, Key> *node) {
  if (node == NULL)
    return 0;
  else
    return node->height;
}

template <typename Node, typename Key>
AVLNode<Node, Key>* AVL<Node, Key>::createNode(Node *data, Key key) {
  AVLNode<Node, Key> *node = new AVLNode<Node, Key>();
  node->key = key;
  node->height = 0;
  node->data = data;
}

template <typename Node, typename Key>
bool AVL<Node, Key>::search(AVLNode<Node, Key>* node, Key key) {
  if (node == NULL) {
    return false;
  }

  if (key == node->key) {
    return true;
  }

  else if (key < node->key) {
    return search(node->left, key);
  }

  else if (key > node->key) {
    return search(node->right, key);
  }
}

template <typename Node, typename Key>
AVLNode<Node, Key>* AVL<Node, Key>::deleteNode(AVLNode<Node, Key> *node, Key key) {
  if (node == NULL) {
    return NULL;
  }

  else if (key < node->key) {
    node->left = deleteNode(node->left, key);
  } else if (key > node->key) {
    node->right = deleteNode(node->right, key);
  }

  else if (key == node->key) {
    AVLNode<Node, Key> *temp;

    if (node->left == NULL && node->right == NULL) {
      temp = node;
      free(temp);
      node = NULL;
      return node;
    } else if (node->left == NULL) {
      temp = node->right;
      *node = *temp;
      free(temp);
    } else if (node->right == NULL) {
      temp = node->left;
      *node = *temp;
      free(temp);
    }
    else{
      temp = minValNode(node->right);
      node->key = temp->key;
      root-right = deleteNode(root->right, temp->key);
    }
  }

  node->height = 1 + max(height(node->left), height(node->right));

  int balance = height(node->left) - height(node->right);

  if (balance > 1 && key < node->left->key) {
    return rotateRight(node);
  }

  else if (balance < -1 && key >= node->right->key) {
    return rotateLeft(node);
  }

  else if (balance > 1 && key >= node->left->key) {
    node->left = rotateLeft(node->left);
    rotateRight(node);
  }

  else if (balance < -1 && key < node->right->key) {
    node->right = rotateRight(node->right);
    rotateLeft(node);
  }

  return node;
}

template <typename Node, typename Key>
AVLNode<Node, Key>* AVL<Node, Key>::getMinVal(AVLNode<Node, Key> *node) {
  AVLNode<Node, Key> *current = node;
  while(current->left) current = current->left;
  return current;
}
