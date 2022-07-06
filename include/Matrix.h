#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix
{
    public:
        enum constr_modes {mode_copy, mode_identity, mode_conseq};
        Matrix(const constr_modes constr_mode, const int p_rows, const int p_cols = 1, const int p_val = 0);
        ~Matrix();
        const int rows() const;
        const int cols() const;
        const int set_item(const int p_row, const int p_col, const int p_val);
        const int get_item(const int p_row, const int p_col) const;
        Matrix & operator+=(const Matrix & p_a);
        Matrix & operator=(const Matrix & p_a);
        Matrix(const Matrix & p_a);

    protected:

    private:
        int copy_items(const Matrix & p_a);
        std::vector<std::vector<int>> m_items;
        Matrix();
};

Matrix operator+(const Matrix p_a, const Matrix & p_b);

std::ostream & operator<<(std::ostream & p_os, const Matrix & p_m);
std::istream & operator>>(std::istream & p_is, Matrix & p_m);

#endif // MATRIX_H
