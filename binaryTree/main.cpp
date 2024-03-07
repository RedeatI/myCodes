#include "BinaryTree.h"
#include "BinaryTree.cpp"
#include "AVLTree.cpp"
#include "BSTree.cpp"
#include "Heap.cpp"
#include "HuffmanTree.cpp"
#include "RBTree.cpp"

using namespace std;

void firstAsk();
void showTreeOperate();
void showArray();

template <typename T>
void TreeOperate(T root);

void Run();

void buildBinarySortTree();
void buildHuffmanTree();
void buildHeapBySifting();
void buildHeapByInserting();
void buildAVLTree();
void buildRedBlackTree();

vector<int> valueArray;

int main()
{
    // Set the console to UTF-8
    system("chcp 65001");

    Run();

    return 0;
}

void firstAsk()
{
    cout << "请选择要创建的树：" << '\n';
    cout << "1 : binary sort tree(二叉排序树)" << '\n';
    cout << "2 : huffman tree(哈夫曼树)" << '\n';
    cout << "3 : heap(筛选法)" << '\n';
    cout << "4 : heap(插入法)" << '\n';
    cout << "5 : AVL tree(AVL树)" << '\n';
    cout << "6 : Red-Black tree(红黑树)" << '\n';
    cout << "0 : exit the program(退出程序)" << '\n';
}

void showTreeOperate()
{
    cout << '\n';
    cout << "Choose a way to traverse your tree" << '\n';
    cout << "选择遍历方式：" << '\n';
    cout << "1 : Preorder Traversal(前序遍历)" << '\n';
    cout << "2 : Inorder Traversal(中序遍历)" << '\n';
    cout << "3 : Postorder Traversal(后序遍历)" << '\n';
    cout << "4 : Level Order Traversal(层序遍历)" << '\n'
         << '\n';

    cout << "Others(其他选项):" << '\n';
    cout << "5 : Draw the tree(显示树图)" << '\n';
    cout << "10 : Add node(增加节点)" << '\n';
    cout << "11 : Delete node(删除节点)" << '\n';
    cout << "-1 : Rebuild the tree(重建树)" << '\n';
    cout << "0 : exit the program(退出程序)" << '\n'
         << '\n';
    cout << "other number : show the helps again" << '\n';
    cout << "其他 : 显示帮助" << '\n';
}

void Run()
{
    firstAsk();
    while (true)
    {
        int16_t sel;
        cin >> sel;

        if (sel == 0)
        {
            return;
        }

        cout << "Please enter the numbers to build the tree.(0 to stop)" << '\n';
        cout << "请输入要创建树的节点值。(输入0停止)" << '\n';

        valueArray.clear();

        int32_t value;
        while (cin >> value && value != 0)
        {
            if (find(valueArray.begin(), valueArray.end(), value) != valueArray.end())
            {
                cout << "The value: " << value << " is already in the tree." << '\n';
                continue;
            }
            valueArray.emplace_back(value);
        }

        /*
        1 : binary sort tree(二叉排序树)
        2 : huffman tree(哈夫曼树)
        3 : heap(筛选法)
        4 : heap(插入法)
        5 : AVL tree(AVL树)
        6 : Red-Black tree(红黑树)
        */
        switch (sel)
        {
        case 1:
            buildBinarySortTree();
            break;
        case 2:
            buildHuffmanTree();
            break;
        case 3:
            buildHeapBySifting();
            break;
        case 4:
            buildHeapByInserting();
            break;
        case 5:
            buildAVLTree();
            break;
        case 6:
            buildRedBlackTree();
            break;
        default:
            break;
        }
    }
}

void showArray(vector<int> valueArray)
{
    for (int i = 0; i < valueArray.size(); i++)
    {
        cout << valueArray[i] << " ";
    }
    cout << '\n';
}

void buildBinarySortTree()
{
    BSTree *root = nullptr;
    root = buildTree(root, valueArray);
    TreeOperate(root);
}

void buildHuffmanTree()
{
    HuffmanTree *root = nullptr;
    root = buildTree(root, valueArray);
    TreeOperate(root);
}

void buildHeapBySifting()
{
    Heap *root = nullptr;
    root->buildBySifting(root, valueArray);
    TreeOperate(root);
}

void buildHeapByInserting()
{
    Heap *root = nullptr;
    root->buildHeapByInserting(root);
    TreeOperate(root);
}

void buildAVLTree()
{
    AVLTree *root = nullptr;
    root = buildTree(root, valueArray);
    TreeOperate(root);
}

void buildRedBlackTree()
{
    RBTree *root = nullptr;
    root = buildTree(root, valueArray);
    TreeOperate(root);
}

template <typename T>
void TreeOperate(T root)
{
    showTreeOperate();
    while (true)
    {
        vector<int> temp = {};
        int16_t sel;
        cin >> sel;

        switch (sel)
        {
        case 1:
            cout << "Preorder Traversal(前序遍历):" << '\n';
            preOrderTraversal(temp, root);
            showArray(temp);
            break;
        case 2:
            cout << "Inorder Traversal(中序遍历):" << '\n';
            inOrderTraversal(temp, root);
            showArray(temp);
            break;
        case 3:
            cout << "Postorder Traversal(后序遍历):" << '\n';
            postOrderTraversal(temp, root);
            showArray(temp);
            break;
        case 4:
            cout << "Level Order Traversal(层序遍历):" << '\n';
            levelOrderTraversal(temp, root);
            showArray(temp);
            break;
        case 5:
            cout << "Draw the tree(显示树图):" << '\n';
            drawTheTree(root);
            break;
        case 10:
            cout << "Add node(增加节点) 0 to stop:" << '\n';
            int32_t value;
            while (cin >> value && value != 0)
            {
                if (find(valueArray.begin(), valueArray.end(), value) != valueArray.end())
                {
                    cout << "The value: " << value << " is already in the tree." << '\n';
                    continue;
                }
                root->insert(root, value);
                valueArray.emplace_back(value);
            }
            showTreeOperate();
            break;
        case 11:
            cout << "Delete node(删除节点) 0 to stop:" << '\n';
            int32_t DeleteValue;
            while (cin >> DeleteValue && DeleteValue != 0)
            {
                if (find(valueArray.begin(), valueArray.end(), DeleteValue) == valueArray.end())
                {
                    cout << "The value: " << DeleteValue << " is not in the tree." << '\n';
                    continue;
                }
                root->remove(root, DeleteValue);
                valueArray.erase(find(valueArray.begin(), valueArray.end(), DeleteValue));
            }
            showTreeOperate();
            break;
        case -1:
            cout << "Rebuild the tree(重建树):" << '\n';
            Run();
            break;
        case 0:
            return;
        default:
            showTreeOperate();
            break;
        }
    }
}