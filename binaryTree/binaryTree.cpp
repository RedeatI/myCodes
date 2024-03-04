#pragma once
#include "binaryTree.h"
#include <iostream>
using namespace std;

// First time to ask
// 询问用户需要创建的树
void firstAsk()
{
    cout << "Select a tree that what you want to create." << endl;
    cout << "选择你想创建的树：" << endl;
    cout << "1 : binary sort tree(二叉排序树)" << endl;
    cout << "2 : huffman tree(哈夫曼树)" << endl;
    cout << "3 : heap, Sift(堆，筛选法)" << endl;
    cout << "4 : heap, Insert(堆，插入法)" << endl;
    cout << "5 : AVL tree(平衡二叉树)" << endl
         << endl;
}

// Show the helps
// 显示帮助
void showHelps()
{
    // Select a way to traverse the tree
    // 选择遍历树的方式
    cout << endl;
    cout << "Choose a way to traverse your tree" << endl;
    cout << "选择遍历方式：" << endl;
    cout << "1 : Preorder Traversal(前序遍历)" << endl;
    cout << "2 : Inorder Traversal(中序遍历)" << endl;
    cout << "3 : Postorder Traversal(后序遍历)" << endl;
    cout << "4 : Level Order Traversal(层序遍历)" << endl
         << endl;

    // Others
    // 其他选项
    cout << "Others(其他选项):" << endl;
    cout << "5 : Draw the tree(显示树图)" << endl;
    cout << "10 : Add node(增加节点)" << endl;
    cout << "11 : Delete node(删除节点)" << endl;
    cout << "-1 : Rebuild the tree(重建树)" << endl;
    cout << "0 : exit the program(退出程序)" << endl
         << endl;
    cout << "other number : show the helps again" << endl;
    cout << "其他 : 显示帮助" << endl;
}

// Mark as binary sort tree
// 标记为二叉排序树
void binaryTree::BinarySortTrue()
{
    this->isBinarySortTree = true;
}

// Mark as huffman tree
// 标记为哈夫曼树
void binaryTree::HuffmanTrue()
{
    this->isHuffmanTree = true;
}

// Mark as heap
// 标记为堆
void binaryTree::heapTrue()
{
    this->isHeapTree = true;
}

// Mark as AVL tree
// 标记为AVL树
void binaryTree::AVLTrue()
{
    this->isAVLTree = true;
}

// Create a binary sort tree by array
// 根据数组创建二叉排序树
binaryTree *buildHeapByArray(vector<int32_t> &valueArray)
{
    // Create Heap
    // 创建堆
    // Create the root node
    // 创建根节点
    binaryTree *heap = new binaryTree(valueArray[0]);

    // Create a queue to store the tree
    // 创建队列存储树
    queue<binaryTree *> treeQueue;

    // Add the root node to the queue
    // 将根节点加入队列
    treeQueue.push(heap);

    // Create the heap by array
    // 通过数组创建堆
    for (int32_t i = 0; i < valueArray.size() / 2; ++i)
    {
        // If the left child is not empty, create the left child
        // 若左孩子不为空，则创建左孩子
        if (2 * i + 1 < valueArray.size())
        {
            treeQueue.front()->lchild = new binaryTree(valueArray[2 * i + 1]);
            treeQueue.push(treeQueue.front()->lchild);
        }

        // If the right child is not empty, create the right child
        // 若右孩子不为空，则创建右孩子
        if (2 * i + 2 < valueArray.size())
        {
            treeQueue.front()->rchild = new binaryTree(valueArray[2 * i + 2]);
            treeQueue.push(treeQueue.front()->rchild);
        }

        // The front node out of the queue
        // 队列首节点出列
        treeQueue.pop();
    }

    // Mark as heap
    // 标记为堆
    heap->heapTrue();

    // Return the heap
    // 返回堆
    return heap;
}

