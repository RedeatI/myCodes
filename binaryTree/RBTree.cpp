#include "BinaryTree.h"

RBTree::RBTree() : BinaryTree()
{
    value = INT_MIN;
    color = COLOR::RED;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

RBTree::RBTree(int32_t value) : BinaryTree()
{
    this->value = value;
    color = COLOR::RED;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

RBTree *const RBTree::find(RBTree *&root, int32_t value)
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

bool RBTree::insert(RBTree *&root, int32_t value) // 注意这里的引用传递
{
    if (!root) // 如果树为空，则直接创建根节点
    {
        root = new RBTree(value);
        root->color = COLOR::BLACK;
        return true;
    }
    else if (root->value == INT_MIN) // 如果当前节点是初始节点
    {
        root->value = value;
        root->color = COLOR::BLACK;
        return true;
    }

    RBTree *node = new RBTree(value);
    RBTree *temp = root;
    while (temp)
    {
        if (temp->value == value)
        {
            delete node; // 如果值已存在，删除新节点并返回false
            return false;
        }
        else if (temp->value > value)
        {
            if (!temp->left)
            {
                temp->left = node;
                node->parent = temp;
                break;
            }
            temp = temp->left;
        }
        else
        {
            if (!temp->right)
            {
                temp->right = node;
                node->parent = temp;
                break;
            }
            temp = temp->right;
        }
    }
    insertFixup(root, node); // 修复可能的红黑树性质破坏
    return true;
}

void RBTree::insertFixup(RBTree *&root, RBTree *node)
{
    while (node != root && node->parent && node->parent->color == COLOR::RED)
    {
        RBTree *uncle = nullptr;
        bool leftSide = node->parent == node->parent->parent->left;
        uncle = leftSide ? node->parent->parent->right : node->parent->parent->left;

        if (uncle && uncle->color == COLOR::RED)
        {
            // 情况1：叔叔节点是红色
            node->parent->color = COLOR::BLACK;
            uncle->color = COLOR::BLACK;
            node->parent->parent->color = COLOR::RED;
            node = node->parent->parent;
        }
        else
        {
            if (leftSide)
            {
                if (node == node->parent->right)
                {
                    // 情况2：节点是右孩子
                    node = node->parent;
                    leftRotate(root, node);
                }
                // 情况3：节点是左孩子
                node->parent->color = COLOR::BLACK;
                node->parent->parent->color = COLOR::RED;
                rightRotate(root, node->parent->parent);
            }
            else
            {
                if (node == node->parent->left)
                {
                    // 情况2：节点是左孩子
                    node = node->parent;
                    rightRotate(root, node);
                }
                // 情况3：节点是右孩子
                node->parent->color = COLOR::BLACK;
                node->parent->parent->color = COLOR::RED;
                leftRotate(root, node->parent->parent);
            }
        }
    }
    root->color = COLOR::BLACK; // 确保根节点始终是黑色
}

void transplant(RBTree *&root, RBTree *u, RBTree *v)
{
    if (u->parent == nullptr)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    if (v)
    {
        v->parent = u->parent;
    }
}

RBTree *minimum(RBTree *node)
{
    while (node->left)
    {
        node = node->left;
    }
    return node;
}

void RBTree::remove(RBTree *&root, int32_t value)
{
    RBTree *node = RBTree::find(root, value);
    if (node == nullptr)
    {
        return;
    }

    RBTree *child = nullptr;
    RBTree *parent = nullptr;
    COLOR originalColor = node->color;

    if (node->left == nullptr || node->right == nullptr)
    {
        parent = node->parent; // 更新parent
    }

    if (node->left == nullptr)
    {
        child = node->right;
        transplant(root, node, node->right);
    }
    else if (node->right == nullptr)
    {
        child = node->left;
        transplant(root, node, node->left);
    }
    else
    {
        RBTree *successor = minimum(node->right);
        originalColor = successor->color;
        child = successor->right;
        parent = successor->parent; // 更新parent为后继的父节点
        if (successor->parent == node)
        {
            parent = successor; // 特殊情况：后继节点是删除节点的直接子节点
        }
        else
        {
            transplant(root, successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }
        transplant(root, node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
        successor->color = node->color;
    }

    if (originalColor == COLOR::BLACK)
    {
        removeFixup(root, child, parent);
    }

    delete node;
}

void RBTree::removeFixup(RBTree *&root, RBTree *node, RBTree *parent)
{
    while ((node == nullptr || node->color == COLOR::BLACK) && node != root)
    {
        if (node == parent->left)
        {
            RBTree *sibling = parent->right;
            if (sibling != nullptr && sibling->color == COLOR::RED)
            {
                sibling->color = COLOR::BLACK;
                parent->color = COLOR::RED;
                leftRotate(root, parent);
                sibling = parent->right;
            }
            if ((sibling == nullptr) ||
                (sibling->left == nullptr || sibling->left->color == COLOR::BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == COLOR::BLACK))
            {
                if (sibling != nullptr)
                {
                    sibling->color = COLOR::RED;
                }
                node = parent;
                parent = node->parent; // 更新parent
            }
            else
            {
                if (sibling->right == nullptr || sibling->right->color == COLOR::BLACK)
                {
                    if (sibling->left != nullptr)
                    {
                        sibling->left->color = COLOR::BLACK;
                    }
                    sibling->color = COLOR::RED;
                    rightRotate(root, sibling);
                    sibling = parent->right;
                }
                sibling->color = parent->color;
                parent->color = COLOR::BLACK;
                if (sibling->right != nullptr)
                {
                    sibling->right->color = COLOR::BLACK;
                }
                leftRotate(root, parent);
                node = root; // 修复完成，退出循环
            }
        }
        else
        {
            // 对称的逻辑处理node为parent的右子节点的情况
            RBTree *sibling = parent->left;
            if (sibling != nullptr && sibling->color == COLOR::RED)
            {
                sibling->color = COLOR::BLACK;
                parent->color = COLOR::RED;
                rightRotate(root, parent);
                sibling = parent->left;
            }
            if ((sibling == nullptr) ||
                (sibling->right == nullptr || sibling->right->color == COLOR::BLACK) &&
                    (sibling->left == nullptr || sibling->left->color == COLOR::BLACK))
            {
                if (sibling != nullptr)
                {
                    sibling->color = COLOR::RED;
                }
                node = parent;
                parent = node->parent; // 更新parent
            }
            else
            {
                if (sibling->left == nullptr || sibling->left->color == COLOR::BLACK)
                {
                    if (sibling->right != nullptr)
                    {
                        sibling->right->color = COLOR::BLACK;
                    }
                    sibling->color = COLOR::RED;
                    leftRotate(root, sibling);
                    sibling = parent->left;
                }
                sibling->color = parent->color;
                parent->color = COLOR::BLACK;
                if (sibling->left != nullptr)
                {
                    sibling->left->color = COLOR::BLACK;
                }
                rightRotate(root, parent);
                node = root; // 修复完成，退出循环
            }
        }
    }
    if (node != nullptr)
    {
        node->color = COLOR::BLACK;
    }
}