#pragma once

#include <exception>
#include <string>

using string = std::string;

// абстрактный класс обработки исключений, связанных с матрицами
class MatrixExceptions : public std::exception {
public:
    // конструктор класса
    MatrixExceptions(const string time_info, const string file_info, string class_name, const int line_info,
                     const string err_msg = "No error message") :
            _err_msg(err_msg + "\nTime: " + time_info + "\nFile: " + file_info + "\nLine: " +
                     std::to_string(line_info) +
                     "\nClass name: " + class_name) {}

    // деструктор класса
    virtual ~MatrixExceptions() {};

    virtual const char *what() const

//    Ключевое слово override указывает компилятору,
//    что данная функция должна переопределять виртуальную функцию
//    из базового класса.
    noexcept override
            {
                    return _err_msg.c_str();
            };

protected:
    string _err_msg;
};

// класс для обработки случаев выхода за пределы матрицы
class IndexError : public MatrixExceptions {
public:
    IndexError(const string time_info, const string file_info, string class_name, const int line_info,
               const string err_msg = "No error message") :
            MatrixExceptions(time_info, file_info, class_name, line_info, err_msg) {
        _err_msg += " (error type: Index Error)";
    }
};

class MemoryError : public MatrixExceptions {
public:
    MemoryError(const string time_info, const string file_info, string class_name, const int line_info,
                const string err_msg = "No error message") :
            MatrixExceptions(time_info, file_info, class_name, line_info, err_msg) {
        _err_msg += " (error type: Memory Error)";
    }
};

class IteratorIndexError : public MatrixExceptions {
public:
    IteratorIndexError(const string time_info, const string file_info, string class_name, const int line_info,
                       const string err_msg = "No error message") :
            MatrixExceptions(time_info, file_info, class_name, line_info, err_msg) {
        _err_msg += " (error type: Iterator Index Error)";
    }
};