// Adjust the heap by insert method
// 通过插入法调整堆
void heapSort(vector<int32_t> &valueArray)
{
    // Get the index of the inserted node
    // 获取插入节点的下标
    int32_t index = valueArray.size() - 1;

    // Get the parent node of the inserted node
    // 获取插入节点的父节点
    int32_t parent = (index - 1) / 2;

    // If the value of the inserted node is greater than the value of the parent node, exchange the node
    // 若插入节点的值大于父节点的值，则交换节点
    while (valueArray[index] > valueArray[parent])
    {
        // Exchange the node 交换节点
        swap(valueArray[index], valueArray[parent]);

        // Update the index of the inserted node
        // 更新插入节点的下标
        index = parent;

        // Update the parent node of the inserted node
        // 更新插入节点的父节点
        parent = (index - 1) / 2;
    }
}

// Insert a node to the heap by insert method
// 通过插入法向堆中插入节点
void heapInsert(vector<int32_t> &valueArray, int32_t value)
{
    // Insert the node to the array
    // 插入节点至数组
    valueArray.push_back(value);
    heapSort(valueArray);
}

// Adjust the heap by sift method
// 通过筛选法调整堆
void maxHeapify(vector<int> &valueArray, int i, int n)
{
    // Get the left and right child of the parent node
    // 获取父节点的左右孩子
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int max = i;

    // If the left child is greater than the parent node, record the index of the left child
    // 若左孩子大于父节点，则记录左孩子的下标
    if (l < n && valueArray[l] > valueArray[max])
    {
        max = l;
    }

    // If the right child is greater than the parent node, record the index of the right child
    // 若右孩子大于父节点，则记录右孩子的下标
    if (r < n && valueArray[r] > valueArray[max])
    {
        max = r;
    }

    // If the parent node is not the maximum, exchange the parent node and the maximum node
    // 若父节点不是最大值，则交换父节点和最大值
    if (max != i)
    {
        swap(valueArray[i], valueArray[max]);

        // Recursively adjust the heap
        // 递归调整堆
        maxHeapify(valueArray, max, n);
    }
}

// Build a heap by sift method
// 通过筛选法建立堆
binaryTree *buildHeapBySift(vector<int32_t> &valueArray)
{
    // Get the size of the array
    // 获取数组大小
    int32_t n = valueArray.size();

    // Adjust the heap by last parent node
    // 通过最后一个父节点调整堆
    for (int32_t i = n / 2 - 1; i >= 0; --i)
    {
        maxHeapify(valueArray, i, n);
    }

    // Return the heap
    // 返回堆
    return buildHeapByArray(valueArray);
}

// Default constructor
// 构造函数
binaryTree::binaryTree()
{
    value = 0;
    height = 0;
    lchild = nullptr;
    rchild = nullptr;
    parent = nullptr;
    isBinarySortTree = false;
    isHuffmanTree = false;
    isHeapTree = false;
}

// Constructor with value
// 构造函数
binaryTree::binaryTree(int32_t value)
{
    this->value = value;
    height = 0;
    lchild = nullptr;
    rchild = nullptr;
    parent = nullptr;
    isBinarySortTree = false;
    isHuffmanTree = false;
    isHeapTree = false;
}

// Judge whether it is a binary sort tree
// 判断是否为二叉排序树
bool binaryTree::isBinarySort()
{
    return this->isBinarySortTree;
}

// Judge whether it is a huffman tree
// 判断是否为哈夫曼树
bool binaryTree::isHuffman()
{
    return this->isHuffmanTree;
}

// Judge whether it is a heap
// 判断是否为堆
bool binaryTree::isHeap()
{
    return this->isHeapTree;
}

// Judge whether it is a AVL tree
// 判断是否为AVL树
bool binaryTree::isAVL()
{
    return this->isAVLTree;
}

