#pragma once
#include <stdint.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stdint.h>
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <limits.h>

template <typename Value, typename Tree>
void preOrderTraversal(Value& getValues, Tree root);

template <typename Value, typename Tree>
void inOrderTraversal(Value& getValues, Tree root);

template <typename Value, typename Tree>
void postOrderTraversal(Value& getValues, Tree root);

template <typename Value, typename Tree>
void levelOrderTraversal(Value& getValues, Tree root);

template <typename Tree>
int32_t findMaxDeepth(Tree root);

template <typename Tree>
void fillMapWithXandY(std::vector<std::vector<std::string>>& treeMap, Tree root, int32_t x, int32_t y);

template <typename Tree>
void drawTheTree(Tree root);

template <typename Tree>
void rightRotate(Tree root, Tree x);

template <typename Tree>
void leftRotate(Tree root, Tree x);

template <typename Tree>
Tree buildTree(Tree root, const std::vector<int>& valueArray);