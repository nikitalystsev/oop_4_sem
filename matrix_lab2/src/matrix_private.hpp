template<typename T>
void Matrix<T>::_check_sizes(const Matrix <T> &matrix) const {
    if (_rows != matrix._rows || _cols != matrix._cols) {
        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);

        throw IncompatibleElements(asctime(local_time), __FILE__, typeid(*this).name(), __LINE__,
                                   "Different matrix sizes");
    }
}

template<typename T>
void Matrix<T>::_check_mult_sizes(const Matrix <T> &matrix) const {
    if (_cols != matrix._rows) {
        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);

        throw IncompatibleElements(asctime(local_time), __FILE__, typeid(*this).name(), __LINE__,
                                   "Bad sizes of matrices for multiplication");
    }
}

template<typename T>
void Matrix<T>::_check_index(size_t pos, size_t limit) const {
    if (pos > limit) {
        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);

        throw IndexError(asctime(local_time), __FILE__, typeid(*this).name(), __LINE__,
                         "Index is bigger than sizes");
    }
}

template<typename T>
SharedPtr<typename Matrix<T>::MatrixRow[]> Matrix<T>::_mem_alloc(size_t rows, size_t cols) {
    SharedPtr < MatrixRow[] > data = nullptr;

    try {
        data.reset(new MatrixRow[rows]);

        for (size_t i = 0; i < rows; i++)
            data[i].reset(new T[cols], cols);
    }
    catch (std::bad_alloc &err) {
        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);

        throw MemoryError(asctime(local_time), __FILE__, typeid(*this).name(), __LINE__,
                          "_allocateMemory function error");
    }

    return data;
}

