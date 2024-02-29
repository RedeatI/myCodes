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
                int32_t value;
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
