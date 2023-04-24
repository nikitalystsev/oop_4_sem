#pragma once

#include <cstddef>

class MatrixBase {
public:
    MatrixBase(size_t rows = 0, size_t columns = 0) : _rows(rows), _cols(columns) {}

    virtual size_t get_columns() const

    noexcept { return _cols; };

    virtual size_t get_rows() const

    noexcept { return _rows; };

    virtual operator bool() const

    noexcept { return _cols && _rows; }

    virtual ~MatrixBase() = 0;

protected:
    size_t _rows = 0, _cols = 0;
};

MatrixBase::~MatrixBase() {}
