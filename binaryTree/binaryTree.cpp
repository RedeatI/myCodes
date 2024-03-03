#pragma once
#include "binaryTree.h"
#include <iostream>
using namespace std;

// 以数组的方式创建堆
binaryTree *buildHeapByArray(vector<int32_t> &staticHeap)
{
    // 创建堆
    // 创建根节点
    binaryTree *heap = new binaryTree(staticHeap[0]);

    // 创建队列
    queue<binaryTree *> treeQueue;

    // 将根节点加入队列
    treeQueue.push(heap);

    // 逐步创建堆
    for (int32_t i = 0; i < staticHeap.size() / 2; ++i)
    {
        // 若左孩子不为空，则创建左孩子
        if (2 * i + 1 < staticHeap.size())
        {
            treeQueue.front()->lchild = new binaryTree(staticHeap[2 * i + 1]);
            treeQueue.push(treeQueue.front()->lchild);
        }

        // 若右孩子不为空，则创建右孩子
        if (2 * i + 2 < staticHeap.size())
        {
            treeQueue.front()->rchild = new binaryTree(staticHeap[2 * i + 2]);
            treeQueue.push(treeQueue.front()->rchild);
        }

        // 当前节点出列
        treeQueue.pop();
    }

    // 返回堆
    return heap;
}

// 堆插入
void heapInsert(vector<int32_t> &staticHeap, int32_t value)
{
    // 插入节点至数组
    staticHeap.push_back(value);

    // 调整堆
    // 获取插入节点的下标
    int32_t index = staticHeap.size() - 1;

    // 获取父节点的下标
    int32_t parent = (index - 1) / 2;

    // 若插入节点大于父节点则交换
    while (staticHeap[index] > staticHeap[parent])
    {
        // 交换节点
        swap(staticHeap[index], staticHeap[parent]);

        // 更新插入节点下标
        index = parent;

        // 更新父节点下标
        parent = (index - 1) / 2;
    }
}

// 堆调整
void maxHeapify(vector<int> &staticHeap, int i, int n)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int max = i;

    // 若左孩子大于父节点,则记录左孩子的下标
    if (l < n && staticHeap[l] > staticHeap[max])
    {
        max = l;
    }

    // 若右孩子大于父节点,则记录右孩子的下标
    if (r < n && staticHeap[r] > staticHeap[max])
    {
        max = r;
    }

    // 若父节点不是最大值，则交换
    if (max != i)
    {
        swap(staticHeap[i], staticHeap[max]);

        // 递归调整堆
        maxHeapify(staticHeap, max, n);
    }
}

// 以筛选法创建堆
binaryTree *buildHeapBySift(vector<int32_t> &staticHeap)
{

    int32_t n = staticHeap.size();

    // 从最后一个非叶子节点开始调整堆
    for (int32_t i = n / 2 - 1; i >= 0; --i)
    {
        maxHeapify(staticHeap, i, n);
    }

    // 返回堆
    return buildHeapByArray(staticHeap);
}

binaryTree::binaryTree()
{
    value = 0;
    lchild = nullptr;
    rchild = nullptr;
    father = nullptr;
    isHuffmanTree = false;
}

binaryTree::binaryTree(int32_t value)
{
    this->value = value;
    lchild = nullptr;
    rchild = nullptr;
    father = nullptr;
    isHuffmanTree = false;
}

bool binaryTree::isHuffman()
{
    return this->isHuffmanTree;
}

bool binaryTree::treeInsert_sort(int32_t value)
{
    // 创建p指针指向当前节点
    binaryTree *p = this;

    // 如果树为空则创建根节点
    if (p->value == 0)
    {
        p->value = value;
        return true;
    }

    // 如果树不为空则插入节点
    while (true)
    {
        // 如果插入值小于当前节点值则插入左孩子
        if (value < p->value)
        {
            // 如果左孩子为空则创建左孩子
            if (p->lchild == nullptr)
            {
                p->lchild = new binaryTree(value);
                return true;
            }
            p = p->lchild;
        }
        // 如果插入值大于当前节点值则插入右孩子
        else if (value > p->value)
        {
            // 如果右孩子为空则创建右孩子

            if (p->rchild == nullptr)
            {
                p->rchild = new binaryTree(value);
                return true;
            }
            p = p->rchild;
        }
        // 如果插入值等于当前节点值则插入失败
        else
        {
            cout << "Insert failed, don't enter the same number." << endl;
            return false;
        }
    }

    // 插入失败
    return false;
}

