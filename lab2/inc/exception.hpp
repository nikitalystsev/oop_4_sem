#pragma once

#include <exception>
#include <string>

using string = std::string;

class MatrixException : public std::exception {
public:
    MatrixException(const string time_info, const string file_info, string class_name, const int line_info,
                     const string err_msg = "No error message") {
        _err_msg = "\nFile: " + file_info + "\nClass: " + class_name + "\nLine: " + std::to_string(line_info) +
                   "\nTime: " + time_info + "Message: " + err_msg;
    }

    virtual ~MatrixException() {};

    virtual const char *what() const

    noexcept override
            {
                    return _err_msg.c_str();
            };
protected:
    string _err_msg;
};


class IndexError : public MatrixException {
public:
    IndexError(const string time_info, const string file_info, string class_name, const int line_info,
               const string err_msg = "No error message") :
            MatrixException(time_info, file_info, class_name, line_info, err_msg) {
        _err_msg += " (error type: Index Error)";
    }
};


class MemoryError : public MatrixException {
public:
    MemoryError(const string time_info, const string file_info, string class_name, const int line_info,
                const string err_msg = "No error message") :
            MatrixException(time_info, file_info, class_name, line_info, err_msg) {
        _err_msg += " (error type: Memory Error)";
    }
};

class InvalidArgument : public MatrixException {
public:
    InvalidArgument(const string time_info, const string file_info, string class_name, const int line_info,
                    const string err_msg = "No error message") :
            MatrixException(time_info, file_info, class_name, line_info, err_msg) {
        _err_msg += " (error type: Invalid Argument)";
    }
};

class IncompatibleElements : public MatrixException {
public:
    IncompatibleElements(const string time_info, const string file_info, string class_name, const int line_info,
                         const string err_msg = "No error message") :
            MatrixException(time_info, file_info, class_name, line_info, err_msg) {
        _err_msg += " (error type: Incompatible Elements)";
    }
};

class InvalidState : public MatrixException {
public:
    InvalidState(const string time_info, const string file_info, string class_name, const int line_info,
                 const string err_msg = "No error message") :
            MatrixException(time_info, file_info, class_name, line_info, err_msg) {
        _err_msg += " (error type: Invalid State)";
    }
};

class IteratorIndexError : public MatrixException {
public:
    IteratorIndexError(const string time_info, const string file_info, string class_name, const int line_info,
                       const string err_msg = "No error message") :
            MatrixException(time_info, file_info, class_name, line_info, err_msg) {
        _err_msg += " (error type: Iterator Index Error)";
    }
};

class IteratorValidationError : public MatrixException {
public:
    IteratorValidationError(const string time_info, const string file_info, string class_name, const int line_info,
                            const string err_msg = "No error message") :
            MatrixException(time_info, file_info, class_name, line_info, err_msg) {
        _err_msg += " (error type: Iterator Validation Error)";
    }
};

