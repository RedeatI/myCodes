#include "binaryTree.h"
#include "binaryTree.cpp"
#include <iostream>
using namespace std;

int main()
{
    // Set the console to UTF-8
    system("chcp 65001");
    
    // When user don't end the program, the program will continue to run.
    // 当用户不结束程序时，程序将继续运行。
    while (true)
    {

        // Select a tree to build.
        // 选择要创建的树。
        firstAsk();

        int16_t sel;
        cin >> sel;

        // Ask the user to enter the numbers to build the tree.
        // 请用户输入要创建树的节点值。
        cout << "Please enter the numbers to build the tree.(0 to stop)" << endl;
        cout << "请输入要创建树的节点值。(输入0停止)" << endl;

        // Create a tree.
        // 创建树。
        binaryTree *tree = nullptr;
        vector<int> valueArray;

        // Clear the array
        // 清空数组
        valueArray.resize(0);

        /*
       1 : binary sort tree(二叉排序树)
       2 : huffman tree(哈夫曼树)
       3 : heap(筛选法)
       4 : heap(插入法)
       5 : AVL tree(AVL树)
       */

        // Select a tree to build.
        // 选择要创建的树。
        switch (sel)
        {

            // Create a binary sort tree.
            // 创建二叉排序树。
        case 1:
            tree = new binaryTree();
            // Insert Node
            // 插入节点
            while (true)
            {
                int32_t value;
                cin >> value;

                // 0 to stop
                // 输入0停止
                if (value)
                {
                    valueArray.push_back(value);
                    tree->treeInsert_sort(value);
                }
                else
                {
                    break;
                }
            }
            break;

            // Create a huffman tree.
            // 创建哈夫曼树。
        case 2:
            while (true)
            {
                int32_t value;
                cin >> value;

                // 0 to stop
                // 输入0停止
                // Insert the node to the array
                // 插入节点至数组
                if (value)
                {
                    valueArray.push_back(value);
                }
                // Build the huffman tree 建立哈夫曼树
                else
                {
                    tree = tree->buildHuffmanTree(valueArray);
                    break;
                }
            }
            break;

            // Create a heap(Sift)
            // 创建堆(筛选法)
        case 3:
            while (true)
            {
                int32_t value;
                cin >> value;

                // 0 to stop
                // 输入0停止
                // Save the value to the array
                // 保存节点值至数组
                if (value)
                    valueArray.push_back(value);
                // Build the heap(Sift)
                // 建立堆(筛选法)
                else
                {
                    tree = buildHeapBySift(valueArray);
                    break;
                }
            }
            break;

            // Create a heap(Insert)
            // 建立堆(插入法)
        case 4:
            while (true)
            {
                int32_t value;
                cin >> value;

                // 0 to stop
                // 输入0停止
                // Save the value to the array
                // 保存节点值至数组
                if (value)
                    heapInsert(valueArray, value);
                // Build the heap(Insert)
                // 建立堆(插入法)
                else
                {
                    tree = buildHeapByArray(valueArray);
                    break;
                }
            }
            break;

            // Create AVL tree
            // 创建AVL树
        case 5:
            while (true)
            {
                int32_t value;
                cin >> value;

                // 0 to stop
                // 输入0停止
                // Insert the node to the AVL tree
                // 插入节点至AVL树
                if (value)
                {
                    valueArray.push_back(value);
                    tree = tree->treeInsert_AVL(tree, value);
                }
                else
                {
                    break;
                }
            }

            break;

            // Exit the program
            // 退出程序
        default:
            // When user haven't select a tree, the program will exit.
            // 当用户没有选择树时，程序将退出。
            return 0;
        }

        /*
        遍历方式：
        前序遍历 (Preorder Traversal)
        中序遍历 (Inorder Traversal)
        后序遍历 (Postorder Traversal)
        层序遍历 (Level Order Traversal)
        */

        showHelps();

        // set loop to judge whether to continue the loop
        // 设置循环以判断是否继续循环
        bool loop = true;

        // while loop is true, continue the loop
        // 当循环为真时，继续循环
        while (loop)
        {
            // If the tree is empty
            // 树为空
            if (!tree)
            {
                cout << "The tree is empty, please rebuild the tree. " << endl;
                cout << "树为空，请重新创建树。" << endl
                     << endl;

                // Close the loop
                // 关闭循环
                loop = false;
                break;
            }

            cout << endl;
            cin >> sel;

            // Select the traversal method
            // 选择遍历方式
            switch (sel)
            {
                // rebuild the tree
                // 重新创建树
            case -1:
                // Free the memory
                // 释放内存
                delete tree;

                // Close the loop
                // 关闭循环
                loop = false;
                break;

                // exit the program
                // 退出程序
            case 0:
                return 0;

                // Preorder Traversal
                // 前序遍历
            case 1:
                cout << "Preorder Traversal(前序遍历):" << endl;
                tree->preorderTraversal();
                break;

                // Inorder Traversal
                // 中序遍历
            case 2:
                cout << "Inorder Traversal(中序遍历):" << endl;
                tree->inorderTraversal();
                break;

                // Postorder Traversal
                // 后序遍历
            case 3:
                cout << "Postorder Traversal(后序遍历):" << endl;
                tree->postorderTraversal();
                break;

                // Level Order Traversal
                // 层序遍历
            case 4:
                cout << "Level Order Traversal(层序遍历):" << endl;
                tree->levelOrderTraversal();
                break;

                // Draw the tree
                // 绘制树
            case 5:
                cout << "Draw of the tree(树的图像):" << endl;
                tree->drawTheTree();
                cout << endl;
                cout << "Tree's max deepth(树的最大深度): " << tree->findMaxDeepth() << endl;
                if (tree && tree->isHuffman())
                {
                    cout << "Tree's WPL(树的带权路径长度): " << tree->findWPL(tree, 0) << endl;
                }
                break;

                // Insert a node into the tree
                // 插入节点
            case 10:

                cout << "Please enter the numbers to insert the tree.(0 to stop)" << endl;
                cout << "请输入要插入的节点值。(输入0停止)" << endl;
                while (true)
                {
                    int32_t value;
                    cin >> value;

                    // Input 0 to stop
                    // 输入0停止
                    if (value == 0)
                    {
                        break;
                    }
                    else if (tree->isBinarySort())
                    {
                        valueArray.push_back(value);
                        tree->treeInsert_sort(value);
                    }
                    else if (tree->isHuffman())
                    {
                        valueArray.push_back(value);
                        // Rebuild the huffman tree
                        // 重新构建哈夫曼树
                        tree = tree->buildHuffmanTree(valueArray);
                    }
                    else if (tree->isHeap())
                    {
                        heapInsert(valueArray, value);
                        // Rebuild the heap
                        // 重新构建堆
                        tree = buildHeapByArray(valueArray);
                    }
                    else if (tree->isAVL())
                    {
                        heapInsert(valueArray, value);
                        tree = tree->treeInsert_AVL(tree, value);
                    }
                }
                cout << "Insert completed. 插入完成。" << endl;
                break;

                // Delete a node from the tree
                // 删除节点
            case 11:
                cout << "Please enter the numbers to delete the tree.(0 to stop)" << endl;
                cout << "请输入要删除的节点值。(输入0停止)" << endl;
                while (true)
                {
                    int32_t value;
                    cin >> value;

                    // Input 0 to stop
                    // 输入0停止
                    if (value == 0)
                    {
                        break;
                    }
                    else if (valueArray.size() == 0)
                    {
                        cout << "The tree is Empty. 该树为空。" << endl;
                    }
                    else if (tree->isBinarySort())
                    {
                        // If the node hasn't been found
                        // 如果未找到节点
                        if (find(valueArray.begin(), valueArray.end(), value) == valueArray.end())
                        {
                            cout << "The value is not found. 未找到该值的节点。" << endl;
                        }
                        else
                        {
                            valueArray.erase(find(valueArray.begin(), valueArray.end(), value));
                            tree = tree->deleteNode_sortedTree(value);
                        }
                    }
                    else if (tree->isHuffman())
                    {
                        // If the node hasn't been found
                        // 如果未找到节点
                        if (find(valueArray.begin(), valueArray.end(), value) == valueArray.end())
                        {
                            cout << "The value is not found. 未找到该值的节点。" << endl;
                        }
                        else
                        {
                            valueArray.erase(find(valueArray.begin(), valueArray.end(), value));
                            // Rebuild the huffman tree
                            // 重新构建哈夫曼树
                            tree = tree->buildHuffmanTree(valueArray);
                        }
                    }
                    else if (tree->isHeap())
                    {
                        // If the node hasn't been found
                        // 如果未找到节点
                        if (find(valueArray.begin(), valueArray.end(), value) == valueArray.end())
                        {
                            cout << "The value is not found. 未找到该值的节点。" << endl;
                        }
                        else
                        {
                            valueArray.erase(find(valueArray.begin(), valueArray.end(), value));
                            // Rebuild the heap
                            // 重新构建堆
                            tree = buildHeapBySift(valueArray);
                        }
                    }
                    else if (tree->isAVL())
                    {
                        // If the node hasn't been found
                        // 如果未找到节点
                        if (find(valueArray.begin(), valueArray.end(), value) == valueArray.end())
                        {
                            cout << "The value is not found. 未找到该值的节点。" << endl;
                        }
                        else
                        {
                            valueArray.erase(find(valueArray.begin(), valueArray.end(), value));
                            tree = tree->deleteNode_AVL(tree, value);
                        }
                    }
                }
                cout << "Delete completed. 删除完成。" << endl;
                break;

                // Show the helps again
                // 再次显示帮助
            default:
                showHelps();
                break;
            }
        }
    }

    return 0;
}
