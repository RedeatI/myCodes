#include "BinaryTree.h"

Heap::Heap()
{
    value = 0;
    left = right = parent = nullptr;
    height = 0;
}

Heap::Heap(int32_t value)
{
    this->value = value;
    left = right = parent = nullptr;
    height = 1;
}

Heap *const Heap::find(Heap *&root, int32_t value)
{
    Heap *p = root;
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

int32_t Heap::getHeight(Heap *p)
{
    return p ? p->height : 0;
}

void Heap::updateHeight(Heap *p)
{
    p->height = std::max(getHeight(p->left), getHeight(p->right)) + 1;
}

bool Heap::insert(Heap *&root, int32_t value)
{
    Heap *p = root;
    Heap *q = nullptr;
    while (p)
    {
        q = p;
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
    p = new Heap(value);
    if (q == nullptr)
    {
        root = p;
    }
    else if (value < q->value)
    {
        q->left = p;
    }
    else
    {
        q->right = p;
    }
    p->parent = q;
    updateHeight(p);
    while (q)
    {
        updateHeight(q);
        q = q->parent;
    }
    return true;
}

bool Heap::remove(Heap *&root, int32_t value)
{
    Heap *p = root;
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
            break;
        }
    }
    if (p == nullptr)
    {
        return false;
    }
    if (p->left && p->right)
    {
        Heap *q = p->left;
        while (q->right)
        {
            q = q->right;
        }
        p->value = q->value;
        p = q;
    }
    Heap *child = p->left ? p->left : p->right;
    if (child)
    {
        child->parent = p->parent;
    }
    if (p->parent == nullptr)
    {
        root = child;
    }
    else if (p == p->parent->left)
    {
        p->parent->left = child;
    }
    else
    {
        p->parent->right = child;
    }
    Heap *q = p->parent;
    delete p;
    while (q)
    {
        updateHeight(q);
        q = q->parent;
    }
    return true;
}

bool Heap::buildBySifting(Heap *&root, const std::vector<int32_t> &valueArray)
{
    for (int32_t i = 0; i < valueArray.size(); i++)
    {
        if (!insert(root, valueArray[i]))
        {
            return false;
        }
    }
    return true;
}

bool Heap::buildHeapByInserting(Heap *&root)
{
    int32_t value;
    while (std::cin >> value)
    {
        if (value == -1)
        {
            break;
        }
        if (!insert(root, value))
        {
            return false;
        }
    }
    return true;
}