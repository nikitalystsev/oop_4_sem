#ifndef __CONCEPTS_H__
#define __CONCEPTS_H__

#include <concepts> // встроенные концепты

template <typename T>
concept MatrixType = requires { std::floating_point<T>; };

template <typename T1, typename T2>
concept CreateByOtherType = requires { std::constructible_from<T2, T1>; };

template <typename T>
concept MatrixEquality = requires { MatrixType<T>; std::equality_comparable<T>; };

#endif // __CONCEPTS_H__