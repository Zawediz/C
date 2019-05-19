#include <iostream>
#include <vector>
#include <string>
#include <random>

struct Node {
    Node() : str(""), key(1), priority(rand()), left(nullptr), right(nullptr) {}

    Node(std::string s) : str(s), key(1), priority(rand()), left(nullptr), right(nullptr) {}

    std::string str;
    Node *left;
    Node *right;
    int priority;
    int key;
};

int getKey(Node *node) {
    if (!node) {
        return 0;
    } else {
        return node->key;
    }
}


void updateKey(Node *&node) {
    if (node != nullptr) {
        node->key = getKey(node->left) + getKey(node->right) + 1;
    }
}

void split(Node *node, Node *&left, Node *&right, int pos) {
    if (!node) {
        left = nullptr;
        right = nullptr;
    } else if (getKey(node->left) >= pos) {
        right = node;
        split(right->left, left, right->left, pos);
        updateKey(right);
        updateKey(left);
    } else {
        left = node;
        split(left->right, left->right, right, pos - getKey(node->left) - 1);
        updateKey(right);
        updateKey(left);
    }
}


void merge(Node *&node, Node *left, Node *right) {
    if (!right) {
        node = left;
        updateKey(node);
    } else if (!left) {
        node = right;
        updateKey(node);
    } else {
        if (left->priority <= right->priority) {
            node = right;
            merge(node->left, left, node->left);
            updateKey(node);
        } else {
            node = left;
            merge(node->right, node->right, right);
            updateKey(node);
        }
    }
}

void InsertAt(Node *&node, int position, const std::string &value) {
    Node *left = nullptr;
    Node *right = nullptr;
    split(node, left, right, position);
    node = new Node(value);
    merge(node, node, right);
    merge(node, left, node);
}

void DeleteAt(Node *&node, int position) {
    Node *left = nullptr;
    Node *middle = nullptr;
    Node *right = nullptr;
    split(node, left, middle, position);
    split(middle, middle, right, 1);
    merge(node, left, right);
}


std::string GetAt(Node *node, int position) {
    int key = getKey(node->left);
    if (key == position) {
        return node->str;
    } else if (key < position) {
        return GetAt(node->right, position - key - 1);
    } else return GetAt(node->left, position);
}

int main() {
    int k;
    std::cin >> k;
    Node *a = nullptr;
    for (int i = 0; i < k; ++i) {
        char command;
        int position;
        std::cin >> command >> position;

        if (command == '+') {
            std::string s;
            std::cin >> s;
            InsertAt(a, position, s);
        } else if (command == '-') {
            int position2;
            std::cin >> position2;
            for (int j = position; j <= position2; ++j)
                DeleteAt(a, j);
        } else if (command == '?') {
            std::cout << GetAt(a, position) << std::endl;
        }
    }
    return 0;
}
