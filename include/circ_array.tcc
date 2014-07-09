/**
 * @file circ_array.tcc
 * @author Sun Woo Kim
 * @date Summer 2014
 */

#include <stdexcept>
#include <iostream>
#include "circ_array.h"

namespace cs225
{

template <class T>
circ_array<T>::circ_array()
    : capacity{0}
{
    arr_ = nullptr;
}

template <class T>
circ_array<T>::circ_array(uint64_t size)
    : capacity{size}, first_{0}, last_{size-1}
{
    arr_ = std::move(std::unique_ptr<T[]> (new T[size]));
}

template <class T>
circ_array<T>::circ_array(const circ_array& other)
    : capacity{other.capacity}, first_{other.first_}, last_{other.last_}
{
    arr_ = std::move(std::unique_ptr<T[]> (new T[capacity]));
    for(uint64_t i = 0; i<capacity; i++)
	arr_[i] = other.arr_[i]; 
}

template <class T>
circ_array<T>::circ_array(circ_array&& other)
    :arr_{nullptr}, capacity{0}, first_{0}, last_{0}
{
    std::swap(*this, other);
}

template <class T>
circ_array<T>& circ_array<T>::operator=(circ_array rhs)
{
    swap(rhs);
    return *this;
}

template <class T>
circ_array<T>::~circ_array() = default;

template <class T>
void circ_array<T>::swap(circ_array& other)
{
    other.arr_.swap(arr_);
    std::swap(other.capacity, capacity);
    std::swap(other.first_, first_);
    std::swap(other.last_, last_);
}

template <class T>
const T& circ_array<T>::operator[](uint64_t idx) const
{
     return arr_[idx];
}

template <class T>
T& circ_array<T>::operator[](uint64_t idx)
{
    return arr_[idx];
}

template <class T>
const T& circ_array<T>::at(uint64_t idx) const
{
    if(idx >= capacity)
	throw std::out_of_range{"invalid index"};
    else if (first_ < last_)
    {
	if(idx < first_ || idx > last_)
	    throw std::out_of_range{"invalid index"};
    }
    else if(last_ < first_)
    {
	if(idx < first_ && idx > last_)
	    throw std::out_of_range{"invalid index"};
    }
    return arr_[idx];
}

template <class T>
T& circ_array<T>::at(uint64_t idx)
{
    if(idx >= capacity)
		throw std::out_of_range{"invalid index"};
    else if (first_ < last_)
    {
        if(idx < first_ || idx > last_)
            throw std::out_of_range{"invalid index"};
    }
    else if(last_ < first_)
    {
        if(idx < first_ && idx > last_)
            throw std::out_of_range{"invalid index"};
    }
    return arr_[idx];
}

template <class T>
void circ_array<T>::resize()
{
    std::unique_ptr<T[]> tmp = std::unique_ptr<T[]> (new T[2*capacity]);
    int j = -1;
    for(uint64_t i =first_; i<capacity; i++)
    {
	j++;
	tmp[j] = arr_[i];
    }
    for(uint64_t i=0; i<first_; i++)
    {
	j++;
	tmp[j] = arr_[i];
    }
    last_ = j;
    first_ = 0;
    capacity = 2*capacity;
    tmp.swap(arr_);
}

template <class T>
void circ_array<T>::push_front(const T& elem)
{
    if((first_==0 && last_ == capacity-1) || (first_-1==last_))
    {
	resize();
    }
    std::unique_ptr<T[]> tmp = std::unique_ptr<T[]> (new T[capacity]);
    tmp[0] = elem;
    for(uint64_t i=0; i<capacity; i++)
    {
	tmp[i+1] = arr_[i];
    }
    arr_.swap(tmp);
    last_++;
}

template <class T>
void circ_array<T>::first_set(int i, int j)
{
    std::cout<< "first: " << first_ << " changed to: ";
     first_ = i;
     last_ = j;
    std::cout<< first_ << std::endl;
}

template <class T>
void circ_array<T>::push_front(T&& elem)
{
if((first_==0 && last_ == capacity-1) || (first_-1==last_))
    {
        resize();
    }
    std::unique_ptr<T[]> tmp = std::unique_ptr<T[]> (new T[capacity]);
    tmp[0] = elem;
    for(uint64_t i=0; i<capacity; i++)
    {
        tmp[i+1] = arr_[i];
    }
    arr_.swap(tmp);
    last_++;
}

template <class T>
void circ_array<T>::push_back(const T& elem)
{
    if((first_==0 && last_ == capacity-1) || (first_-1==last_))
    {
        resize();
    }
    std::unique_ptr<T[]> tmp = std::unique_ptr<T[]> (new T[capacity]);
    for(uint64_t i=0; i<capacity; i++)
    {
        tmp[i] = arr_[i];
    }
    last_++;
    tmp[last_] = elem;
    arr_.swap(tmp);
}

template <class T>
void circ_array<T>::push_back(T&& elem)
{
if((first_==0 && last_ == capacity-1) || (first_-1==last_))
    {
        resize();
    }
    std::unique_ptr<T[]> tmp = std::unique_ptr<T[]> (new T[capacity]);
    for(uint64_t i=0; i<capacity; i++)
    {
        tmp[i] = arr_[i];
    }
    last_++;
    tmp[last_] = elem;
    arr_.swap(tmp);
}

template <class T>
void circ_array<T>::pop_front()
{
    std::unique_ptr<T[]> tmp(new T[capacity]);
    for(int i=1; i<capacity; i++)
    {
	tmp[i-1] = arr_[i];
    }
    last_--;
    arr_.swap(tmp);
}

template <class T>
void circ_array<T>::pop_back()
{
    std::unique_ptr<T[]> tmp(new T[capacity]);
    for(int i=0; i<last_; i++)
    {
	tmp[i] = arr_[i];
    }
    last_--;
    arr_.swap(tmp);
}

template <class T>
void circ_array<T>::erase(uint64_t idx)
{
    /// @todo mp_parse.1
}

template <class T>
uint64_t circ_array<T>::size() const
{
    uint64_t counter = 1;
    if(first_<last_)
    {
        for(uint64_t i = first_; i<last_; i++)
	    counter++;
    }
    else
    {
        for(uint64_t i = first_; i<capacity; i++)
	    counter++;
	for(uint64_t i = 0; i<first_; i++)
	    counter++;
    }
    return counter;
}

template <class T>
bool circ_array<T>::empty() const
{
 //    return first_==last_;
}
}
