// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <numeric>
#include <random>
#include <string>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::uniform_int_distribution;

string RandString(int len) {
    string ret;
    default_random_engine gen((random_device())());
    while (len--) {
        uniform_int_distribution<int> zero_or_one(0, 1);
        uniform_int_distribution<char> dis(0, 26);
        ret += (zero_or_one(gen) ? 'a' : 'A') + dis(gen);
    }
    return ret;
}

// @include
// TODO: modulus is for??
// Again, understand what is a hash function. Given an input key (string 'str' in this case),
// you want to return a hash code that is unique for that particular key.
// So how would you calculate this hash code? What formula you will use?
// What is the requirement for hashing? Unique, distinct, fast?
int StringHash(const string& str, int modulus) {
    // TODO: what's this magic number???
    const int kMult = 997;
    // @exclude
    /*
       return accumulate(str.cbegin(), str.cend(), 0,
       [kMult, modulus](const int &val, const char &c) {
       return (val * kMult + c) % modulus;
       });
       */
    // @include
    int val = 0;
    for (char c : str) {
        val = (val * kMult + c) % modulus;
    }
    return val;
}
// @exclude

int main(int argc, char* argv[]) {
    default_random_engine gen((random_device())());
    string str;
    if (argc == 2) {
        str = argv[1];
    } else {
        uniform_int_distribution<int> dis(1, 20);
        str = RandString(dis(gen));
    }
    cout << "string = " << str << endl;
    cout << "StringHash() = " << StringHash(str, 1 << (16)) << endl;
    return 0;
}
