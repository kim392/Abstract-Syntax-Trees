/**
 * @file circ_array_test.cpp
 */

#include <cassert>
#include <memory>
#include <vector>
#include <string>
#include "circ_array.h"

using namespace cs225;

void test_provided()
{   
    circ_array<uint64_t> arr{6};
    for (uint64_t i = 0; i < arr.size(); ++i)
        arr[i] = i + 1;
    arr.push_front(0);
    arr.push_back(7);

    for (uint64_t i = 0; i < arr.size(); ++i)
        assert(arr.at(i) == i);
    assert(arr.size() == 8);

    arr.pop_front();
    assert(arr[0] == 1);
    arr.pop_front();
    assert(arr[0] == 2);

    arr.pop_back();
    assert(arr[arr.size() - 1] == 6);
    arr.pop_back();
    assert(arr[arr.size() - 1] == 5);
    assert(arr.size() == 4);

    arr.erase(2);

    assert(arr[0] == 2);
    assert(arr[1] == 3);
    assert(arr[2] == 5);
    assert(arr.size() == 3);
   
}

void test_non_empty()
{

    circ_array<std::unique_ptr<int>> arr_{8};
    assert(arr_.size() == 8);
    for(uint64_t i = 0; i < arr_.size() ; i++)
    {
        if(i % 2 == 0)
            arr_[i] = std::make_unique<int>(i);  //non const []
        else
            arr_.at(i) = std::make_unique<int>(i);  //non const at
    }
    assert(*arr_[7] == 7);
    assert(*arr_.at(0) == 0);

    try
    {
        arr_.at(8);
    }
    catch (const std::out_of_range& ex)
    {        
    }

}

void test_resize_push_pop()
{

    std::vector<std::unique_ptr<int>> data{8};
    for(int i = 0 ; i < 8 ; i++)
        data[i] = std::make_unique<int>(i);

    circ_array<std::unique_ptr<int>> arr_{2};

    arr_.push_front(std::move(data[0])); //move push_front
    arr_.push_front(std::move(data[1])); 
    arr_.push_front(std::move(data[2])); 
    arr_.push_front(std::move(data[3])); 

    arr_.push_back(std::move(data[4])); //move push_back
    arr_.push_back(std::move(data[5])); 
    arr_.push_back(std::move(data[6])); 
    arr_.push_back(std::move(data[7])); 

    for(int i = 0 ; i < 8 ; i++)
        assert(!data[0]);
    for(int i = 0 ; i < 4 ; i++)
        assert(*arr_[i] = 4 - i);
    for(int i = 6 ; i < 9 ; i++)
        assert(*arr_[i] = i - 1);

    arr_.pop_front();
    arr_.pop_front();
    assert(*arr_[0] == 2);

    arr_.pop_back();
    arr_.pop_back();
    assert(*arr_[5] == 6);




    std::string A{"test1"};
    std::string B{"test2"};

    circ_array<std::string> arr2_{2};
    arr2_.push_front(A);    //copy push_front
    assert(arr2_[0] == "test1");
    arr2_.push_back(B);     //copy push_back
    assert(arr2_[3] == "test2");

}

void test_swap()
{
    circ_array<uint64_t> arr1{4};
    for(uint64_t i = 0; i < arr1.size(); i++)
        arr1[i] = i;
    circ_array<uint64_t> arr2{8};
    for(uint64_t i = 0; i < arr2.size(); i++)
        arr2[i] = i + 1;

    arr1.swap(arr2);

    assert(arr1.size() == 8);
    assert(arr2.size() == 4);

    assert(arr1[0] == 1);
    assert(arr2[3] == 3);
}

void test_empty()
{

    /**
     * these lines test empty-related operations
     */

    circ_array<std::unique_ptr<int>> arr_{};
    assert(arr_.size() == 0);
    assert(arr_.empty());

    arr_.push_back(std::make_unique<int>(20)); //move push_back
    assert(arr_.size() == 1);
    assert(*arr_.at(0) == 20);

    arr_.pop_front();
    assert(arr_.size() == 0);
    assert(arr_.empty());

    try
    {
        arr_.at(0);
    }
    catch (const std::out_of_range& ex)
    {        
    }

    arr_.push_front(std::make_unique<int>(10)); //move push_front
    assert(arr_.size() == 1);
    assert(*arr_.at(0) == 10);

    arr_.pop_back();
    assert(arr_.size() == 0);
    assert(arr_.empty());

}

void test_copy()
{
    circ_array<std::string> arr1{8};
    for(int i = 0 ; i < 8 ; i++)
        arr1[i] = std::string{"test"};

    circ_array<std::string> arr2{arr1}; //copy_ctr
    for(int i = 0 ; i < 8 ; i++)
    {
        assert(arr1[i] == "test");
        assert(arr2[i] == "test");
    }

    circ_array<std::string> arr3{8};
    for(int i = 0 ; i < 8 ; i++)
        arr3[i] = std::string{"test2"};

    arr3 = arr2; //copy assignment
    for(int i = 0 ; i < 8 ; i++)
    {
        assert(arr3[i] == "test");
        assert(arr2[i] == "test");
    }
}

void test_move()
{
    circ_array<std::string> arr1{8};
    for(int i = 0 ; i < 8 ; i++)
    arr1[i] = std::string{"test"};
    circ_array<std::string> arr2{std::move(arr1)}; //move_ctr
    for(int i = 0 ; i < 8 ; i++)
        assert(arr2[i] == "test");
    assert(arr1.size() == 0);
    assert(arr1.empty());
    
    circ_array<std::string> arr3{8};
    for(int i = 0 ; i < 8 ; i++)
        arr3[i] = std::string{"test2"};

    arr3 = std::move(arr2); //move assignment
    for(int i = 0 ; i < 8 ; i++)
        assert(arr3[i] == "test");
    assert(arr2.size() == 0);
    assert(arr2.empty());

}

void test_erase()
{

    circ_array<int> arr_{4};
    for(uint64_t i = 0 ; i < arr_.size() ; i++)
        arr_[i] = i + 1;

    arr_.erase(2);
    assert(arr_.size() == 3);
    assert(arr_[2] == 4);

    arr_.erase(1);
    assert(arr_.size() == 2);
    assert(arr_[0] == 1);

    arr_.erase(0);
    assert(arr_.size() == 1);
    assert(arr_[0] == 4);

    arr_.erase(0);
    assert(arr_.size() == 0);

}

int main()
{
    
    test_provided();
    test_non_empty();
    test_resize_push_pop();
    test_swap();
    test_copy();
    test_move(); //depending on how you implement move ctr
    test_empty();
    test_erase();
    return 0;
    
}


    


