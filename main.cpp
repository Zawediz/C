#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <memory>

struct Node {
    Node() : str(""), key(1), priority(rand()), left(nullptr), right(nullptr) {}

    Node(std::string s) : str(s), key(1), priority(rand()), left(nullptr), right(nullptr) {}

    std::string str;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    int priority;
    int key;

};

int getKey(std::shared_ptr<Node> &node) {
    if (!node) {
        return 0;
    } else {
        return node.get()->key;
    }
}


void updateKey(std::shared_ptr<Node> &node) {
    if (node != nullptr) {
        node->key = getKey(node->left) + getKey(node->right) + 1;
    }
}

void split(std::shared_ptr<Node> node, std::shared_ptr<Node> &left, std::shared_ptr<Node> &right, int pos) {
    if (!node) {
        left = nullptr;
        right = nullptr;
    } else if (getKey(node->left) >= pos) {
        right = node;
        split(right.get()->left, left, right.get()->left, pos);
        updateKey(right);
        updateKey(left);
    } else {
        left = node;
        split(left->right, left->right, right, pos - getKey(node->left) - 1);
        updateKey(right);
        updateKey(left);
    }
}


void merge(std::shared_ptr<Node> &node, std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
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

void InsertAt(std::shared_ptr<Node> &node, int position, const std::string &value) {
    auto left = std::make_shared<Node>();
    auto right = std::make_shared<Node>();
    left = nullptr;
    right = nullptr;
    split(node, left, right, position);
    auto node2 = std::make_shared<Node>(value);
    merge(node2, node2, right);
    merge(node, left, node2);
}


void DeleteAt(std::shared_ptr<Node> &node, int position_left, int position_right) {
    auto left = std::make_shared<Node>();
    auto middle = std::make_shared<Node>();
    auto right = std::make_shared<Node>();
    left = nullptr;
    middle = nullptr;
    right = nullptr;
    split(node, left, middle, position_left);
    split(middle, middle, right, position_right - position_left + 1);
    merge(node, left, right);
}


std::string GetAt(std::shared_ptr<Node> node, int position) {
    int key = getKey(node->left);
    if (key == position) {
        return node.get()->str;
    } else if (key < position) {
        return GetAt(node->right, position - key - 1);
    } else return GetAt(node->left, position);
}

int main() {
    int k;
    std::cin >> k;
    auto a = std::make_shared<Node>();
    a = nullptr;
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
            DeleteAt(a, position, position2);
        } else if (command == '?') {
            std::cout << GetAt(a, position) << std::endl;
        }
    }

    return 0;
}