// Create a binary sort tree by insert method
// 通过插入法创建二叉排序树
bool binaryTree::treeInsert_sort(int32_t value)
{
    // Mark as binary sort tree
    // 标记为二叉排序树
    this->isBinarySortTree = true;

    // Create p pointer to the current node
    // 创建p指针指向当前节点
    binaryTree *p = this;

    // If the value of the current node is empty, create the current node
    // 若当前节点的值为空，则创建当前节点
    if (p->value == 0)
    {
        p->value = value;
        return true;
    }

    // If the insert value is less than the current node value, insert the left child
    // 若插入值小于当前节点值，则插入左孩子
    if (value < p->value)
    {
        // If the left child is empty, create the left child
        // 若左孩子为空则创建左孩子
        if (p->lchild == nullptr)
        {
            p->lchild = new binaryTree(value);
            // Mark as binary sort tree
            // 标记为二叉排序树
            p->lchild->BinarySortTrue();
            // Set the parent node
            // 设置父节点
            p->lchild->parent = p;
            return true;
        }

        // Recursively insert the left child
        // 递归插入左孩子
        p->lchild->treeInsert_sort(value);
    }
    // If the insert value is greater than the current node value, insert the right child
    // 若插入值大于当前节点值，则插入右孩子
    else if (value > p->value)
    {
        // If the right child is empty, create the right child
        // 若右孩子为空则创建右孩子
        if (p->rchild == nullptr)
        {
            p->rchild = new binaryTree(value);
            // Mark as binary sort tree
            // 标记为二叉排序树
            p->rchild->BinarySortTrue();
            // Set the parent node
            // 设置父节点
            p->rchild->parent = p;
            return true;
        }

        // Recursively insert the right child
        // 递归插入右孩子
        p->rchild->treeInsert_sort(value);
    }
    // If the insert value is equal to the current node value, insert failed
    // 若插入值等于当前节点值，则插入失败
    else
    {
        cout << "Insert failed, don't enter the same number." << endl;
        cout << "插入失败，不要输入相同的数字。" << endl;
        return false;
    }

    // Insert failed
    // 插入失败
    return false;
}

// Sort the huffman tree
// 排序哈夫曼树
void binaryTree::sortHuffmanTree(vector<binaryTree *> &trees)
{
    // Sort the huffman tree from small to large
    // 按照从小到大的顺序排序哈夫曼树
    sort(trees.begin(), trees.end(), [](binaryTree *a, binaryTree *b)
         { return a->value < b->value; });
}

// Build a huffman tree by huffman algorithm
// 通过哈夫曼算法创建哈夫曼树
binaryTree *binaryTree::buildHuffmanTree(vector<int> &valueArray)
{
    // Create array to store the huffman tree node
    // 创建数组存取哈夫曼树节点
    vector<binaryTree *> trees;

    // Create the huffman tree node by the value of the array
    // 将数组中的值创建为哈夫曼树节点
    for (int it : valueArray)
    {
        trees.push_back(new binaryTree(it));
    }

    // Get the size of the array
    // 获取数组大小
    int32_t n = trees.size();

    // Create the huffman tree by step by step
    // 逐步构建哈夫曼树
    for (int32_t i = 0; i < n - 1; ++i)
    {
        // Sort the huffman tree node by value
        // 排序哈夫曼树节点大小
        sortHuffmanTree(trees);

        // Create the father node and connect the left and right child
        // 创建父亲节点并连接左右孩子
        trees[i]->parent = new binaryTree(trees[i]->value + trees[i + 1]->value);
        trees[i]->parent->lchild = trees[i];
        trees[i]->parent->rchild = trees[i + 1];

        // Add the father node to the array
        // 将父亲节点加入数组
        trees[i + 1] = trees[i]->parent;
    }

    // Mark as huffman tree
    // 标记哈夫曼树
    trees[n - 1]->HuffmanTrue();

    // Return the huffman tree
    // 返回哈夫曼树
    return trees[n - 1];
}

// Preorder traversal
// 前序遍历
void binaryTree::preorderTraversal()
{
    // Print the value of the current node
    // 输出当前节点的值
    cout << value << " -> ";

    // If the left child is not empty, postorder traversal the left child
    // 若左孩子不为空则前序遍历左孩子
    if (lchild)
        lchild->preorderTraversal();

    // If the right child is not empty, postorder traversal the right child
    // 若右孩子不为空则前序遍历右孩子
    if (rchild)
        rchild->preorderTraversal();
}

// Inorder traversal
// 中序遍历
void binaryTree::inorderTraversal()
{
    // If the left child is not empty, inorder traversal the left child 若左孩子不为空则中序遍历左孩子
    if (lchild)
        lchild->inorderTraversal();

    // Print the value of the current node 输出当前节点的值
    cout << value << " -> ";

    // If the right child is not empty, inorder traversal the right child 若右孩子不为空则中序遍历右孩子
    if (rchild)
        rchild->inorderTraversal();
}

