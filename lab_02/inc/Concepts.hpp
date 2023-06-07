#ifndef __CONCEPTS_H__
#define __CONCEPTS_H__

#include <concepts> // встроенные концепты

template <typename T>
concept MatrixType = requires { std::semiregular<T>; };

template <typename T, typename T2>
concept PermittedType = requires {
    // std::constructible_from<T2, T>;
    std::convertible_to<T2, T>;
};

template <typename T, typename T2>
concept MatrixEquality = requires {
    std::equality_comparable<T>;
    std::equality_comparable<T2>;
    std::equality_comparable_with<T, T2>;
};

template <typename T, typename U>
concept MatrixSum = requires(T a, U b) {
    // CreateByOtherType<T, U>;
    {
        a + b
    } -> std::convertible_to<T>;
};

template <typename T, typename U>
concept MatrixSub = requires(T a, U b) {
    // CreateByOtherType<T, U>;
    {
        a - b
    } -> std::convertible_to<T>;
};

template <typename T, typename U>
concept MatrixMul = requires(T a, U b) {
    // CreateByOtherType<T, U>;
    {
        a *b
    } -> std::convertible_to<T>;
};

template <typename T>
concept MatrixFloatPoint = requires {
    std::floating_point<T>;
};

#endif // __CONCEPTS_H__