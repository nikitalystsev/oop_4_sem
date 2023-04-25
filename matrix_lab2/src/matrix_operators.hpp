template <typename T>
// переопределили ==
bool Matrix<T>::operator==(const Matrix& matrix) const
{
    if ((_rows != matrix._rows) || (_cols != matrix._cols))
        return false;

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            if (_data[i][j] != matrix[i][j])
                return false;

    return true;

}

template <typename T>
// переопределили !=
bool Matrix<T>::operator!=(const Matrix& matrix) const
{
    return !operator==(matrix);
}

/* сложение */

template <typename T>
template <typename T2>
// сложение 2-х матриц
decltype(auto) Matrix<T>::operator+(const Matrix<T2> &matrix) const
{
    _check_sizes(matrix);
    Matrix<decltype((*this)[0][0] + matrix[0][0])> tmp(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] + matrix[i][j];

    return tmp;
}

template <typename T>
template <typename T2>
// сложение с числом
decltype(auto) Matrix<T>::operator+(const T2 &elem) const noexcept
{
    Matrix<decltype((*this)[0][0] + elem)> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] + elem;

    return tmp;
}

template <typename T>
// сложение с числом
Matrix<T> &Matrix<T>::operator+=(const T &elem) noexcept
{
for (auto &element: *this)
element += elem;

return *this;
}

template <typename T>
// сложение 2-х матриц
Matrix<T> &Matrix<T>::operator+=(const Matrix &matrix)
{
    _checkSizes(matrix);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] += matrix[i][j];

    return *this;
}

/* вычитание */

template <typename T>
template <typename T2>
// вычитание 2-х матриц
decltype(auto) Matrix<T>::operator-(const Matrix<T2> &matrix) const
{
    _checkSizes(matrix);
    Matrix<decltype((*this)[0][0] - matrix[0][0])> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] - matrix[i][j];

    return tmp;
}

template <typename T>
template <typename T2>
// вычитание элемента из матрицы
decltype(auto) Matrix<T>::operator-(const T2 &elem) const noexcept
{
    Matrix<decltype((*this)[0][0] - elem)> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] - elem;

    return tmp;
}

template <typename T>
// вычитание элемента из матрицы
Matrix<T> &Matrix<T>::operator-=(const T &elem) noexcept
{
    for (auto &element: *this)
        element -= elem;

    return *this;
}

template <typename T>
// вычитание 2-х матриц
Matrix<T> &Matrix<T>::operator-=(const Matrix &matrix)
{
    _checkSizes(matrix);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] -= matrix[i][j];

    return *this;
}

/* умножение */

template <typename T>
template <typename T2>
// умножение 2-х матриц
decltype(auto) Matrix<T>::operator*(const Matrix<T2> &matrix) const
{
    _check_mult_sizes(matrix);

    Matrix<decltype((*this)[0][0] * matrix[0][0])> tmp(_rows, matrix._cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < matrix._cols; ++j)
            for (size_t k = 0; k < _cols; ++k)
                tmp[i][j] += _data[i][k] * matrix[k][j];

    return tmp;
}

template <typename T>
template <typename T2>
// умножение всей матрицы на число
decltype(auto) Matrix<T>::operator*(const T2 &elem) const noexcept
{
    Matrix<decltype((*this)[0][0] * elem)> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] * elem;

    return tmp;
}

template <typename T>
// умножение матрицы на число
Matrix<T> &Matrix<T>::operator*=(const T &elem) noexcept
{
    for (auto &element: *this)
        element *= elem;

    return *this;
}

template <typename T>
// умножение 2-х матриц
Matrix<T> &Matrix<T>::operator*=(const Matrix &matrix)
{
    _check_sizes(matrix);
    _check_mult_sizes(matrix);

    Matrix<T> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            for (size_t k = 0; k < _rows; ++k)
                tmp[i][j] += _data[i][k] + matrix[k][j];

    *this = tmp;
    return *this;
}

/* деление */

template <typename T>
template <typename T2>
// деление матрицы на число
decltype(auto) Matrix<T>::operator/(const T2 &elem) const
{
    if (elem == 0)
    {
        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);

        throw InvalidArgument(asctime(local_time), __FILE__, typeid(*this).name(), __LINE__, "Zero divisor");
    }

    Matrix<decltype((*this)[0][0] / elem)> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] =_data[i][j] / elem;

    return tmp;
}

template <typename T>
// деление матрицы на число
Matrix<T> &Matrix<T>::operator/=(const T &elem)
{
    if (elem == 0)
    {
        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);

        throw InvalidArgument(asctime(local_time), __FILE__, typeid(*this).name(), __LINE__, "Zero divisor");
    }

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] /= elem;

    return *this;
}

template <typename T>
typename Matrix<T>::MatrixRow Matrix<T>::operator[](size_t row)
{
    return _data[row];
}

template <typename T>
const typename Matrix<T>::MatrixRow Matrix<T>::operator[](size_t row) const
{
    return _data[row];
}



template <typename T>
// вывод матрицы на экран
std::ostream &operator<<(std::ostream &out, const Matrix<T> &matrix)
{
    bool first_row = true;
    bool first_col = true;

    for (size_t i = 0; i < matrix.get_rows(); ++i) {
        first_col = true;
        if (!first_row)
            out << "\n";
        first_row = false;

        for(size_t j = 0; j < matrix.get_columns(); ++j) {
            if (!first_col)
                out << '\t';
            first_col = false;
            out << matrix[i][j];
        }
    }
    return out;
}


