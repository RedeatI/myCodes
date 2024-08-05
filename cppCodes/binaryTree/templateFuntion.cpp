#include "templateFuntion.h"

template <typename Value, typename Tree>
void preOrderTraversal(Value& getValues, Tree root)
{
	if (root)
	{
		getValues.emplace_back(root->value);
		preOrderTraversal(getValues, root->left);
		preOrderTraversal(getValues, root->right);
	}
}

template <typename Value, typename Tree>
void inOrderTraversal(Value& getValues, Tree root)
{
	if (root)
	{
		inOrderTraversal(getValues, root->left);
		getValues.emplace_back(root->value);
		inOrderTraversal(getValues, root->right);
	}
}

template <typename Value, typename Tree>
void postOrderTraversal(Value& getValues, Tree root)
{
	if (root)
	{
		postOrderTraversal(getValues, root->left);
		postOrderTraversal(getValues, root->right);
		getValues.emplace_back(root->value);
	}
}

template <typename Value, typename Tree>
void levelOrderTraversal(Value& getValues, Tree root)
{
	std::queue<Tree> q;
	q.push(root);
	while (!q.empty())
	{
		Tree temp = q.front();
		q.pop();
		if (temp)
		{
			getValues.emplace_back(temp->value);
			q.push(temp->left);
			q.push(temp->right);
		}
	}
}

template <typename Tree>
int32_t findMaxDeepth(Tree root)
{
	// If the tree is empty, return 0
	// 若树为空，则返回0
	if (!root)
	{
		return 0;
	}
	// Recursively find the max deepth
	// 递归寻找最大深度
	// If the left and right child are both empty, return 1, otherwise return the sum of the max deepth of the left and right child plus 1
	// 若左右孩子均为空，则返回1，否则返回左右孩子的最大深度之和加1
	return 1 + std::max(root->left ? findMaxDeepth(root->left) : 0, root->right ? findMaxDeepth(root->right) : 0);
}

template <typename Tree>
void fillMapWithXandY(std::vector<std::vector<std::string>>& treeMap, Tree root, int32_t x, int32_t y)
{
	// Let the value of the node be a string and fill the array
	// 将节点值转化为字符串并填充数组
	treeMap[x][y] = std::to_string(root->value);

	// If the left child is not empty, fill ↙
	// 若左孩子不为空，则填充↙
	if (root->left)
	{
		treeMap[x + 1][y - 1] = "↙";
	}
	// If the right child is not empty, fill ↘
	// 若右孩子不为空，则填充↘
	if (root->right)
	{
		treeMap[x + 1][y + 1] = "↘";
	}
}

template <typename Tree>
void drawTheTree(Tree root)
{
	// If the tree is empty, output the prompt
	// 如果树为空，则输出提示
	if (!root)
	{
		std::cout << "The tree is empty. 该树为空。" << std::endl;
		return;
	}

	// Get the max deepth of the tree
	// 获取树的最大深度
	int32_t maxDeepth = findMaxDeepth(root);

	// Create a two-dimensional array to print the tree
	// 创建二维数组存储树图
	// n is the number of rows, m is the number of columns
	// n为行数，m为列数
	int32_t n = maxDeepth * 2 - 1;
	int32_t m = (maxDeepth > 1) ? (3 * pow(2, maxDeepth - 1) - 1) : 1;

	// Initialize the coordinates of the root node
	// 初始化根节点的坐标
	root->x = 0;
	root->y = m / 2;

	// Initialize the array
	// 初始化数组
	std::vector<std::vector<std::string>> treeMap(n, std::vector<std::string>(m, ""));

	// Create a queue to store the tree
	// 创建队列存储树
	std::queue<Tree> treeQueue;
	treeQueue.push(root);

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
		if (treeQueue.front()->left)
		{
			treeQueue.emplace(treeQueue.front()->left);

			// Set the coordinates of the left child
			// 设置左孩子的坐标
			treeQueue.front()->left->x = treeQueue.front()->x + 2;
			treeQueue.front()->left->y = treeQueue.front()->y - offset;
		}
		// If the right child is not empty, add it to the queue
		// 若右孩子不为空，则将其加入队列
		if (treeQueue.front()->right)
		{
			treeQueue.emplace(treeQueue.front()->right);

			// Set the coordinates of the right child
			// 设置右孩子的坐标
			treeQueue.front()->right->x = treeQueue.front()->x + 2;
			treeQueue.front()->right->y = treeQueue.front()->y + offset;
		}

		// Fill the array with the coordinates of the nodes
		// 利用节点的坐标填充数组
		fillMapWithXandY(treeMap, treeQueue.front(), treeQueue.front()->x, treeQueue.front()->y);

		// The front node out of the queue
		// 队列首节点出列
		treeQueue.pop();

		// Judge the current floor and reduce the offset according to the current floor
		// 根据当前层数降低偏移量
		// When the queue is not empty and the depth of the node is not equal to the recorded depth
		// (the maximum depth minus the maximum depth of the first node in the queue is greater than the current floor)
		// 判断当前层数并依据当前层数降低偏移量
		// 当队列非空且节点深度与记录深度不符(最大深度减去队列首节点的最大深度大于当前层数)时
		if (!treeQueue.empty() && maxDeepth - findMaxDeepth(treeQueue.front()) > floorNow)
		{
			// Set the current floor
			// 设置当前层数
			floorNow = maxDeepth - findMaxDeepth(treeQueue.front());

			// Reduce the offset
			// 降低偏移量
			offset /= 2;
		}
	}

	// Output the picture of the tree
	// 输出树图
	for (const auto& row : treeMap)
	{
		for (const auto& cell : row)
		{
			// Output the value of the array
			// 输出数组的值
			std::cout << std::left << std::setw(1) << std::setfill(' ') << cell;
		}
		std::cout << std::endl;
	}
}

template <typename Tree>
void rightRotate(Tree root, Tree x)
{
	Tree y = x->left;
	x->left = y->right;
	if (y->right != nullptr)
	{
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr)
	{
		root = y;
	}
	else if (x == x->parent->right)
	{
		x->parent->right = y;
	}
	else
	{
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

template <typename Tree>
void leftRotate(Tree root, Tree x)
{
	Tree y = x->right;
	x->right = y->left;
	if (y->left != nullptr)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr)
	{
		root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

template <typename Tree>
Tree buildTree(Tree root, const std::vector<int>& valueArray)
{
	for (const auto& value : valueArray)
	{
		root->insert(root, value);
	}
	return root;
}