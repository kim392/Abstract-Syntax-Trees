/**
 * @file circ_array.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <stdexcept>
#include "circ_array.h"

namespace cs225
{

template <class T>
circ_array<T>::circ_array()
{
    /// @todo mp_parse.1
}

template <class T>
circ_array<T>::circ_array(uint64_t size)
{
    /// @todo mp_parse.1
}

template <class T>
circ_array<T>::circ_array(const circ_array& other)
{
    /// @todo mp_parse.1
}

template <class T>
circ_array<T>::circ_array(circ_array&& other)
{
    /// @todo mp_parse.1
}

template <class T>
circ_array<T>& circ_array<T>::operator=(circ_array rhs)
{
    /// @todo mp_parse.1
}

template <class T>
circ_array<T>::~circ_array() = default;

template <class T>
void circ_array<T>::swap(circ_array& other)
{
    /// @todo mp_parse.1
}

template <class T>
const T& circ_array<T>::operator[](uint64_t idx) const
{
    /// @todo mp_parse.1
}

template <class T>
T& circ_array<T>::operator[](uint64_t idx)
{
    /// @todo mp_parse.1
}

template <class T>
const T& circ_array<T>::at(uint64_t idx) const
{
    /// @todo mp_parse.1
}

template <class T>
T& circ_array<T>::at(uint64_t idx)
{
    /// @todo mp_parse.1
}

template <class T>
void circ_array<T>::push_front(const T& elem)
{
    /// @todo mp_parse.1
}

template <class T>
void circ_array<T>::push_front(T&& elem)
{
    /// @todo mp_parse.1
}

template <class T>
void circ_array<T>::push_back(const T& elem)
{
    /// @todo mp_parse.1
}

template <class T>
void circ_array<T>::push_back(T&& elem)
{
    /// @todo mp_parse.1
}

template <class T>
void circ_array<T>::pop_front()
{
    /// @todo mp_parse.1
}

template <class T>
void circ_array<T>::pop_back()
{
    /// @todo mp_parse.1
}

template <class T>
void circ_array<T>::erase(uint64_t idx)
{
    /// @todo mp_parse.1
}

template <class T>
uint64_t circ_array<T>::size() const
{
    /// @todo mp_parse.1
}

template <class T>
bool circ_array<T>::empty() const
{
    /// @todo mp_parse.1
}
}
