// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

#include "./BST_prototype.h"

using std::cout;
using std::endl;
using std::make_unique;
using std::stack;
using std::unique_ptr;
using std::vector;

// @include
vector<int> BSTInSortedOrder(const unique_ptr<BSTNode<int>>& tree) {
    stack<const BSTNode<int>*> _stack;
    // TODO: unique_ptr with cursor technique
    //   https://stackoverflow.com/questions/25370628/doesnt-get-break-the-idea-behind-stdunique-ptr
    //   https://stackoverflow.com/questions/10802046/whats-the-point-of-stdunique-ptrget
    const auto* curr = tree.get();
    vector<int> result;

    // TODO: terminating logic for while
    while (!_stack.empty() || curr) {
        if (curr) {
            _stack.push(curr);
            // Going left.
            curr = curr->left.get();
        } else {
            // Going up.
            curr = _stack.top();
            _stack.pop();
            result.emplace_back(curr->data);
            // Going right.
            curr = curr->right.get();
        }
    }
    return result;
}
// @exclude

void SimpleTest() {
    unique_ptr<BSTNode<int>> tree =
                              make_unique<BSTNode<int>>(BSTNode<int> {43, nullptr});
    auto result = BSTInSortedOrder(tree);
    vector<int> golden_result = {43};
    assert(equal(golden_result.begin(), golden_result.end(), result.begin(),
                 result.end()));
    tree->left = make_unique<BSTNode<int>>(BSTNode<int> {23, nullptr});
    result = BSTInSortedOrder(tree);
    golden_result = {23, 43};
    assert(equal(golden_result.begin(), golden_result.end(), result.begin(),
                 result.end()));
}

int main(int argc, char* argv[]) {
    SimpleTest();
    //        43
    //    23     47
    //      37      53
    //    29  41
    //     31
    unique_ptr<BSTNode<int>> tree =
                              make_unique<BSTNode<int>>(BSTNode<int> {43, nullptr});
    tree->left = make_unique<BSTNode<int>>(BSTNode<int> {23, nullptr});
    tree->left->right = make_unique<BSTNode<int>>(BSTNode<int> {37, nullptr});
    tree->left->right->left =
        make_unique<BSTNode<int>>(BSTNode<int> {29, nullptr});
    tree->left->right->left->right =
        make_unique<BSTNode<int>>(BSTNode<int> {31, nullptr});
    tree->left->right->right =
        make_unique<BSTNode<int>>(BSTNode<int> {41, nullptr});
    tree->right = make_unique<BSTNode<int>>(BSTNode<int> {47, nullptr});
    tree->right->right = make_unique<BSTNode<int>>(BSTNode<int> {53, nullptr});
    auto result = BSTInSortedOrder(tree);
    vector<int> golden_res = {23, 29, 31, 37, 41, 43, 47, 53};
    assert(equal(golden_res.begin(), golden_res.end(), result.begin(),
                 result.end()));
    return 0;
}
