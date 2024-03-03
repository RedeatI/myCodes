#include "binaryTree.h"
#include "binaryTree.cpp"
#include <iostream>
using namespace std;

int main()
{
    // 当用户不主动退出则持续循环程序
    while (true)
    {

        // Select a tree to build.
        cout << "Select a tree that what you want to create." << endl;
        cout << "1 : binary sort tree" << endl;
        cout << "2 : huffman tree" << endl;
        cout << "3 : heap(筛选法)" << endl;
        cout << "4 : heap(插入法)" << endl
             << endl;

        int16_t sel;
        cin >> sel;

        /*
        1 : binary sort tree
        2 : huffman tree
        3 : heap(筛选法)
        4 : heap(插入法)
        */

        // 输入提示
        cout << "Please enter the numbers to build the tree.(0 to stop)" << endl;

        // 创建树
        binaryTree *tree = nullptr;
        vector<binaryTree *> trees;
        vector<int> staticHeap;

        // 选择创建树的方式
        switch (sel)
        {

        // Create a binary sort tree
        case 1:
            tree = new binaryTree();
            // 插入节点
            while (true)
            {
                int32_t value;
                cin >> value;

                // 输入0则停止插入
                if (value)
                    tree->treeInsert_sort(value);
                else
                    break;
            }
            break;

        // Create a huffman tree
        case 2:
            // 保存树节点至数组
            while (true)
            {
                int32_t value;
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

        // Create a heap(筛选法)
        case 3:
            // 保存value至数组
            while (true)
            {
                int32_t value;
                cin >> value;

                // 插入树节点至数组
                if (value)
                    staticHeap.push_back(value);

                // 若输入0则停止插入,并创建堆
                else
                {
                    tree = buildHeapBySift(staticHeap);
                    break;
                }
            }
            break;

        // Create a heap(插入法)
        case 4:
            while (true)
            {
                int32_t value;
                cin >> value;

                // 如果输入0则停止插入
                if (value)
                    heapInsert(staticHeap, value);
                else
                {
                    tree = buildHeapByArray(staticHeap);
                    break;
                }
            }
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
        cout << "10 : 增加节点" << endl;
        cout << "11 : 删除节点" << endl;
        cout << "-1 : Rebuild the tree" << endl;
        cout << "0 : exit the program" << endl
             << endl;
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

            // 增加节点
            case 10:
                cout << "Please enter the numbers to insert the tree.(0 to stop)" << endl;
                while (true)
                {
                    int32_t value;
                    cin >> value;

                    // 输入0则停止插入
                    if (value == 0)
                    {
                        break;
                    }
                    else if (tree->isBinarySort())
                    {
                        tree->treeInsert_sort(value);
                    }
                    else if (tree->isHuffman())
                    {
                        trees.push_back(new binaryTree(value));
                        // 重新构建哈夫曼树
                        tree = tree->buildHuffmanTree(trees);
                    }
                    else if (tree->isHeap())
                    {
                        heapInsert(staticHeap, value);
                        // 重新构建堆
                        tree = buildHeapByArray(staticHeap);
                    }
                }
                break;

            // 删除节点
            case 11:

                break;

            // show the helps again
            default:
                cout << endl
                     << endl;
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
                cout << "10 : 增加节点" << endl;
                cout << "11 : 删除节点" << endl;
                cout << "-1 : Rebuild the tree" << endl;
                cout << "0 : exit the program" << endl
                     << endl;
                cout << "other number : show the helps again" << endl;
                break;
            }
        }
    }

    return 0;
}
