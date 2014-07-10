/**
 * @file circ_array_test.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cassert>
#include <iostream>
#include "circ_array.h"

using namespace cs225;

int main()
{
    circ_array<int> arr{6};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = i + 1;
    arr.push_back(7);
    std::cout << arr[6] << std::endl;
    return 0;
}
