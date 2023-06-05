#include "Iterator.hpp"
// ///////////////////////////////////////////////////////////////////////////////////////////////////

// template <typename T>
// // конструктор итератора
// Iterator<T>::Iterator(const Matrix<T> &matrix, const size_t index)
// {
//     _index = index;
//     _data_iter = matrix._data;
//     _rows = matrix._rows;
//     _cols = matrix._cols;
// }

// ///////////////////////////////////////////////////////////////////////////////////////////////////

// template <typename T>
// // переопределили оператор присваивания =
// Iterator<T> &Iterator<T>::operator=(const Iterator<T> &it)
// {
//     _data_iter = it._data;
//     _index = it._index;
//     _rows = it._rows;
//     _cols = it._cols;

//     return *this;
// }

// ///////////////////////////////////////////////////////////////////////////////////////////////////

// template <typename T>
// // переопределили !=
// bool Iterator<T>::operator!=(Iterator<T> const &other) const
// {
//     return _index != other._index;
// }

// template <typename T>
// // переопределили ==
// bool Iterator<T>::operator==(Iterator<T> const &other) const
// {
//     return _index == other._index;
// }

// template <typename T>
// // переопределили <
// bool Iterator<T>::operator<(Iterator<T> const &other) const
// {
//     return _index < other._index;
// }

// template <typename T>
// // переопределили <=
// bool Iterator<T>::operator<=(Iterator<T> const &other) const
// {
//     return _index <= other._index;
// }

// template <typename T>
// // переопределили >
// bool Iterator<T>::operator>(Iterator<T> const &other) const
// {
//     return _index > other._index;
// }

// template <typename T>
// // переопределили >=
// bool Iterator<T>::operator>=(Iterator<T> const &other) const
// {
//     return _index < other._index;
// }

// ///////////////////////////////////////////////////////////////////////////////////////////////////

// template <typename T>
// // переопределили префиксный инкремент
// Iterator<T> &Iterator<T>::operator++()
// {
//     if (_index < _cols * _rows)
//         ++_index;

//     return *this;
// }

// template <typename T>
// // переопределили постфиксный инкремент
// Iterator<T> Iterator<T>::operator++(int)
// {
//     Iterator<T> it(*this);

//     ++(*this);

//     return it;
// }

// template <typename T>
// // next
// Iterator<T> &Iterator<T>::next()
// {
//     return operator++();
// }

// template <typename T>
// Iterator<T> &Iterator<T>::operator--()
// {
//     if (_index < _cols * _rows)
//     {
//         --_index;
//     }

//     return *this;
// }

// template <typename T>
// Iterator<T> Iterator<T>::operator--(int)
// {
//     Iterator<T> iter(*this);

//     --(*this);

//     return iter;
// }

// template <typename T>
// // переопределили оператор +
// Iterator<T> Iterator<T>::operator+(const int value) const
// {
//     Iterator<T> it(*this);

//     if (value < 0 && it._index < static_cast<size_t>(-value))
//         it._index = 0;
//     else
//         it._index += value;

//     if (it._index < 0)
//         it._index = 0;
//     else if (it._index > _rows * _cols)
//         it._index = _rows * _cols;

//     return it;
// }

// template <typename T>
// // переопределили оператор -
// Iterator<T> Iterator<T>::operator-(const int value) const
// {
//     return operator+(-value);
// }

// template <typename T>
// // переопределили оператор +=
// Iterator<T> &Iterator<T>::operator+=(const int value)
// {
//     _index += value;

//     return *this;
// }

// template <typename T>
// // переопределили оператор -=
// Iterator<T> &Iterator<T>::operator-=(const int value)
// {
//     _index -= value;

//     return *this;
// }

// ///////////////////////////////////////////////////////////////////////////////////////////////////

// template <typename T>
// // переопределили оператор разыменования *
// T &Iterator<T>::operator*()
// {
//     // позже добавить проверки на валидность указателя  и правильность индекса

//     std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = _data_iter.lock();

//     return data_ptr[_index / _cols][_index % _cols];
// }

// template <typename T>
// // переопределили оператор разыменования *
// const T &Iterator<T>::operator*() const
// {
//     std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = _data_iter.lock();

//     return data_ptr[_index / _cols][_index % _cols];
// }

// template <typename T>
// // переопределили ->
// T *Iterator<T>::operator->()
// {
//     std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = _data_iter.lock();

//     return data_ptr[_index / _cols].get_address() + (_index % _cols);
// }

// template <typename T>
// // переопределили ->
// const T *Iterator<T>::operator->() const
// {
//     std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = _data_iter.lock();

//     return data_ptr[_index / _cols].get_address() + (_index % _cols);
// }
// ///////////////////////////////////////////////////////////////////////////////////////////////////

// template <typename T>
// T &Iterator<T>::operator[](const size_t index)
// {
//     std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = _data_iter.lock();

//     return data_ptr[index / _cols][index % _cols];
// }

// template <typename T>
// const T &Iterator<T>::operator[](const size_t index) const
// {
//     std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = _data_iter.lock();

//     return data_ptr[index / _cols][index % _cols];
// }

// ///////////////////////////////////////////////////////////////////////////////////////////////////

// template <typename T>
// Iterator<T>::operator bool() const
// {
//     return _data_iter.expired();
// }

// template <typename T>
// bool Iterator<T>::is_end() const
// {
//     return _index == _rows * _cols;
// }

// template <typename T>
// bool Iterator<T>::is_valid_data() const
// {
//     return !_data_iter.expired();
// }

// ///////////////////////////////////////////////////////////////////////////////////////////////////

// template <typename T>
// // метод для проверки индекса в итераторе
// void Iterator<T>::_check_index(const string hint)
// {
//     if (_index < _rows * _cols)
//         return;

//     throw IteratorIndexError(__FILE__, typeid(*this).name(), __LINE__, hint);
// }

// template <typename T>
// // метод проверяет данные на валидность
// void Iterator<T>::_check_data(const string hint) const
// {
//     if (is_valid_data())
//         return;

//     throw IteratorValidationError(__FILE__, typeid(*this).name(), __LINE__, hint);
// }