void binaryTree::sortHuffmanTree(vector<binaryTree *> &trees)
{
    // 对哈夫曼树节点进行排序
    sort(trees.begin(), trees.end(), [](binaryTree *a, binaryTree *b)
         { return a->value < b->value; });
}

binaryTree *binaryTree::buildHuffmanTree(vector<binaryTree *> &trees)
{
    int32_t n = trees.size();

    // 逐步构建哈夫曼树
    for (int32_t i = 0; i < n - 1; ++i)
    {
        // 排序哈夫曼树节点大小
        sortHuffmanTree(trees);

        // 创建父亲节点并连接左右孩子
        trees[i]->father = new binaryTree(trees[i]->value + trees[i + 1]->value);
        trees[i]->father->lchild = trees[i];
        trees[i]->father->rchild = trees[i + 1];

        // 将父亲节点加入数组
        trees[i + 1] = trees[i]->father;
    }

    // 标记哈夫曼树
    trees[n - 1]->isHuffmanTree = true;

    // 返回哈夫曼树
    return trees[n - 1];
}

void binaryTree::preorderTraversal()
{
    // 输出当前节点的值
    cout << value << " -> ";

    // 如果左孩子不为空则前序遍历左孩子
    if (lchild)
        lchild->preorderTraversal();

    // 如果右孩子不为空则前序遍历右孩子
    if (rchild)
        rchild->preorderTraversal();
}

void binaryTree::inorderTraversal()
{
    // 如果左孩子不为空则中序遍历左孩子
    if (lchild)
        lchild->inorderTraversal();

    // 输出当前节点的值
    cout << value << " -> ";

    // 如果右孩子不为空则中序遍历右孩子
    if (rchild)
        rchild->inorderTraversal();
}

void binaryTree::postorderTraversal()
{
    // 如果左孩子不为空则后序遍历左孩子
    if (lchild)
        lchild->postorderTraversal();

    // 如果右孩子不为空则后序遍历右孩子
    if (rchild)
        rchild->postorderTraversal();

    // 输出当前节点的值
    cout << value << " -> ";
}

void binaryTree::levelOrderTraversal()
{
    // 队列实现层序遍历
    // 创建队列
    queue<binaryTree *> treeQueue;

    // 将根节点加入队列
    treeQueue.push(this);

    // 当队列非空
    while (!treeQueue.empty())
    {
        // 输出当前节点的值
        cout << treeQueue.front()->value << " -> ";

        // 若当前节点左子树非空，则将其加入队列
        if (treeQueue.front()->lchild)
            treeQueue.emplace(treeQueue.front()->lchild);

        // 若当前节点右子树非空，则将其加入队列
        if (treeQueue.front()->rchild)
            treeQueue.emplace(treeQueue.front()->rchild);

        // 当前节点出列
        treeQueue.pop();
    }
}

int32_t binaryTree::findMaxDeepth()
{
    // 递归寻找最大深度
    // 若左右孩子均为空，则返回1，否则返回左右孩子的最大深度之和加1
    return 1 + max(this->lchild ? this->lchild->findMaxDeepth() : 0, this->rchild ? this->rchild->findMaxDeepth() : 0);
}

void binaryTree::fillMapWithXandY(vector<vector<string>> &treeMap, binaryTree *p, int32_t x, int32_t y)
{
    // 将节点值转化为字符串并填充数组
    treeMap[x][y] = to_string(p->value);

    // 若左孩子不为空，则填充↙
    if (p->lchild)
    {
        treeMap[x + 1][y - 1] = "↙";
    }
    // 若右孩子不为空，则填充↘
    if (p->rchild)
    {
        treeMap[x + 1][y + 1] = "↘";
    }
}