// Postorder traversal
// 后序遍历
void binaryTree::postorderTraversal()
{
    // If the left child is not empty, postorder traversal the left child
    // 若左孩子不为空则后序遍历左孩子
    if (lchild)
        lchild->postorderTraversal();

    // If the right child is not empty, postorder traversal the right child
    // 若右孩子不为空则后序遍历右孩子
    if (rchild)
        rchild->postorderTraversal();

    // Print the value of the current node
    // 输出当前节点的值
    cout << value << " -> ";
}

// Level order traversal
// 层序遍历
void binaryTree::levelOrderTraversal()
{
    // Realize the level order traversal by queue
    // 通过队列实现层序遍历
    // Create a queue to store the tree
    // 创建队列存储树
    queue<binaryTree *> treeQueue;

    // Add the root node to the queue
    // 将根节点加入队列
    treeQueue.push(this);

    // When the queue is not empty
    // 当队列非空
    while (!treeQueue.empty())
    {
        // Print the value of the current node
        // 输出当前节点的值
        cout << treeQueue.front()->value << " -> ";

        // If the left child is not empty, add it to the queue
        // 若左孩子不为空，则将其加入队列
        if (treeQueue.front()->lchild)
            treeQueue.emplace(treeQueue.front()->lchild);

        // If the right child is not empty, add it to the queue
        // 若右孩子不为空，则将其加入队列
        if (treeQueue.front()->rchild)
            treeQueue.emplace(treeQueue.front()->rchild);

        // The front node out of the queue
        // 队列首节点出列
        treeQueue.pop();
    }
}

// Find the max deepth of the tree
// 寻找树的最大深度
int32_t binaryTree::findMaxDeepth()
{
    // If the tree is empty, return 0
    // 若树为空，则返回0
    if (!this)
    {
        return 0;
    }
    // Recursively find the max deepth
    // 递归寻找最大深度
    // If the left and right child are both empty, return 1, otherwise return the sum of the max deepth of the left and right child plus 1
    // 若左右孩子均为空，则返回1，否则返回左右孩子的最大深度之和加1
    return 1 + max(this->lchild ? this->lchild->findMaxDeepth() : 0, this->rchild ? this->rchild->findMaxDeepth() : 0);
}

// Let the value of the node be a string and fill the array
// 将节点值转化为字符串并填充数组
void binaryTree::fillMapWithXandY(vector<vector<string>> &treeMap, binaryTree *p, int32_t x, int32_t y)
{
    // Let the value of the node be a string and fill the array
    // 将节点值转化为字符串并填充数组
    treeMap[x][y] = to_string(p->value);

    // If the left child is not empty, fill ↙
    // 若左孩子不为空，则填充↙
    if (p->lchild)
    {
        treeMap[x + 1][y - 1] = "↙";
    }
    // If the right child is not empty, fill ↘
    // 若右孩子不为空，则填充↘
    if (p->rchild)
    {
        treeMap[x + 1][y + 1] = "↘";
    }
}

