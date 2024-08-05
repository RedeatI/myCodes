#include "BinaryTree.h"

BSTree::BSTree() : BinaryTree()
{
    value = INT_MIN;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

BSTree::BSTree(int32_t value) : BinaryTree()
{
    this->value = value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

BSTree *const BSTree::find(BSTree *&root, int32_t value)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else if (root->value == value)
    {
        return root;
    }
    else if (root->value > value)
    {
        return find(root->left, value);
    }
    else
    {
        return find(root->right, value);
    }
}

bool BSTree::insert(BSTree *&root, int32_t value)
{
    if (root == nullptr)
    {
        root = new BSTree(value);
        return true;
    }
    else if (root->value == value)
    {
        return false;
    }
    else if (root->value > value)
    {
        return insert(root->left, value);
    }
    else
    {
        return insert(root->right, value);
    }
}

bool BSTree::remove(BSTree *&root, int32_t value)
{
    if (root == nullptr)
    {
        return false;
    }
    else if (root->value == value)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr)
        {
            BSTree *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr)
        {
            BSTree *temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            BSTree *temp = root->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            root->value = temp->value;
            return remove(root->right, temp->value);
        }
        return true;
    }
    else if (root->value > value)
    {
        return remove(root->left, value);
    }
    else
    {
        return remove(root->right, value);
    }
}