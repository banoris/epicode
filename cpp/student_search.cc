// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <functional>
#include <string>
#include <vector>
#include <iostream>

using std::binary_search;
using std::function;
using std::sort;
using std::string;
using std::vector;

// @include
struct Student {
    string name;
    double grade_point_average;
};

// CompGPA is a lambda. Don't get scared with the syntax
// It is encapsulated in a function wrapper, std::function
// You can treat 'CompGPA' like a variable. But it is function. Yup, confusing.
// 
const static function<bool(const Student&, const Student&)> CompGPA = [] (
    const Student& a, const Student& b)
{
    // NOTE: dehek? why != implies a > b ?
    //   Ehh wait... You misunderstood (╯°□°）╯︵ ┻━┻)
    //   (a > b) will returns true or false, depending on the value of a and b
    //   Really blur today...
    if (a.grade_point_average != b.grade_point_average) {
        return a.grade_point_average > b.grade_point_average;
    }
    return a.name < b.name;
};

bool SearchStudent(
    const vector<Student>& students, const Student& target,
    const function<bool(const Student&, const Student&)>& comp_GPA)
{
    return binary_search(students.begin(), students.end(), target, comp_GPA);
}
// @exclude

int main(int argc, char* argv[]) {
    vector<Student> students = {
        {"A", 4.0},
        {"C", 3.0},
        {"B", 2.0},
        {"D", 3.2}
    };

    // TODO: understand how sort is used to sort 2d vectors
    sort(students.begin(), students.end(), CompGPA);

    for (int i = 0; i < students.size(); ++i) {
        std::cout << students[i].name;
    }

    assert(SearchStudent(students, {"A", 4.0}, CompGPA));
    assert(!SearchStudent(students, {"A", 3.0}, CompGPA));
    assert(!SearchStudent(students, {"B", 3.0}, CompGPA));
    assert(SearchStudent(students, {"D", 3.2}, CompGPA));
    return 0;
}