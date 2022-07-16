#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <array>
/*
class Matrix;

class Row
{
    public:
        int & operator[](int p_idx);
        Row(Matrix & p_parent, int p_row_idx):
            m_parent(p_parent),
            m_row_idx(p_row_idx)
            {};

    private:
        Matrix & m_parent;
        int m_row_idx;
        Row();
        Row(const Row &);
        Row & operator=(const Row &);
};
*/

const int sbm_row = 0, sbm_col = 1;
const int sbm_from = 0, sbm_to = 1;

struct Submatrix
{
    public:
        std::array<std::array<int, 2>, 2> m_idxs;
        const std::array<int, 2> & operator[](int p_idx) const
        {
            if (m_idxs[p_idx][0] < 0 or m_idxs[p_idx][1] < 0)
            {
                std::cerr << "Warning: negative submatrix parameter" << std::endl;
            }
            return m_idxs[p_idx];
        }
        std::array<int, 2> & operator[](int p_idx)
        {
            return m_idxs[p_idx];
        }
        Submatrix():
            m_idxs({std::array<int, 2> ({-1,-1}), std::array<int, 2> ({-1,-1})})
        {

        }
};

class Matrix
{
    friend class Row;
    public:
        enum constr_modes {mode_copy, mode_identity, mode_conseq};
        Matrix(const constr_modes constr_mode, const int p_rows, const int p_cols = 1, const int p_val = 0);
        ~Matrix();
        int rows() const;
        int cols() const;
        void set_item(const int p_row, const int p_col, const int p_val);
        int get_item(const int p_row, const int p_col) const;
        Matrix & operator+=(const Matrix & p_a);
        Matrix add(const Submatrix & sbm_this, const Matrix & p_a, const Submatrix & sbm_a) const;
        Matrix & operator-=(const Matrix & p_a);
        Matrix subtract(const Submatrix & sbm_this, const Matrix & p_a, const Submatrix & sbm_a) const;
        Matrix & operator*=(const int p_a);
        Matrix & operator*=(const Matrix & p_a);
        bool operator==(const Matrix & p_a) const;
        Matrix operator~() const;
        Matrix & operator=(const Matrix & p_a);
        Matrix(const Matrix & p_a);
        //Row operator[](int p_idx);
        double determinant() const;
        Matrix minor(int p_row, int p_col) const;
        Matrix submatrix(Submatrix p_subm) const;

    protected:

    private:
        Matrix schtrassen_multiply(const Matrix & p_a) const;
        int copy_items(const Matrix & p_a);
        std::vector<std::vector<int>> m_items;
        Matrix();
};

Matrix operator+(const Matrix p_a, const Matrix & p_b);
Matrix operator-(const Matrix p_a, const Matrix & p_b);
Matrix operator*(Matrix p_a, const int p_b);
Matrix operator*(const int p_a, Matrix p_b);
Matrix operator*(Matrix p_a, const Matrix & p_b);

std::ostream & operator<<(std::ostream & p_os, const Matrix & p_m);
std::istream & operator>>(std::istream & p_is, Matrix & p_m);

const Matrix err(Matrix::constr_modes::mode_copy, 0, 0, 0);

#endif // MATRIX_H
