/**
 * @file circ_array.tcc
 * @author Sun Woo Kim
 * @date Summer 2014
 */

#include <stdexcept>
#include <iostream>
#include "circ_array.h"
#include <vector>

namespace cs225
{

template <class T>
circ_array<T>::circ_array()
{
    size_ = 0;
    capacity = 1;
    arr_ = std::move(std::unique_ptr<T[]> (new T[capacity]));
    first_ = 0;
    last_ = 0;
}

template <class T>
circ_array<T>::circ_array(uint64_t size)
    : size_{size}, capacity{size}, first_{0}, last_{size-1}
{
    arr_ = std::move(std::unique_ptr<T[]> (new T[capacity]));
}

template <class T>
circ_array<T>::circ_array(const circ_array& other)
    : size_{other.size_}, capacity{other.capacity}, first_{other.first_}, last_{other.last_}
{
    arr_ = std::move(std::unique_ptr<T[]> (new T[capacity]));
    for(uint64_t i = 0; i<capacity; i++)
	arr_[i] = other.arr_[i]; 
}

template <class T>
circ_array<T>::circ_array(circ_array&& other)
    :arr_{nullptr}, capacity{0}, first_{0}, last_{0}, size_{0}
{
   arr_.swap(other.arr_);
    std::swap(first_, other.first_);
    std::swap(last_, other.last_);
    std::swap(capacity, other.capacity);
    std::swap(size_, other.size_);
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
   other.arr_.swap(arr_);std::swap(size_,other.size_);
    std::swap(other.capacity, capacity);
    std::swap(other.first_, first_);
    std::swap(other.last_, last_);
}

template <class T>
const T& circ_array<T>::operator[](uint64_t idx) const
{
    int x = idx + first_;
    if(x >= capacity)
    {     
	x= x%capacity;
    }
    return arr_[x];	
}

template <class T>
T& circ_array<T>::operator[](uint64_t idx)
{
	uint64_t x = idx + first_;
	if(x >= capacity)
	     x= x%capacity;
	return arr_[x];	
}

template <class T>
const T& circ_array<T>::at(uint64_t idx) const
{
	if (idx>=size_) throw std::out_of_range{"invalid index"};
	int x = idx + first_;
	if(x >= capacity)
	     x = x%capacity;
	return arr_[x];	
}

template <class T>
T& circ_array<T>::at(uint64_t idx)
{
	if (idx>=size_) throw std::out_of_range{"invalid index"};
	int x = idx + first_;
	if(x >= capacity)
	     x = x%capacity;
	return arr_[x];	
}

template <class T>
void circ_array<T>::resize()
{
    std::unique_ptr<T[]> tmp = std::unique_ptr<T[]> (new T[2*capacity]);
    int j = -1;
    for(uint64_t i =first_; i<capacity; i++)
    {
	j++;
	tmp[j] = std::move(arr_[i]);
    }
    for(uint64_t i=0; i<first_; i++)
    {
	j++;
	tmp[j] = std::move(arr_[i]);
    }
    last_ = j;
    first_ = 0;
    capacity = 2*capacity;
    tmp.swap(arr_);
}

template <class T>
void circ_array<T>::push_front(const T& elem)
{
    if((first_==0 && last_ == capacity-1) || (first_-1==last_) || (size_ == capacity))
	resize();
    if(first_ == 0)
    {
	first_ = capacity-1;
	arr_[capacity-1] = elem;
	size_ = size_ + 1;
    }
    else if(first_>last_ && size_ < capacity)
    {
	first_--;
	arr_[first_] = elem;
	size_++;
    }
}

template <class T>
void circ_array<T>::push_front(T&& elem)
{
    if((first_==0 && last_ == capacity-1) || (first_-1==last_) || (size_ == capacity))
	resize();
    if(first_ == 0)
    {
	first_ = capacity-1;
	arr_[capacity-1] = std::move(elem);
	size_ = size_ + 1;
    }
    else if(first_>last_ && size_ < capacity)
    {
	first_--;
	arr_[first_] = std::move(elem);
	size_++;
    }
}





template <class T>
void circ_array<T>::push_back(const T& elem)
{
    if((first_==0 && last_ == capacity-1) || (first_-1==last_) || size_==capacity)
        resize();
    if(last_ == capacity-1)
    {
	last_ = 0;
	arr_[last_] = elem;
	size_++;
    }
    else
    {
	last_++;
	arr_[last_] = elem;
	size_++;
    }    
}

template <class T>
void circ_array<T>::push_back(T&& elem)
{

    if((first_==0 && last_ == capacity-1) || (first_-1==last_) || size_==capacity)
        resize();
    if(last_ == capacity-1)
    {
	last_ = 0;
	arr_[last_] = std::move(elem);
	size_++;
	return;
    }
    if(first_==last_)
    {
	first_++;
    }
	last_++;
	arr_[last_] = std::move(elem);
	size_++;
}

template <class T>
void circ_array<T>::pop_front()
{
	if(first_ + 1 >= capacity)
		first_=0;
	else
		first_++;
	size_--;
}

template <class T>
void circ_array<T>::pop_back()
{
     if(last_-1 < 0)
	last_ = capacity -1;
     else
	last_--;
     size_--;
}

template <class T>
void circ_array<T>::erase(uint64_t idx)
{
    if(idx < size_ || idx > -1)
    {
    int x = idx + first_;
    if(x >= size_)
    {
	x %= capacity;
    }
    int j = 0;
    std::unique_ptr<T[]> tmp = std::unique_ptr<T[]> (new T[capacity]);
    if(first_ < last_)
    {
	for(int i = 0; i <= size_; i++)
	    if(i!=x)
	    {
		tmp[j] = arr_[i];
		j++;
	    }
	arr_.swap(tmp);
	last_--;
	size_--;
    }
    else if(first_ > last_)
    {
	for(int i = first_; i < capacity; i++)
	    if(i!=x)
	    {
		tmp[j] = arr_[i];
	  	j++;
	    }
	for(int i = 0; i <= last_; i++)
	    if(i!=x)
	    {
		tmp[j] = arr_[i];
		j++;
	    }
	arr_.swap(tmp);
	first_ = 0;
	last_--;
	size_--;
    }
    else if(first_ == last_ && x == first_)
    {
	tmp[0] = arr_[first_];
	arr_.swap(tmp);
	last_--;
	size_--;
    }
}
}

template <class T>
uint64_t circ_array<T>::size() const
{
	return size_;
}

template <class T>
bool circ_array<T>::empty() const
{
    return size_ == 0;
}

}
