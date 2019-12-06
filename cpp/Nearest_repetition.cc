// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::min;
using std::numeric_limits;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::vector;

string RandString(int len) {
    default_random_engine gen((random_device())());
    string ret = "";
    while (len--) {
        uniform_int_distribution<int> dis('a', 'z');
        ret += dis(gen);
    }
    return ret;
}

// @include
int FindNearestRepetition(const vector<string>& paragraph) {
    unordered_map<string, int> word_to_latest_index;
    int nearest_repeated_distance = numeric_limits<int>::max();
    cout << "START algo, sentence: ";
    for (auto word : paragraph){
        cout << word << " ";
    }
    cout << endl;
    /*
    Suppose that the input string is the following:
        "All work and no play makes for no work no fun and no results"
    for i=0, paragraph[i] = "All"
     */
    for (int i = 0; i < paragraph.size(); ++i) {
        // find the next occurence of the word in paragraph[i]
        cout << "Currently at word paragraph[" << i << "] = " << paragraph[i] << endl;
        auto latest_equal_word = word_to_latest_index.find(paragraph[i]);
        if (latest_equal_word != word_to_latest_index.end()) {
            // DONE: latest_equal_word? 'find' in the map for
            //   the word we are currently at, i.e., paragraph[i]
            //
            // DONE: Bug? Isn't it `latest_equal_word->second - i` ?
            //   No, it's correct. 'word_to_latest_index' is a map where key is
            //   a word in a sentence and value is the index (or location) in which
            //   the word recently appears. So if a word repeats, e.g. 'no', then
            //   we will store the index where it is last seen
            nearest_repeated_distance =
                min(nearest_repeated_distance, i - latest_equal_word->second);
            cout << "\tlatest_equal_word->second=" << latest_equal_word->second << endl;
            cout << "\tnearest_repeated_distance=" << nearest_repeated_distance << endl;
        }
        cout << "\tAdd to map: key=" << paragraph[i] << ", value=" << i << endl;
        word_to_latest_index[paragraph[i]] = i;
    }
    cout << "Nearest repeated distance is " << nearest_repeated_distance << endl;
    cout << "=============== DONE ===============" << endl;
    return nearest_repeated_distance;
}
// @exclude

// O(n^2) checking
int CheckAnswer(const vector<string>& s) {
    int nearest_repeated_distance = numeric_limits<int>::max();
    for (int i = 0; i < s.size(); ++i) {
        for (int j = i + 1; j < s.size(); ++j) {
            if (s[i] == s[j]) {
                nearest_repeated_distance = min(nearest_repeated_distance, j - i);
            }
        }
    }
    return nearest_repeated_distance;
}

int main(int argc, char* argv[]) {
    vector<string> A = {"foo",    "bar",    "widget", "foo",
                        "widget", "widget", "adnan"
                       };
    assert(CheckAnswer(A) == FindNearestRepetition(A));
    A = {"foo", "bar", "widget", "foo", "xyz", "widget", "bar", "adnan"};
    assert(CheckAnswer(A) == FindNearestRepetition(A));
    A = {"foo", "bar", "widget", "adnan"};
    assert(CheckAnswer(A) == FindNearestRepetition(A));
    A = {};
    assert(CheckAnswer(A) == FindNearestRepetition(A));
    A = {"foo", "foo", "foo"};
    assert(CheckAnswer(A) == FindNearestRepetition(A));

    vector<string> sentence{"All", "work", "and", "no", "play",
        "makes", "for", "no", "work", "no", "fun",
        "and", "no", "results"
    };

    FindNearestRepetition(sentence);


    // NOTE: this takes super-long time to run
    // default_random_engine gen((random_device())());
    // for (int times = 0; times < 1000; ++times) {
    //     int n;
    //     if (argc == 2) {
    //         n = atoi(argv[1]);
    //     } else {
    //         uniform_int_distribution<int> dis(1, 10000);
    //         n = dis(gen);
    //     }
    //     vector<string> s;
    //     for (int i = 0; i < n; ++i) {
    //         uniform_int_distribution<int> dis(1, 10);
    //         s.emplace_back(RandString(dis(gen)));
    //     }
    //     assert(CheckAnswer(s) == FindNearestRepetition(s));
    // }
    return 0;
}
