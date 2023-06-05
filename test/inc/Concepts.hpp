#ifndef __CONCEPTS_H__
#define __CONCEPTS_H__

#include <concepts> // встроенные концепты

template <typename T>
concept MatrixType = requires { std::semiregular<T>; };

#endif // __CONCEPTS_H__