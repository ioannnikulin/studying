#include "Matrix.h"
#include <ios>
#include <iomanip>
#include <cmath>

using namespace std;

Matrix::Matrix(const constr_modes constr_mode, const int p_rows, const int p_cols, const int p_val)
{
    switch(constr_mode)
    {
        case mode_copy:
            m_items = vector<vector<int>>(p_rows, vector<int>(p_cols, p_val));
            break;
        case mode_identity:
            m_items = vector<vector<int>>(p_rows, vector<int>(p_rows, 0));
            for (int i = 0; i < p_rows; i++)
            {
                m_items[i][i] = 1;
            }
            break;
        case mode_conseq:
            m_items = vector<vector<int>>(p_rows, vector<int>(p_cols, 0));
            {
                int val = 0;
                for (int r = 0; r < p_rows; r ++)
                {
                    for (int c = 0; c < p_cols; c ++)
                    {
                        m_items[r][c] = val ++;
                    }
                }
            }
            break;
        default:
            cerr << "Error: unrecognized matrix creation mode" << endl;
            m_items = vector<vector<int>>(1, vector<int>(1, 0));
    }
}

Matrix::Matrix(const int p_rows, const int p_cols, initializer_list<int> p_vals)
{
    m_items = vector<vector<int>>(p_rows, vector<int>(p_rows, 0));
    for (int i = 0; i < p_vals.size() and i < p_rows * p_cols; i ++)
    {
        m_items[i / p_cols][i % p_cols] = *(p_vals.begin() + i);
    }
}

Matrix::~Matrix()
{

}

int Matrix::get_item(const int p_row, const int p_col) const
{
    return m_items[p_row][p_col];
}

void Matrix::set_item(const int p_row, const int p_col, const int p_val)
{
    if (p_row >= this->rows())
    {
        cerr << "cannot assign value: no such row" << endl;
        return;
    }
    if (p_col >= this->cols())
    {
        cerr << "cannot assign value: no such column" << endl;
        return;
    }
    m_items[p_row][p_col] = p_val;
}

ostream & operator<<(ostream & p_os, const Matrix & p_m)
{
    int rows = p_m.rows();
    int cols = p_m.cols();
    int mx = p_m.get_item(0, 0);
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            if (abs(p_m.get_item(r, c)) > abs(mx))
            {
                mx = p_m.get_item(r, c);
            }
        }
    }
    if (rows <= 0)
    {
        p_os << "empty matrix: no rows" << endl;
    }
    if (cols <= 0)
    {
        p_os << "empty matrix: no columns" << endl;
    }
    int width = to_string(mx).size();
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            p_os << setw(width) << p_m.get_item(r, c) << setw(1) << " ";
        }
        p_os << endl;
    }
    return p_os;
}

istream & operator>>(istream & p_is, Matrix & p_m)
{
    int rows = p_m.rows();
    int cols = p_m.cols();
    int val = 0;
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            if (not (p_is >> val))
            {
                val = 0;
            }
            p_m.set_item(r, c, val);
        }
    }
    return p_is;
}
int Matrix::rows() const
{
    return m_items.size();
}
int Matrix::cols() const
{
    if (m_items.size() == 0)
    {
        return 0;
    }
    return m_items[0].size();
}

Matrix Matrix::add(const Submatrix & sbm_this, const Matrix & p_a, const Submatrix & sbm_a) const
{
    int trf = sbm_this.m_idxs[sbm_row][sbm_from];
    int trt = sbm_this.m_idxs[sbm_row][sbm_to];
    int rows = trt - trf;

    int tcf = sbm_this.m_idxs[sbm_col][sbm_from];
    int tct = sbm_this.m_idxs[sbm_col][sbm_to];
    int cols = tct - tcf;

    int arf = sbm_a.m_idxs[sbm_row][sbm_from];
    int art = sbm_a.m_idxs[sbm_row][sbm_to];

    int acf = sbm_a.m_idxs[sbm_col][sbm_from];
    int act = sbm_a.m_idxs[sbm_col][sbm_to];

    Matrix res(*this);

    if (trt > this->rows() or trf < 0 or trt < 0)
    {
        cerr << "Error: not enough rows in first matrix" << endl;
        return res;
    }

    if (tct > this->cols() or tcf < 0 or tct < 0)
    {
        cerr << "Error: not enough columns in first matrix" << endl;
        return res;
    }

    if (art > p_a.rows() or arf < 0 or art < 0)
    {
        cerr << "Error: not enough rows in second matrix" << endl;
        return res;
    }

    if (act > p_a.cols() or acf < 0 or act < 0)
    {
        cerr << "Error: not enough columns in second matrix" << endl;
        return res;
    }


    if (rows != art - arf
        or cols != act - acf)
    {
        cerr << "Error: cannot add/subtract matrices of different sizes" << endl;
        return res;
    }

    for (int r = trf; r < trt; r ++)
    {
        for (int c = tcf; c < tct; c ++)
        {
            res.set_item(r, c, this->get_item(r, c) + p_a.get_item(r - trf + arf, c - tcf + acf));
        }
    }
    return res;
}

Matrix Matrix::subtract(const Submatrix & sbm_this, const Matrix & p_a, const Submatrix & sbm_a) const
{
    return this->add(sbm_this, p_a * -1, sbm_a);
}

