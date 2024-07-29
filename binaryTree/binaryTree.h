#pragma once
#include "templateFuntion.cpp"

enum COLOR
{
    RED,
    BLACK
};

class BinaryTree
{
public:
    int32_t x;
    int32_t y;
    int32_t height;
    BinaryTree();
};

class AVLTree : public BinaryTree
{
public:
    int32_t value;
    
    AVLTree *left, *right, *parent;
    
    AVLTree();

    AVLTree(int32_t value);

    AVLTree *const find(AVLTree *&root, int32_t value);

    // Get the height of the tree
    // 获取树的高度
    int32_t getHeight(AVLTree *p);

    // Update the height of the tree
    // 更新树的高度
    void updateHeight(AVLTree *p);

    // Get the balance factor of the tree
    // 获取树的平衡因子
    int32_t getBalanceFactor(AVLTree *root);

    // Rotate the tree
    // 旋转树
    AVLTree *rotate(AVLTree *p);

    // Insert a node into the AVL tree
    // 插入一个节点到AVL树中
    bool insert(AVLTree *root, int32_t value);

    // Delete a node from the AVL tree
    // 从AVL树中删除一个节点
    bool remove(AVLTree *root, int32_t value);
};

class BSTree : public BinaryTree
{
public:
    BSTree *left, *right, *parent;

    int32_t value;

    BSTree();

    BSTree(int32_t val);

    BSTree *const find(BSTree *&root, int32_t value);

    bool insert(BSTree *&root, int32_t value);

    bool remove(BSTree *&root, int32_t value);
};

class Heap : public BinaryTree
{
public:
    int32_t value;
    
    Heap *left, *right, *parent;

    Heap();

    Heap(int32_t value);

    Heap *const find(Heap *&root, int32_t value);

    bool insert(Heap *&root, int32_t value);

    bool remove(Heap *&root, int32_t value);

    void updateHeight(Heap *p);

    int32_t getHeight(Heap *p);

    bool buildBySifting(Heap *&root, const std::vector<int32_t> &valueArray);

    bool buildHeapByInserting(Heap *&root);
};

class HuffmanTree : public BinaryTree
{
public:
    HuffmanTree *left, *right, *parent;

    int32_t value;

    HuffmanTree();

    HuffmanTree(int32_t value);

    int32_t findWPL(HuffmanTree *p, int32_t length);

    bool insert(HuffmanTree *root, int32_t value);

    bool remove(HuffmanTree *root, int32_t value);
};

class RBTree : public BinaryTree
{
public:
    int32_t value;

    COLOR color;

    RBTree *left, *right, *parent;

    RBTree();

    RBTree(int32_t value);

    RBTree *const find(RBTree *&root, int32_t value);

    bool insert(RBTree *&root, int32_t value);

    void insertFixup(RBTree *&root, RBTree *node);

    void remove(RBTree *&root, int32_t value);

    void removeFixup(RBTree *&root, RBTree *node, RBTree* parent);
};