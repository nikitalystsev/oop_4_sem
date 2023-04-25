template<typename T>
// переопределяем = для матрицы
// принимается const lvalue, создается копия matrix и присваивается текущему объекту
Matrix <T> &Matrix<T>::operator=(const Matrix &matrix) {
    _data = _mem_alloc(matrix._rows, matrix._cols);

    _rows = matrix._rows, _cols = matrix._cols;

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] = matrix[i][j];

    return *this;
}

template<typename T>
// переопределяем = для матрицы
// принимается rvalue и передача владения от matrix к текущему объекту
Matrix <T> &Matrix<T>::operator=(Matrix <T> &&matrix) {
    _data = matrix._data;
    _rows = matrix._rows, _cols = matrix._cols;

    return *this;
}

template<typename T>
// переопределяем = для матрицы
// принимаем список инициализации
Matrix <T> &Matrix<T>::operator=(std::initializer_list <std::initializer_list<T>> init_list) {
    auto it = init_list.begin();
    size_t cols = it->size();

    for (const auto &i_list: init_list)
        if (i_list.size() != cols) {
            time_t cur_time = time(NULL);
            auto local_time = localtime(&cur_time);
            throw InvalidArgument(asctime(local_time), __FILE__, typeid(*this).name(), __LINE__,
                                  "Bad initializer list");
        }

    size_t i = 0;
    for (const auto &i_list: init_list)
        for (const auto &elem: i_list) {
            _data[i / cols][i % cols] = elem;
            ++i;
        }

    return *this;
}

