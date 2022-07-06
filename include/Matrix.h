#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix
{
    public:
        Matrix(const int p_rows, const int p_cols = 1, const int p_val = 0);
        ~Matrix();
        const int rows() const;
        const int cols() const;
        const int set_item(const int p_row, const int p_col, const int p_val);
        const int get_item(const int p_row, const int p_col) const;
    protected:

    private:
        std::vector<std::vector<int>> m_items;
        Matrix();
        Matrix(const Matrix &);
        Matrix & operator=(const Matrix &);
};

std::ostream & operator<<(std::ostream & p_os, const Matrix & p_m);
std::istream & operator>>(std::istream & p_is, Matrix & p_m);

#endif // MATRIX_H
