template<typename T>
void _check_ptr(T ptr) {
    if (ptr)
        return;

    time_t cur_time = time(NULL);
    auto local_time = localtime(&cur_time);

    throw InvalidArgument(asctime(local_time), __FILE__, "Non-class", __LINE__, "nullptr as a ptr of c-matrix");
}

template<typename T>
// первый конструктор
Matrix<T>::Matrix(size_t rows, size_t columns): MatrixBase(rows, columns) {
    _data = _mem_alloc(rows, columns);
}

template<typename T>
// второй конструктор
Matrix<T>::Matrix(size_t rows, size_t columns, const T &fill): MatrixBase(rows, columns) {
    _data = _mem_alloc(rows, columns);

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            _data[i][j] = fill;
}

template<typename T>
// третий конструктор (размеры и си матрица)
Matrix<T>::Matrix(size_t rows, size_t columns, T **matrix): MatrixBase(rows, columns) {
    _check_ptr(matrix);

    _data = _mem_alloc(rows, columns);

    for (size_t i = 0; i < rows; ++i) {
        _check_ptr(matrix[i]);
        for (size_t j = 0; j < columns; ++j)
            _data[i][j] = matrix[i][j];
    }
}

template<typename T>
// четвертый конструктор (список инициализации)
Matrix<T>::Matrix(std::initializer_list <std::initializer_list<T>> init_list) {
    size_t rows = init_list.size();
    auto it = init_list.begin();
    size_t cols = it->size();

    for (const auto &i_list: init_list)
        if (i_list.size() != cols) {
            time_t cur_time = time(NULL);
            auto local_time = localtime(&cur_time);

            throw InvalidArgument(asctime(local_time), __FILE__, typeid(*this).name(), __LINE__,
                                  "Bad initializer list");
        }

    _data = _mem_alloc(rows, cols);
    _rows = rows;
    _cols = cols;

    size_t i = 0;
    for (const auto &i_list: init_list)
        for (const auto &elem: i_list) {
            _data[i / cols][i % cols] = elem;
            ++i;
        }
}

template<typename T>
// конструктор копирования
Matrix<T>::Matrix(const Matrix &matrix): MatrixBase(matrix._rows, matrix._cols) {
    _data = _mem_alloc(matrix._rows, matrix._cols);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] = matrix[i][j];
}

template<typename T>
Matrix<T>::Matrix(Matrix &&matrix): MatrixBase(matrix._rows, matrix._cols) {
    _data = matrix._data;
}
