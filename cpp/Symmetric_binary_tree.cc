// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "./Binary_tree_prototype.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;

bool CheckSymmetric(const unique_ptr<BinaryTreeNode<int>>&,
                    const unique_ptr<BinaryTreeNode<int>>&);

// @include
bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
    return tree == nullptr || CheckSymmetric(tree->left, tree->right);
}

bool CheckSymmetric(const unique_ptr<BinaryTreeNode<int>>& subtree_0,
                    const unique_ptr<BinaryTreeNode<int>>& subtree_1) {
    /* subtree0  subtree1
          0          0    --> both trees empty
          0          1    --> if one tree is empty and the other is not,
          1          0    -->   then for sure non-symmetric, return false
          1          1    --> both trees available. Compare data for both
    */

    // both subtrees is empty i.e. NULL
    if (subtree_0 == nullptr && subtree_1 == nullptr) {
        return true;
    }
    // both subtrees not empty
    else if (subtree_0 != nullptr && subtree_1 != nullptr) {
        // NOTE: the meat of the operation.
        //   Can we short-circuit this much earlier?
        if (subtree_0->data != subtree_1->data) {
            return false;
        }

        return CheckSymmetric(subtree_0->left, subtree_1->right) &&
            CheckSymmetric(subtree_0->right, subtree_1->left);

        // NOTE: the meat of the operation.
        //   Can we short-circuit this much earlier?
        // return subtree_0->data == subtree_1->data &&
        //        CheckSymmetric(subtree_0->left, subtree_1->right) &&
        //        CheckSymmetric(subtree_0->right, subtree_1->left);
    }
    // One subtree is empty, and the other is not.
    return false;
}
// @exclude

void SimpleTest() {
    auto symm_tree = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    assert(IsSymmetric(symm_tree));
    symm_tree->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    assert(!IsSymmetric(symm_tree));
    symm_tree->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    assert(IsSymmetric(symm_tree));
    symm_tree->right->right =
        make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    assert(!IsSymmetric(symm_tree));
}

int main(int argc, char* argv[]) {
    SimpleTest();
    // Non symmetric tree test.
    //      x
    //    x   x
    //  x    x x
    auto non_symm_tree =
        make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    non_symm_tree->left =
        make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    non_symm_tree->left->left =
        make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    non_symm_tree->right =
        make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    non_symm_tree->right->left =
        make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    non_symm_tree->right->right =
        make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    assert(!IsSymmetric(non_symm_tree));
    cout << boolalpha << IsSymmetric(non_symm_tree) << endl;
    // Symmetric tree test.
    unique_ptr<BinaryTreeNode<int>> symm_tree =
                                     make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    symm_tree->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    symm_tree->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
    assert(IsSymmetric(symm_tree) == true);
    cout << boolalpha << IsSymmetric(symm_tree) << endl;
    // Empty tree test.
    symm_tree = nullptr;
    assert(IsSymmetric(symm_tree) == true);
    cout << boolalpha << IsSymmetric(symm_tree) << endl;
    return 0;
}
