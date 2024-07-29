#include "BinaryTree.h"

HuffmanTree::HuffmanTree()
{
    value = INT_MIN;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

HuffmanTree::HuffmanTree(int32_t value)
{
    this->value = value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

// Find the WPL of the tree
// 寻找树的WPL
int32_t HuffmanTree::findWPL(HuffmanTree *p, int32_t length)
{
    // If left and right child are both not empty, return the sum of the WPL of the left and right child
    // 若左右孩子均不为空，则返回左右孩子的WPL之和
    if (p->left && p->right)
    {
        return findWPL(p->left, length + 1) + findWPL(p->right, length + 1);
    }
    // If left and right child are have at least one empty node (the current node is a leaf node),
    // return the value of the current node multiplied by the length
    // 若左右孩子至少有一个空节点(当前节点为叶子节点)，则返回当前节点的值乘以长度
    else if (p->left || p->right)
    {
        HuffmanTree *child = p->left ? p->left : p->right;
        return p->value * length + findWPL(child, length + 1);
    }
    // If left and right child are both empty, return the value of the current node multiplied by the length
    // 若左右孩子均为空，则返回当前节点的值乘以长度
    return p->value * length;
}

// Insert a node into the huffman tree
// 插入一个节点到哈夫曼树
bool HuffmanTree::insert(HuffmanTree *root, int32_t value)
{
    // If the root is empty, create a new node and set the value
    // 若根节点为空，则创建一个新节点并设置值
    if (!root)
    {
        root = new HuffmanTree(value);
        return true;
    }
    // If the value is less than the root value, insert it into the left child
    // 若值小于根节点值，则插入到左孩子
    if (value < root->value)
    {
        if (!root->left)
        {
            root->left = new HuffmanTree(value);
            root->left->parent = root;
            return true;
        }
        return insert(root->left, value);
    }
    // If the value is greater than the root value, insert it into the right child
    // 若值大于根节点值，则插入到右孩子
    if (value > root->value)
    {
        if (!root->right)
        {
            root->right = new HuffmanTree(value);
            root->right->parent = root;
            return true;
        }
        return insert(root->right, value);
    }
    return false;
}

// Remove a node from the huffman tree
// 从哈夫曼树中删除一个节点
bool HuffmanTree::remove(HuffmanTree *root, int32_t value)
{
    // If the root is empty, return false
    // 若根节点为空，则返回false
    if (!root)
    {
        return false;
    }
    // If the value is less than the root value, remove it from the left child
    // 若值小于根节点值，则从左孩子中删除
    if (value < root->value)
    {
        return remove(root->left, value);
    }
    // If the value is greater than the root value, remove it from the right child
    // 若值大于根节点值，则从右孩子中删除
    if (value > root->value)
    {
        return remove(root->right, value);
    }
    // If the value is equal to the root value
    // 若值等于根节点值
    // If the left child is empty, set the right child as the root
    // 若左孩子为空，则将右孩子设置为根节点
    if (!root->left)
    {
        HuffmanTree *temp = root->right;
        delete root;
        root = temp;
        return true;
    }
    // If the right child is empty, set the left child as the root
    // 若右孩子为空，则将左孩子设置为根节点
    if (!root->right)
    {
        HuffmanTree *temp = root->left;
        delete root;
        root = temp;
        return true;
    }
    // If the left and right child are both not empty
    // 若左右孩子均不为空
    // Find the minimum value of the right child
    // 寻找右孩子的最小值
    HuffmanTree *temp = root->right;
    while (temp->left)
    {
        temp = temp->left;
    }
    // Set the value of the minimum value of the right child to the root value
    // 将右孩子的最小值设置为根节点值
    root->value = temp->value;
    // Remove the minimum value of the right child
    // 删除右孩子的最小值
    return remove(root->right, temp->value);
}