#include "BinaryTree.h"

AVLTree::AVLTree()
{
    value = 0;
    left = right = parent = nullptr;
    height = 0;
}

AVLTree::AVLTree(int32_t value)
{
    this->value = value;
    left = right = parent = nullptr;
    height = 1;
}

AVLTree *const AVLTree::find(AVLTree *&root, int32_t value)
{
    AVLTree *p = root;
    while (p)
    {
        if (value < p->value)
        {
            p = p->left;
        }
        else if (value > p->value)
        {
            p = p->right;
        }
        else
        {
            return p;
        }
    }
    return nullptr;
}

// Get the height of the tree
// 获取树的高度
int32_t AVLTree::getHeight(AVLTree *p)
{
    return p ? p->height : 0;
}

// Update the height of the tree
// 更新树的高度
void AVLTree::updateHeight(AVLTree *p)
{
    p->height = std::max(getHeight(p->left), getHeight(p->right)) + 1;
}

// Get the balance factor of the tree
// 获取树的平衡因子
int32_t AVLTree::getBalanceFactor(AVLTree *p)
{
    return p ? getHeight(p->left) - getHeight(p->right) : 0;
}

// Rotate the tree
// 旋转树
AVLTree *AVLTree::rotate(AVLTree *p)
{
    if (getBalanceFactor(p) > 1)
    {
        if (getBalanceFactor(p->left) < 0)
        {
            p->left = rotate(p->left);
        }
        AVLTree *left = p->left;
        p->left = left->right;
        left->right = p;
        updateHeight(p);
        updateHeight(left);
        return left;
    }
    else if (getBalanceFactor(p) < -1)
    {
        if (getBalanceFactor(p->right) > 0)
        {
            p->right = rotate(p->right);
        }
        AVLTree *right = p->right;
        p->right = right->left;
        right->left = p;
        updateHeight(p);
        updateHeight(right);
        return right;
    }
    return p;
}

// Insert a node into the AVL tree
// 插入一个节点到AVL树中
bool AVLTree::insert(AVLTree *root, int32_t value)
{
    AVLTree *p = root;
    AVLTree *parent = nullptr;
    while (p)
    {
        parent = p;
        if (value < p->value)
        {
            p = p->left;
        }
        else if (value > p->value)
        {
            p = p->right;
        }
        else
        {
            return false;
        }
    }
    p = new AVLTree(value);
    if (!parent)
    {
        root = p;
    }
    else if (value < parent->value)
    {
        parent->left = p;
    }
    else
    {
        parent->right = p;
    }
    p->parent = parent;
    while (parent)
    {
        updateHeight(parent);
        parent = parent->parent;
    }
    return true;
}

// Delete a node from the AVL tree
// 从AVL树中删除一个节点
bool AVLTree::remove(AVLTree *p, int32_t value)
{
    if (!p)
    {
        return false;
    }
    if (value < p->value)
    {
        if (remove(p->left, value))
        {
            updateHeight(p);
            p = rotate(p);
            return true;
        }
    }
    else if (value > p->value)
    {
        if (remove(p->right, value))
        {
            updateHeight(p);
            p = rotate(p);
            return true;
        }
    }
    else
    {
        if (!p->left && !p->right)
        {
            delete p;
            p = nullptr;
            return true;
        }
        else if (p->left && !p->right)
        {
            AVLTree *temp = p;
            p = p->left;
            delete temp;
            return true;
        }
        else if (!p->left && p->right)
        {
            AVLTree *temp = p;
            p = p->right;
            delete temp;
            return true;
        }
        else
        {
            AVLTree *temp = p->right;
            while (temp->left)
            {
                temp = temp->left;
            }
            p->value = temp->value;
            if (remove(p->right, temp->value))
            {
                updateHeight(p);
                p = rotate(p);
                return true;
            }
        }
    }
    return false;
}