Matrix & Matrix::operator+=(const Matrix & p_a)
{
    Submatrix t_whole;
    t_whole[sbm_row][sbm_from] = 0;
    t_whole[sbm_row][sbm_to] = this->rows();
    t_whole[sbm_col][sbm_from] = 0;
    t_whole[sbm_col][sbm_to] = this->cols();

    Submatrix a_whole;
    a_whole[sbm_row][sbm_from] = 0;
    a_whole[sbm_row][sbm_to] = p_a.rows();
    a_whole[sbm_col][sbm_from] = 0;
    a_whole[sbm_col][sbm_to] = p_a.cols();

    this->copy_items(this->add(t_whole, p_a, a_whole));
    return * this;
}

Matrix & Matrix::operator*=(const Matrix & p_a)
{
    int rows = this->rows();
    int connect = this->cols();
    int cols = p_a.cols();
    if (connect != p_a.rows())
    {
        cerr << "Error: cannot multiply incompatible matrices" << endl;
        return *this;
    }
    if (rows == connect and connect == cols)
    {
        Matrix res(schtrassen_multiply(p_a));
        return res;
    }
    Matrix res(constr_modes::mode_copy, rows, cols);
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            int val = 0;
            for (int i = 0; i < connect; i ++)
            {
                val += this->get_item(r, i) * p_a.get_item(i, c);
            }
            res.set_item(r, c, val);
        }
    }
    this->copy_items(res);
    return * this;
}

Matrix & Matrix::operator-=(const Matrix & p_a)
{
    (*this) += p_a * -1;
    return * this;
}

Matrix & Matrix::operator*=(const int p_a)
{
    int rows = this->rows();
    int cols = this->cols();
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            this->set_item(r, c, this->get_item(r, c) * p_a);
        }
    }
    return * this;
}

Matrix Matrix::operator~() const
{
    int rows = this->cols();
    int cols = this->rows();
    Matrix res(constr_modes::mode_copy, rows, cols);
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            res.set_item(r, c, this->get_item(c, r));
        }
    }
    return res;
}

int Matrix::copy_items(const Matrix & p_a)
{
    int rows = p_a.rows();
    int cols = p_a.cols();
    this->m_items = vector<vector<int>>(rows, vector<int>(cols, 0));
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            this->set_item(r, c, p_a.get_item(r, c));
        }
    }
    return 0;
}

Matrix operator+(Matrix p_a, const Matrix & p_b)
{
    p_a += p_b;
    return p_a;
}

Matrix operator*(Matrix p_a, const Matrix & p_b)
{
    p_a *= p_b;
    return p_a;
}

Matrix operator-(Matrix p_a, const Matrix & p_b)
{
    p_a -= p_b;
    return p_a;
}

Matrix operator*(Matrix p_a, const int p_b)
{
    p_a *= p_b;
    return p_a;
}

Matrix operator*(const int p_a, Matrix p_b)
{
    p_b *= p_a;
    return p_b;
}

Matrix & Matrix::operator=(const Matrix & p_a)
{
    this->copy_items(p_a);
    return * this;
}

Matrix::Matrix(const Matrix & p_a)
{
    this->copy_items(p_a);
}
/*
int & Row::operator[](int p_idx)
{
    return m_parent.m_items[m_row_idx][p_idx];
}

Row Matrix::operator[](int p_idx)
{
    return Row(*this, p_idx);
}
*/
double Matrix::determinant() const
{
    int rows = this->rows();
    if (rows != this->cols())
    {
        cerr << "cannot find a determinant for a nonsquare matrix" << endl;
        return nan("");
    }
    if (rows == 1)
    {
        return this->get_item(0, 0);
    }
    double res = 0;
    for (int i = 0; i < rows; i ++)
    {
        res += pow(-1, i) * get_item(0, i) * (this->minor(0, i).determinant());
    }
    return res;
}

Matrix Matrix::minor(int p_row, int p_col) const
{
    if (p_row > this->rows())
    {
        cerr << "cannot create a minor: no such row" << endl;
        return err;
    }
    if (p_col > this->cols())
    {
        cerr << "cannot create a minor: no such column" << endl;
        return err;
    }
    Matrix res(*this);
    res.m_items.erase(res.m_items.begin() + p_row);
    int rows = this->rows() - 1;
    int cols = this->cols() - 1;
    for (int r = 0; r < rows; r ++)
    {
        for (int c = p_col; c < cols; c ++)
        {
            res.m_items[r][c] = res.m_items[r][c + 1];
        }
        res.m_items[r].pop_back();
    }
    return res;
}

bool Matrix::operator==(const Matrix & p_a) const
{
    int rows = this->rows();
    int cols = this->cols();
    if (rows != p_a.rows() or cols != p_a.cols())
    {
        return false;
    }

    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            if (this->get_item(r, c) != p_a.get_item(r, c))
            {
                return false;
            }
        }
    }
    return true;
}

Matrix Matrix::submatrix(Submatrix p_subm) const
{
    Matrix res(constr_modes::mode_copy, p_subm[sbm_row][sbm_to] - p_subm[sbm_row][sbm_from], p_subm[sbm_col][sbm_to] - p_subm[sbm_col][sbm_from]);
    for (int r = p_subm[sbm_row][sbm_from]; r < p_subm[sbm_row][sbm_to]; r ++)
    {
        for (int c = p_subm[sbm_col][sbm_from]; c < p_subm[sbm_col][sbm_to]; c ++)
        {
            res.set_item(r - p_subm[sbm_row][sbm_from], c - p_subm[sbm_col][sbm_from], this->get_item(r, c));
        }
    }
    return res;
}

