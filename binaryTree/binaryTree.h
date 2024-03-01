#pragma once
#include <stdint.h>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <cmath>
#include <iomanip>

// 二叉树节点类
/**
 * @brief 二叉树类
 */
class binaryTree
{
private:
    // 二叉树节点的值
    int32_t value;
    int32_t x;
    int32_t y;
    bool isHuffmanTree = false;

public:
    // 二叉树节点,创建左右孩子以及父亲指针
    binaryTree *lchild, *rchild, *father;

    // 默认构造函数
    binaryTree();

    /**
     * @brief 构造函数
     * @param value 节点的值
     */
    binaryTree(int32_t value);

    /**
     * @brief 判断是否为哈夫曼树
     * @return 如果是哈夫曼树返回true，否则返回false
     */
    bool isHuffman();

    /**
     * @brief 根据方法一创建树
     * @param value 节点的值
     * @return 如果创建成功返回true，否则返回false
     */
    bool treeInsert_sort(int32_t value);

    /**
     * @brief 对哈夫曼树节点进行排序
     * @param trees 哈夫曼树节点的数组
     */
    void sortHuffmanTree(std::vector<binaryTree *> &trees);

    /**
     * @brief 建立并返回哈夫曼树
     * @param trees 哈夫曼树节点的数组
     * @return 哈夫曼树的根节点
     */
    binaryTree *buildHuffmanTree(std::vector<binaryTree *> &trees);

    /**
     * @brief 建立并返回堆
     * @param trees 堆节点的数组
     * @return 堆的根节点
     */
    binaryTree *buildHeap(std::vector<int> &staticHeap);

    /**
     * @brief 前序遍历
     */
    void preorderTraversal();

    /**
     * @brief 中序遍历
     */
    void inorderTraversal();

    /**
     * @brief 后序遍历
     */
    void postorderTraversal();

    /**
     * @brief 层序遍历
     */
    void levelOrderTraversal();

    /**
     * @brief 寻找该树最大深度
     * @return 树的最大深度
     */
    int32_t findMaxDeepth();

    /**
     * @brief 利用坐标绘制树
     * @param treeMap 树状图数组
     * @param tree 当前节点
     * @param x 当前节点的行坐标
     * @param y 当前节点的列坐标
     */
    void fillMapWithXandY(std::vector<std::vector<std::string>> &treeMap, binaryTree *tree, int32_t x, int32_t y);

    /**
     * @brief 利用层序遍历绘制树
     */
    void drawTheTree();

    /**
     * @brief 求哈夫曼树的WPL
     * @param p 当前节点
     * @param length 当前节点到根节点的路径长度
     * @return 哈夫曼树的WPL
     */
    int32_t findWPL(binaryTree *p, int32_t length);
};