// Using coordinates to draw the tree
// 利用坐标绘制树
void binaryTree::drawTheTree()
{
    // If the tree is empty, output the prompt
    // 如果树为空，则输出提示
    if (!this)
    {
        cout << "The tree is empty. 该树为空。" << endl;
        return;
    }

    // Get the max deepth of the tree
    // 获取树的最大深度
    int32_t maxDeepth = this->findMaxDeepth();

    // Create a two-dimensional array to print the tree
    // 创建二维数组存储树图
    // n is the number of rows, m is the number of columns
    // n为行数，m为列数
    int32_t n = maxDeepth * 2 - 1;
    int32_t m = (maxDeepth > 1) ? (3 * pow(2, maxDeepth - 1) - 1) : 1;

    // Initialize the coordinates of the root node
    // 初始化根节点的坐标
    this->x = 0;
    this->y = m / 2;

    // Initialize the array
    // 初始化数组
    vector<vector<string>> treeMap(n, vector<string>(m, ""));

    // Create a queue to store the tree
    // 创建队列存储树
    queue<binaryTree *> treeQueue;
    treeQueue.push(this);

    // Set the offset
    // 设置偏移量
    int32_t offset = m / 4;

    // Set the current floor
    // 设置当前层数
    int32_t floorNow = 0;

    // While the queue is not empty
    // 当队列非空
    while (!treeQueue.empty())
    {
        // Set the children into the queue and set the coordinates of the children
        // 将孩子节点加入队列并设置孩子节点的坐标

        // If the left child is not empty, add it to the queue
        // 若左孩子不为空，则将其加入队列
        if (treeQueue.front()->lchild)
        {
            treeQueue.emplace(treeQueue.front()->lchild);

            // Set the coordinates of the left child
            // 设置左孩子的坐标
            treeQueue.front()->lchild->x = treeQueue.front()->x + 2;
            treeQueue.front()->lchild->y = treeQueue.front()->y - offset;
        }
        // If the right child is not empty, add it to the queue
        // 若右孩子不为空，则将其加入队列
        if (treeQueue.front()->rchild)
        {
            treeQueue.emplace(treeQueue.front()->rchild);

            // Set the coordinates of the right child
            // 设置右孩子的坐标
            treeQueue.front()->rchild->x = treeQueue.front()->x + 2;
            treeQueue.front()->rchild->y = treeQueue.front()->y + offset;
        }

        // Fill the array with the coordinates of the nodes
        // 利用节点的坐标填充数组
        treeQueue.front()->fillMapWithXandY(treeMap, treeQueue.front(), treeQueue.front()->x, treeQueue.front()->y);

        // The front node out of the queue
        // 队列首节点出列
        treeQueue.pop();

        // Judge the current floor and reduce the offset according to the current floor
        // 根据当前层数降低偏移量
        // When the queue is not empty and the depth of the node is not equal to the recorded depth
        // (the maximum depth minus the maximum depth of the first node in the queue is greater than the current floor)
        // 判断当前层数并依据当前层数降低偏移量
        // 当队列非空且节点深度与记录深度不符(最大深度减去队列首节点的最大深度大于当前层数)时
        if (!treeQueue.empty() && maxDeepth - treeQueue.front()->findMaxDeepth() > floorNow)
        {
            // Set the current floor
            // 设置当前层数
            floorNow = maxDeepth - treeQueue.front()->findMaxDeepth();

            // Reduce the offset
            // 降低偏移量
            offset /= 2;
        }
    }

    // Output the picture of the tree
    // 输出树图
    for (const auto &row : treeMap)
    {
        for (const auto &cell : row)
        {
            // Output the value of the array
            // 输出数组的值
            cout << left << setw(1) << setfill(' ') << cell;
        }
        cout << endl;
    }
}

// Find the WPL of the tree
// 寻找树的WPL
int32_t binaryTree::findWPL(binaryTree *p, int32_t length)
{
    // If left and right child are both not empty, return the sum of the WPL of the left and right child
    // 若左右孩子均不为空，则返回左右孩子的WPL之和
    if (p->lchild && p->rchild)
    {
        return findWPL(p->lchild, length + 1) + findWPL(p->rchild, length + 1);
    }
    // If left and right child are have at least one empty node (the current node is a leaf node),
    // return the value of the current node multiplied by the length
    // 若左右孩子至少有一个空节点(当前节点为叶子节点)，则返回当前节点的值乘以长度
    else if (p->lchild || p->rchild)
    {
        binaryTree *child = p->lchild ? p->lchild : p->rchild;
        return p->value * length + findWPL(child, length + 1);
    }
    // If left and right child are both empty, return the value of the current node multiplied by the length
    // 若左右孩子均为空，则返回当前节点的值乘以长度
    return p->value * length;
}

