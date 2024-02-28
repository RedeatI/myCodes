#include <bits/stdc++.h>
using namespace std;

// 二叉树节点类
/**
 * @brief 二叉树类
 */
class binaryTree
{
private:
    // 二叉树节点的值
    int value = 0;
    int x;
    int y;
    bool isHuffmanTree = false;

public:
    // 二叉树节点,创建左右孩子以及父亲指针
    binaryTree *lchild, *rchild, *father;

    // 默认构造函数
    binaryTree() : lchild(nullptr), rchild(nullptr), father(nullptr) {}

    /**
     * @brief 构造函数
     * @param value 节点的值
     */
    binaryTree(int value) : value(value), lchild(nullptr), rchild(nullptr), father(nullptr) {}

    /**
     * @brief 判断是否为哈夫曼树
     * @return 如果是哈夫曼树返回true，否则返回false
     */
    bool isHuffman()
    {
        return this->isHuffmanTree;
    }

    /**
     * @brief 根据方法一创建树
     * @param value 节点的值
     * @return 如果创建成功返回true，否则返回false
     */
    bool treeInsert_normal(int value)
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

    /**
     * @brief 对哈夫曼树节点进行排序
     * @param trees 哈夫曼树节点的数组
     */
    void sortHuffmanTree(vector<binaryTree *> &trees)
    {
        // 对哈夫曼树节点进行排序
        sort(trees.begin(), trees.end(), [](binaryTree *a, binaryTree *b)
             { return a->value < b->value; });
    }