/**
 * Draws the binary tree in a tree-like structure.
 *
 * This function calculates the maximum depth of the tree and creates a tree map array
 * to represent the tree structure. It performs a level-order traversal using a queue
 * and assigns coordinates to each node in the tree map array. Finally, it prints the
 * tree map to visualize the binary tree.
 *
 * @note This function assumes that the binary tree is not empty.
 */
void binaryTree::drawTheTree()
{
    // 若树为空则输出提示信息
    if (!this)
    {
        cout << "The tree is empty." << endl;
        return;
    }

    // 获取树的最大深度
    int32_t maxDeepth = this->findMaxDeepth();

    // 创建树状图数组
    // n为行数，m为列数
    int32_t n = maxDeepth * 2 - 1;
    int32_t m = (maxDeepth > 1) ? (3 * pow(2, maxDeepth - 1) - 1) : 1;

    // 设置根节点的坐标
    this->x = 0;
    this->y = m / 2;

    // 初始化数组
    vector<vector<string>> treeMap(n, vector<string>(m, ""));

    // 队列实现层序遍历
    queue<binaryTree *> treeQueue;
    treeQueue.push(this);

    // 设置偏移量
    int32_t offset = m / 4;

    // 记录当前层数
    int32_t floorNow = 0;

    // 当队列非空
    while (!treeQueue.empty())
    {
        // 将子树加入队列并获取每个节点在数组中的坐标

        // 若左孩子不为空，则将其加入队列
        if (treeQueue.front()->lchild)
        {
            treeQueue.emplace(treeQueue.front()->lchild);

            // 设置左孩子的坐标
            treeQueue.front()->lchild->x = treeQueue.front()->x + 2;
            treeQueue.front()->lchild->y = treeQueue.front()->y - offset;
        }
        // 若右孩子不为空，则将其加入队列
        if (treeQueue.front()->rchild)
        {
            treeQueue.emplace(treeQueue.front()->rchild);

            // 设置右孩子的坐标
            treeQueue.front()->rchild->x = treeQueue.front()->x + 2;
            treeQueue.front()->rchild->y = treeQueue.front()->y + offset;
        }

        // 填充数组
        treeQueue.front()->fillMapWithXandY(treeMap, treeQueue.front(), treeQueue.front()->x, treeQueue.front()->y);

        // 当前节点出列
        treeQueue.pop();

        // 判断当前层数并依据当前层数降低偏移量
        // 当队列非空且节点深度与记录深度不符(最大深度减去队列首节点的最大深度大于当前层数)时
        if (!treeQueue.empty() && maxDeepth - treeQueue.front()->findMaxDeepth() > floorNow)
        {
            // 记录当前层数
            floorNow = maxDeepth - treeQueue.front()->findMaxDeepth();

            // 降低偏移量
            offset /= 2;
        }
    }

    // 输出树状图
    for (const auto &row : treeMap)
    {
        for (const auto &cell : row)
        {
            // 输出数组
            cout << left << setw(1) << setfill(' ') << cell;
        }
        cout << endl;
    }
}

int32_t binaryTree::findWPL(binaryTree *p, int32_t length)
{
    // 若左右孩子均不为空，则返回左右孩子的WPL之和
    if (p->lchild && p->rchild)
    {
        return findWPL(p->lchild, length + 1) + findWPL(p->rchild, length + 1);
    }
    // 若左右孩子至少有一个空节点(当前节点为叶子节点)，则返回当前节点的值乘以长度
    else if (p->lchild || p->rchild)
    {
        binaryTree *child = p->lchild ? p->lchild : p->rchild;
        return p->value * length + findWPL(child, length + 1);
    }
    // 若左右孩子均为空，则返回当前节点的值乘以长度
    return p->value * length;
}