#ifndef __CONCEPTS_H__
#define __CONCEPTS_H__

#include <concepts> // встроенные концепты

template <typename T>
concept MatrixType = requires { std::semiregular<T>; };

template <typename T, typename T2>
concept PermittedType = requires {
    std::constructible_from<T2, T>;
    std::convertible_to<T2, T>;
};

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

template <typename T>
concept NumericMatrix = requires(T m) {
    {
        -m
    } -> Numeric;
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

template <typename T, typename T2>
concept MatrixDiv = requires(T a, T2 b) {
    MatrixFloatPoint<T>;
    MatrixFloatPoint<T2>;
    {
        a / b
    } -> std::convertible_to<T>;
};

template <typename T, typename U>
concept PermittedContainer = requires(U &u) {
    {
        u.get_rows()
    } noexcept -> std::same_as<typename T::size_type>;
    {
        u.get_cols()
    } noexcept -> std::same_as<typename T::size_type>;
};

#endif // __CONCEPTS_H__