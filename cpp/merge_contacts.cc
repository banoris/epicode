// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <string>
#include <unordered_set>
#include <vector>

using std::hash;
using std::string;
using std::unordered_set;
using std::vector;

// @include
struct ContactList {
    // TODO; study == operator override
    // Equal function for hash.
    bool operator==(const ContactList& that) const {
        return unordered_set<string>(names.begin(), names.end()) ==
               unordered_set<string>(that.names.begin(), that.names.end());
    }

    vector<string> names;
};

// Hash function for ContactList.
struct HashContactList {
    // TODO: this will override () operator? Study C++ operator, functor
    //   https://stackoverflow.com/questions/356950/what-are-c-functors-and-their-uses
    //   https://www.youtube.com/watch?v=qM2kvcSW4_E
    // The idea is to create that acts like a function. And the functionality differs
    // by how you construct the object. Although in this case, the functionality is
    // the same since no ctor args involved at all in this object. Maybe you can
    // get similar feature using function callback or something. Not really sure
    // how it will look in C++ though ¯\_(ツ)_/¯
    size_t operator()(const ContactList& contacts) const {
        size_t hash_code = 0;
        for (const string& name : unordered_set<string>(contacts.names.begin(),
                contacts.names.end())) {
            // NOTE: why double parentheses? First parentheses is for
            //   object instantiation. Second is to call the
            //   parentheses operator()
            //   What happen if remove the first () ? Compile error
            //   https://stackoverflow.com/questions/40024008/how-to-understand-two-pairs-of-parentheses-in-this-code-fragment
            // Protip: use braces init e.g. hash<string>{}(name)
            hash_code ^= hash<string>()(name);
        }

        return hash_code;
    }
};

vector<ContactList> MergeContactLists(const vector<ContactList>& contacts) {
    // 1. DONE: study unordered_set
    //   explain parentheses ctor?
    //   Pass vector.begin/end to unordered_set ?
    // Like you study in Math, set is unique. I.e., all elements
    // must be unique. The .begin/.end from vector thingy is normal
    // C++ code to create set from vector. Any duplicate elements
    // in the vector is removed when creating the set
    //
    // 2. TODO: What is this unordered_set<something1, something2> ?
    // Google: passing functor as template argument
    //   https://www.cprogramming.com/tutorial/functors-function-objects-in-c++.html
    //   https://www.youtube.com/watch?v=qcuYSqHxqLk kinda long but good demo on functor
    //   https://thispointer.com/using-unordered_set-with-custom-hasher-and-comparision-function/
    //     Refer your custom hasher practice at misc_codes repo
    unordered_set<ContactList, HashContactList> unique_contacts(
        contacts.begin(), contacts.end());

    // Don't get confused with this {...} notation. Note that this function has
    // return type of vector<..>. Braces is initialization is very
    // common in C++, not just for vector
    return {unique_contacts.begin(), unique_contacts.end()};
}
// @exclude

int main(int argc, char* argv[]) {

    // acb is considered duplicate for contact abc
    // How do we check?
    vector<ContactList> contacts = {
        {{"a", "b", "c"}}, {{"a", "c", "b"}}, {{"b", "c", "d"}}
    };

    auto result = MergeContactLists(contacts);
    assert(result.size() == 2);
    return 0;
}