// Delete a node from the binary sort tree
// 从二叉排序树中删除节点
binaryTree *binaryTree::deleteNode_sortedTree(int32_t value)
{
    // Create p pointer to the current node
    // 创建p指针指向当前节点
    binaryTree *p = this;

    // If the tree is empty, output the prompt
    // 若树为空，则输出提示
    if (!p)
    {
        cout << "The tree is empty. 该树为空。" << endl;
        return p;
    }

    // Find the node to be deleted
    // 寻找要删除的节点
    while (p->value != value)
    {
        if (p->value > value)
        {
            p = p->lchild;
        }
        else
        {
            p = p->rchild;
        }
    }

    // If p has no child
    // 若p没有孩子
    if (!p->lchild && !p->rchild)
    {
        // If p is the root node then delete the root node
        // 若p为根节点则删除根节点
        if (!p->parent)
        {
            delete p;
            return nullptr;
        }
        // If p is the left child, set the left child of the parent node to empty
        // 若p是左孩子，则将其父节点的左孩子置空
        if (p->parent->lchild == p)
        {
            p->parent->lchild = nullptr;
        }
        // If p is the right child, set the right child of the parent node to empty
        // 若p是右孩子，则将其父节点的右孩子置空
        else
        {
            p->parent->rchild = nullptr;
        }

        // Free memory
        // 释放内存
        delete p;
        return this;
    }
    // If p only has a child
    // 如果p只有一个孩子
    else if ((p->lchild || p->rchild) && !(p->lchild && p->rchild))
    {
        // If p is the root node
        // 若p为根节点
        if (!p->parent)
        {
            if (p->lchild)
            {
                // Set the left child as the root node
                // 将左孩子设为根节点
                p = p->lchild;
                // Free memory
                // 释放内存
                delete p->parent;
                // Set the parent node as empty
                // 将父节点置空
                p->parent = nullptr;
            }
            else
            {
                // Set the right child as the root node
                // 将右孩子设为根节点
                p = p->rchild;
                // Free memory
                // 释放内存
                delete p->parent;
                // Set the parent node as empty
                // 将父节点置空
                p->parent = nullptr;
            }

            // Return the root node
            // 返回根节点
            return p;
        }

        // If p is the left child, set the left child of the parent node to the child of p
        // 若p是左孩子，则将其父节点的左孩子指向p的孩子
        if (p->parent->lchild == p)
        {
            p->parent->lchild = p->lchild ? p->lchild : p->rchild;
        }
        // If p is the right child, set the right child of the parent node to the child of p
        // 若p是右孩子，则将其父节点的右孩子指向p的孩子
        else
        {
            p->parent->rchild = p->lchild ? p->lchild : p->rchild;
        }

        p->lchild ? p->lchild->parent = p->parent : p->rchild->parent = p->parent;

        // free memory
        // 释放内存
        delete p;

        return this;
    }
    // If p has two children
    // 若p有两个孩子
    else
    {
        // Find the minimum value of the right child of p
        // 寻找p的右孩子的最小值
        binaryTree *minValue = p->rchild;
        while (minValue && minValue->lchild)
        {
            minValue = minValue->lchild;
        }

        // Set the value of p as the minimum value of the right child of p
        // 将p的值设为p的右孩子的最小值
        p->value = minValue->value;
        // Delete the minimum value of the right child of p
        // 删除p的右孩子的最小值
        if (minValue->parent->lchild == minValue)
        {
            minValue->parent->lchild = minValue->rchild;
        }
        else
        {
            if (minValue->rchild)
            {
                minValue->rchild->parent = minValue->parent;
            }
            minValue->parent->rchild = minValue->rchild;
        }
        delete minValue;

        return this;
    }
}

// Get the height of the node
// 获取节点的高度
int32_t binaryTree::getHeight(binaryTree *p)
{
    return p == nullptr ? -1 : p->height;
}

// Update the height of the node
// 更新节点的高度
void binaryTree::updateHeight(binaryTree *p)
{
    p->height = max(getHeight(p->lchild), getHeight(p->rchild)) + 1;
}

// Get the balance factor of the node
// 获取节点的平衡因子
int32_t binaryTree::getBalanceFactor(binaryTree *p)
{
    return p == nullptr ? 0 : getHeight(p->lchild) - getHeight(p->rchild);
}

// Right rotation
// 右旋
binaryTree *binaryTree::rightRotation(binaryTree *p)
{
    // Create a pointer to the left child of the current node
    // 创建指向当前节点左孩子的指针
    binaryTree *lchild = p->lchild;

    // Set the left child of the current node as the right child of the left child of the current node
    // 将当前节点的左孩子的右孩子设为当前节点的左孩子
    p->lchild = lchild->rchild;
    lchild->parent = p->parent;
    p->parent = lchild;
    if (p->lchild)
    {
        p->lchild->parent = p;
    }

    // Set the right child of the left child of the current node as the current node
    // 将当前节点的左孩子设为当前节点的左孩子的右孩子
    lchild->rchild = p;

    // Update the height of the current node
    // 更新当前节点的高度
    updateHeight(p);

    // Update the height of the left child of the current node
    // 更新当前节点的左孩子的高度
    updateHeight(lchild);

    // Return the left child of the current node
    // 返回当前节点的左孩子
    return lchild;
}

