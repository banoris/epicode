// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_CAN_STRING_BE_PALINDROME_HASH_H_
#define SOLUTIONS_CAN_STRING_BE_PALINDROME_HASH_H_

#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>

using std::string;
using std::unordered_map;

namespace CanStringBeAPalindromeHash {

// @include
bool CanFormPalindrome(const string& s) {
    unordered_map<char, int> char_frequencies;
    // Compute the frequency of each char in s.
    for (char c : s) {
        ++char_frequencies[c];
    }

    // A string can be permuted as a palindrome if and only if the number of
    // chars whose frequencies is odd is at most 1.
    // TODO: how does this counter work?
    int odd_frequency_count = 0;

    // (p.second % 2) --> check whether the character count is event
    // (++odd_frequency_count > 1) --> TODO: magic??
    auto is_palindrome = [&odd_frequency_count](const auto& p) {
        return (p.second % 2) && (++odd_frequency_count > 1);
    };

    // TODO: How does none_of(...) works? Think about Python list comprehension
    //   It is actually Logical NOR https://en.wikipedia.org/wiki/Truth_table#Logical_NOR
    //     Returns true IFF all propositions are false
    //   none_of(iterator_begin, iterator_end, lambda).
    //   'lambda' will be applied to each element
    return none_of(begin(char_frequencies), end(char_frequencies),
        is_palindrome);
}
// @exclude

}  // namespace CanStringBeAPalindromeHash

#endif  // SOLUTIONS_CAN_STRING_BE_PALINDROME_HASH_H_
