#pragma once
#include <stdint.h>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <iomanip>
#include <algorithm>

/**
 * @class binaryTree
 * 二叉树
 * @brief Represents a binary tree data structure.
 * 表示二叉树数据结构。
 *
 * The `binaryTree` class provides functionality to create, manipulate, and traverse a binary tree.
 * 二叉树类提供了创建、操作和遍历二叉树的功能。
 * It supports various operations such as insertion, deletion, sorting, and drawing of the tree.
 * 支持各种操作，如插入、删除、排序和绘制树。
 * It also provides methods to determine the type of the tree, such as binary sort tree, Huffman tree, or heap tree.
 * 它还提供了确定树类型的方法，如二叉排序树、哈夫曼树或堆树。
 *
 * @note This class assumes that the binary tree contains nodes with integer values.
 * 该类假设二叉树包含具有整数值的节点。
 */
class binaryTree
{
private:
    // Value of the node
    // 二叉树节点的值
    int32_t value;

    // The x and y coordinates of the nodes required to draw the binary tree
    // 绘制二叉树所需节点的x和y坐标
    int32_t x;
    int32_t y;

    // The height of the node
    // 节点的高度
    int height;

public:
    // The left and right child and parent of the node
    // 节点的左右孩子和父节点
    binaryTree *lchild, *rchild, *parent;

    // The flag of the binary tree type
    // 二叉树类型的标志
    bool isBinarySortTree;
    bool isHuffmanTree;
    bool isHeapTree;
    bool isAVLTree;

    // The constructor of the binary tree
    // 二叉树的构造函数
    binaryTree();

    // The constructor of the binary tree with the value
    // 二叉树的构造函数，带有值
    binaryTree(int32_t value);

    // Judge whether the tree is binary sort tree
    // 判断树是否为二叉排序树
    bool isBinarySort();

    // Judge whether the tree is huffman tree
    // 判断树是否为哈夫曼树
    bool isHuffman();

    // Judge whether the tree is heap tree
    // 判断树是否为堆
    bool isHeap();

    // Judge whether the tree is AVL tree
    // 判断树是否为AVL树
    bool isAVL();

    // Set the tree as binary sort tree
    // 将树设置为二叉排序树
    void BinarySortTrue();

    // Set the tree as huffman tree
    // 将树设置为哈夫曼树
    void HuffmanTrue();

    // Set the tree as heap tree
    // 将树设置为堆
    void heapTrue();

    // Set the tree as AVL tree
    // 将树设置为AVL树
    void AVLTrue();

    // Insert a node into the binary tree
    // 插入一个节点到二叉树中
    bool treeInsert_sort(int32_t value);

    // Sort the huffman tree
    // 排序哈夫曼树
    void sortHuffmanTree(std::vector<binaryTree *> &trees);

    // Build the huffman tree
    // 建立哈夫曼树
    binaryTree *buildHuffmanTree(std::vector<int> &trees);

    // Preorder traversal
    // 前序遍历
    void preorderTraversal();

    // Inorder traversal
    // 中序遍历
    void inorderTraversal();

    // Postorder traversal
    // 后序遍历
    void postorderTraversal();

    // Level order traversal
    // 层次遍历
    void levelOrderTraversal();

    // Find max deepth of the tree
    // 查找树的最大深度
    int32_t findMaxDeepth();

    // Using x and y of the nodes to draw the binary tree
    // 利用节点的x和y绘制二叉树
    void fillMapWithXandY(std::vector<std::vector<std::string>> &treeMap, binaryTree *tree, int32_t x, int32_t y);

    // Draw the tree
    // 绘制树
    void drawTheTree();

    // Find the weight path length of the huffman tree
    // 查找哈夫曼树的带权路径长度
    int32_t findWPL(binaryTree *p, int32_t length);

    // Delete a node from the sorted tree
    // 从二叉排序树中删除一个节点
    binaryTree *deleteNode_sortedTree(int32_t value);

    // Get the height of the tree
    // 获取树的高度
    int32_t getHeight(binaryTree *p);

    //Update the height of the tree
    //更新树的高度
    void updateHeight(binaryTree *p);

    // Get the balance factor of the tree
    // 获取树的平衡因子
    int32_t getBalanceFactor(binaryTree *p);

    // Right rotation
    // 右旋
    binaryTree *rightRotation(binaryTree *p);

    // Left rotation
    // 左旋
    binaryTree *leftRotation(binaryTree *p);

    // Rotate the tree
    // 旋转树
    binaryTree *rotate(binaryTree *p);

    // Insert a node into the AVL tree
    // 插入一个节点到AVL树中
    binaryTree *treeInsert_AVL(binaryTree *p, int32_t value);

    // Delete a node from the AVL tree
    // 从AVL树中删除一个节点
    binaryTree *deleteNode_AVL(binaryTree *p, int32_t value);
};