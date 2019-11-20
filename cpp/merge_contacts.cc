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
    // TODO: this will override () operator? Study C++ operator
    //   functor https://stackoverflow.com/questions/356950/what-are-c-functors-and-their-uses
    //   https://www.youtube.com/watch?v=qM2kvcSW4_E
    size_t operator()(const ContactList& contacts) const {
        size_t hash_code = 0;
        for (const string& name : unordered_set<string>(contacts.names.begin(),
                contacts.names.end())) {
            // NOTE: why double parentheses? First parentheses is for
            //   object instantiation. Second is to call the
            //   parentheses operator() --> functor.
            //   What happen if remove the first () ? Compile error
            hash_code ^= hash<string>()(name);
        }

        return hash_code;
    }
};

// TODO: explain this function
vector<ContactList> MergeContactLists(const vector<ContactList>& contacts) {
    // TODO: study unordered_set
    //   explain parentheses ctor?
    //   Pass vector.begin/end to unordered_set ?
    unordered_set<ContactList, HashContactList> unique_contacts(
        contacts.begin(), contacts.end());

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