// Left rotation
// 左旋
binaryTree *binaryTree::leftRotation(binaryTree *p)
{
    // Create a pointer to the right child of the current node
    // 创建指向当前节点右孩子的指针
    binaryTree *rchild = p->rchild;

    // Set the right child of the current node as the left child of the right child of the current node
    // 将当前节点的右孩子的左孩子设为当前节点的右孩子
    p->rchild = rchild->lchild;
    rchild->parent = p->parent;
    p->parent = rchild;
    if (p->rchild)
    {
        p->rchild->parent = p;
    }

    // Set the left child of the right child of the current node as the current node
    // 将当前节点的右孩子设为当前节点的右孩子的左孩子
    rchild->lchild = p;

    // Update the height of the current node
    // 更新当前节点的高度
    updateHeight(p);

    // Update the height of the right child of the current node
    // 更新当前节点的右孩子的高度
    updateHeight(rchild);

    // Return the right child of the current node
    // 返回当前节点的右孩子
    return rchild;
}

// Rotate the tree
// 旋转树
binaryTree *binaryTree::rotate(binaryTree *p)
{
    // Update the height of the current node
    // 更新当前节点的高度
    updateHeight(p);

    // Get the balance factor of the current node
    // 获取当前节点的平衡因子
    int32_t balanceFactor = getBalanceFactor(p);

    // If the balance factor is greater than 1
    // 若平衡因子大于1 - 左偏树
    if (balanceFactor > 1)
    {
        // If the balance factor of the left child of the current node is greater than 0
        // 若当前节点的左孩子的平衡因子大于0
        if (getBalanceFactor(p->lchild) > 0)
        {
            // Right rotation
            // 右旋
            return rightRotation(p);
        }
        // If the balance factor of the left child of the current node is less than 0
        // 若当前节点的左孩子的平衡因子小于0
        else
        {
            // Left rotation
            // 左旋
            p->lchild = leftRotation(p->lchild);
            // Right rotation
            // 右旋
            return rightRotation(p);
        }
    }
    // If the balance factor is less than -1
    // 若平衡因子小于-1 - 右偏树
    else if (balanceFactor < -1)
    {
        // If the balance factor of the right child of the current node is less than 0
        // 若当前节点的右孩子的平衡因子小于0
        if (getBalanceFactor(p->rchild) <= 0)
        {
            // Left rotation
            // 左旋
            return leftRotation(p);
        }
        // If the balance factor of the right child of the current node is greater than 0
        // 若当前节点的右孩子的平衡因子大于0
        else
        {
            // Right rotation
            // 右旋
            p->rchild = rightRotation(p->rchild);
            // Left rotation
            // 左旋
            return leftRotation(p);
        }
    }

    // Return the current node
    // 返回当前节点
    return p;
}

// Insert a node to the AVL tree
// 向AVL树中插入节点
binaryTree *binaryTree::treeInsert_AVL(binaryTree *p, int32_t value)
{
    // If the current node is empty, create the current node
    // 若当前节点为空，则创建当前节点
    if (!p)
    {
        return new binaryTree(value);
    }

    // If the insert value is less than the value of the current node, insert the left child
    // 若插入值小于当前节点的值，则插入左孩子
    if (value < p->value)
    {
        p->lchild = treeInsert_AVL(p->lchild, value);
        p->lchild->parent = p;
    }
    // If the insert value is greater than the value of the current node, insert the right child
    // 若插入值大于当前节点的值，则插入右孩子
    else if (value > p->value)
    {
        p->rchild = treeInsert_AVL(p->rchild, value);
        p->rchild->parent = p;
    }

    // Rotate the tree
    // 旋转树
    return rotate(p);
}

// Delete a node from the AVL tree
// 从AVL树中删除节点
binaryTree *binaryTree::deleteNode_AVL(binaryTree *p, int32_t value)
{
    p = p->deleteNode_sortedTree(value);
    return p ? rotate(p) : p;
}