    /**
     * @brief 建立并返回哈夫曼树
     * @param trees 哈夫曼树节点的数组
     * @return 哈夫曼树的根节点
     */
    binaryTree *buildHuffmanTree(vector<binaryTree *> &trees)
    {
        int n = trees.size();

        // 逐步构建哈夫曼树
        for (int i = 0; i < n - 1; ++i)
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

    /**
     * @brief 前序遍历
     */
    void preorderTraversal()
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

    /**
     * @brief 中序遍历
     */
    void inorderTraversal()
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

    /**
     * @brief 后序遍历
     */
    void postorderTraversal()
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

    /**
     * @brief 层序遍历
     */
    void levelOrderTraversal()
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

    /**
     * @brief 寻找该树最大深度
     * @return 树的最大深度
     */
    int findMaxDeepth()
    {
        // 递归寻找最大深度
        // 若左右孩子均为空，则返回1，否则返回左右孩子的最大深度之和加1
        return 1 + max(this->lchild ? this->lchild->findMaxDeepth() : 0, this->rchild ? this->rchild->findMaxDeepth() : 0);
    }

    /**
     * @brief 利用坐标绘制树
     * @param treeMap 树状图数组
     * @param tree 当前节点
     * @param x 当前节点的行坐标
     * @param y 当前节点的列坐标
     */
    void fillMapWithXandY(vector<vector<string>> &treeMap, binaryTree *tree, int x, int y)
    {
        // 将节点值转化为字符串并填充数组
        treeMap[x][y] = to_string(tree->value);

        // 若左孩子不为空，则填充↙
        if (tree->lchild)
        {
            treeMap[x + 1][y - 1] = "↙";
        }
        // 若右孩子不为空，则填充↘
        if (tree->rchild)
        {
            treeMap[x + 1][y + 1] = "↘";
        }
    }

    /**
     * @brief 利用层序遍历绘制树
     */
    void drawTheTree()
    {
        // 获取树的最大深度
        int maxDeepth = this->findMaxDeepth();

        // 创建树状图数组
        // n为行数，m为列数
        int n = maxDeepth * 2 - 1;
        int m = (maxDeepth > 1) ? (3 * pow(2, maxDeepth - 1) - 1) : 1;

        // 设置根节点的坐标
        this->x = 0;
        this->y = m / 2;

        // 初始化数组
        vector<vector<string>> treeMap(n, vector<string>(m, ""));

        // 队列实现层序遍历
        queue<binaryTree *> treeQueue;
        treeQueue.push(this);

        // 设置偏移量
        int offset = m / 4;

        // 记录当前层数
        int floorNow = 0;

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

    /**
     * @brief 求哈夫曼树的WPL
     * @param p 当前节点
     * @param length 当前节点到根节点的路径长度
     * @return 哈夫曼树的WPL
     */
    int findWPL(binaryTree *p, int length)
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
};

int main()
{
    // 当用户不主动退出则持续循环程序
    while (true)
    {

        // Select a tree to build.
        cout << "Select a tree that what you want to create." << endl;
        cout << "1 : binary tree" << endl;
        cout << "2 : huffman tree" << endl;
        cout << "3 : binary sort tree" << endl;
        cout << "4 : heap" << endl
             << endl;

        int16_t sel;
        cin >> sel;

        /*
        1 : binary tree(Place the smaller number on the left, bigger number on the right)
        2 : huffman tree
        3 : binary sort tree
        4 : heap
        */

        // 输入提示
        cout << "Please enter the numbers to build the tree.(0 to stop)" << endl;

        // 创建树
        binaryTree *tree;
        vector<binaryTree *> trees;

        // 选择创建树的方式
        switch (sel)
        {

        // Create a binary tree
        case 1:
            tree = new binaryTree();
            // 插入节点
            while (true)
            {
                int value;
                cin >> value;

                // 输入0则停止插入
                if (value)
                    tree->treeInsert_normal(value);
                else
                    break;
            }
            break;

        // Create a huffman tree
        case 2:
            // 保存树节点至数组
            while (true)
            {
                int value;
                cin >> value;

                // 插入树节点至数组
                if (value)
                    trees.push_back(new binaryTree(value));

                // 若输入0则停止插入,并创建哈夫曼树
                else
                {
                    tree = tree->buildHuffmanTree(trees);
                    break;
                }
            }
            break;

        // Create a binary sort tree
        case 3:
            break;

        // Create a heap
        case 4:
            break;

        // Exit the program
        default:
            return 0;
        }

        /*
        遍历方式：
        前序遍历 (Preorder Traversal)
        中序遍历 (Inorder Traversal)
        后序遍历 (Postorder Traversal)
        层序遍历 (Level Order Traversal)
        */

        // 选择遍历方式
        cout << endl;
        cout << "Choose a way to traverse your tree" << endl
             << endl;
        cout << "1 : Preorder Traversal" << endl;
        cout << "2 : Inorder Traversal" << endl;
        cout << "3 : Postorder Traversal" << endl;
        cout << "4 : Level Order Traversal" << endl
             << endl;

        // 其他选项
        cout << "Others:" << endl;
        cout << "5 : Draw the tree" << endl;
        cout << "-1 : Rebuild the tree" << endl;
        cout << "0 : exit the program" << endl;
        cout << "other number : show the helps again" << endl;

        // set loop to judge whether to continue
        bool loop = true;

        // while loop is true, continue
        while (loop)
        {
            cout << endl;
            cin >> sel;

            // 选择遍历方式
            switch (sel)
            {
            // rebuild the tree
            case -1:
                // 释放原树的内存
                delete tree;

                // 关闭循环
                loop = false;
                break;

            // exit the program
            case 0:
                return 0;

            // Preorder Traversal
            case 1:
                cout << "Preorder Traversal:" << endl;
                tree->preorderTraversal();
                break;

            // Inorder Traversal
            case 2:
                cout << "Inorder Traversal:" << endl;
                tree->inorderTraversal();
                break;

            // Postorder Traversal
            case 3:
                cout << "Postorder Traversal:" << endl;
                tree->postorderTraversal();
                break;

            // Level Order Traversal
            case 4:
                cout << "Level Order Traversal:" << endl;
                tree->levelOrderTraversal();
                break;

            // Draw the tree
            case 5:
                cout << "Draw of the tree:" << endl;
                tree->drawTheTree();
                cout << endl;
                cout << "Tree's max deepth: " << tree->findMaxDeepth() << endl;
                if (tree->isHuffman())
                {
                    cout << "Tree's WPL: " << tree->findWPL(tree, 0) << endl;
                }
                break;

            // show the helps again
            default:
                cout << endl
                     << endl;
                cout << "Choose a way to traverse your tree" << endl;
                cout << "1 : Preorder Traversal" << endl;
                cout << "2 : Inorder Traversal" << endl;
                cout << "3 : Postorder Traversal" << endl;
                cout << "4 : Level Order Traversal" << endl;

                // 其他选项
                cout << "Others:" << endl;
                cout << "5 : Draw the tree" << endl;
                cout << "-1 : Rebuild the tree" << endl;
                cout << "0 : exit the program" << endl;
                cout << "other number : show the helps again" << endl;
                break;
            }
        }
    }

    return 0;
}
