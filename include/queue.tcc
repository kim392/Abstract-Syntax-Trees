/**
 * @file queue.tcc
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "queue.h"

namespace cs225
{

template <class T>
const T& queue<T>::front() const
{
  return arr_[arr_.size()-1]; 
}

template <class T>
T& queue<T>::front()
{
  return arr_[arr_.size()-1]; 
}

template <class T>
void queue<T>::push(const T& elem)
{
    arr_.push_front(elem);
}

template <class T>
void queue<T>::push(T&& elem)
{
    arr_.push_front(elem);
}

template <class T>
void queue<T>::pop()
{
    arr_.pop_back();
}

template <class T>
uint64_t queue<T>::size() const
{
    return arr_.size();
}

template <class T>
bool queue<T>::empty() const
{
    return arr_.empty();
}
}
