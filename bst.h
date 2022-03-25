#include <iostream>

template<typename _Tp>
class binary_search_tree {

    struct node {
        _Tp value;
        node* left;
        node* right;
    };

public:

    node* new_node(_Tp value);

    node* insert_node(node* root, _Tp value);

    bool search_pre_order(node* root, _Tp value);

    bool search_in_order(node* root, _Tp value);

    bool search_post_order(node* root, _Tp value);

    node* min_value(node* root);

    node* delete_value(node* root, _Tp value);
};

template<typename _Tp>
typename binary_search_tree<_Tp>::node* binary_search_tree<_Tp>::new_node(_Tp value) {
    auto* added = new node();
    added->value = value;
    added->left = nullptr;
    added->right = nullptr;
    return added;
}

template<typename _Tp>
typename binary_search_tree<_Tp>::node* binary_search_tree<_Tp>::insert_node(node* root, _Tp value) {
    if (root == nullptr) {
        root = new_node(value);
        return root;
    } else if (root->value >= value) {
        root->left = insert_node(root->left, value);
        return root->left;
    } else {
        root->right = insert_node(root->right, value);
        return root->right;
    }
}

template<typename _Tp>
bool binary_search_tree<_Tp>::search_pre_order(node* root, _Tp value) {
    if (root == nullptr) return false;
    else if (root->value == value) return true;
    else if (root->value > value) return search_pre_order(root->left, value);
    else return search_pre_order(root->right, value);
}

template<typename _Tp>
bool binary_search_tree<_Tp>::search_in_order(node* root, _Tp value) {
    if (root == nullptr) return false;
    else if (root->value > value) return search_in_order(root->left, value);
    else if (root->value == value) return true;
    else return search_in_order(root->right, value);
}

template<typename _Tp>
bool binary_search_tree<_Tp>::search_post_order(node* root, _Tp value) {
    if (root == nullptr) return false;
    else if (root->value > value) return search_post_order(root->left, value);
    else if (root->value < value) return search_post_order(root->right, value);
    return true;
}

template<typename _Tp>
typename binary_search_tree<_Tp>::node* binary_search_tree<_Tp>::min_value(node* root) {
    node* temp = root;
    while (temp && temp->left != nullptr) temp = temp->left;
    return temp;
}

template<typename _Tp>
typename binary_search_tree<_Tp>::node* binary_search_tree<_Tp>::delete_value(node* root, _Tp value) {
    if (root == nullptr) return root;
    if (value < root->value) {
        root->left = delete_value(root->left, value);
    } else if (value > root->value) {
        root->right = delete_value(root->right, value);
    } else {
        if (root->left == nullptr && root->right == nullptr) return nullptr;
        else if (root->left == nullptr) {
            node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            node* temp = root->left;
            delete root;
            return temp;
        }
    }
    return root;
}