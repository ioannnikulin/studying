#include "Matrix.h"
#include <ios>

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

Matrix::~Matrix()
{

}

const int Matrix::get_item(const int p_row, const int p_col) const
{
    return m_items[p_row][p_col];
}

const int Matrix::set_item(const int p_row, const int p_col, const int p_val)
{
    m_items[p_row][p_col] = p_val;
    return p_val;
}

ostream & operator<<(ostream & p_os, const Matrix & p_m)
{
    int rows = p_m.rows();
    int cols = p_m.cols();
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            p_os << p_m.get_item(r, c) << " ";
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
const int Matrix::rows() const
{
    return m_items.size();
}
const int Matrix::cols() const
{
    if (m_items.size() == 0)
    {
        return 0;
    }
    return m_items[0].size();
}

Matrix & Matrix::operator+=(const Matrix & p_a)
{
    int rows = this->rows();
    int cols = this->cols();
    if (rows != p_a.rows() or cols != p_a.cols())
    {
        cerr << "Error: cannot add matrices of different sizes" << endl;
        return *this;
    }
    for (int r = 0; r < rows; r ++)
    {
        for (int c = 0; c < cols; c ++)
        {
            this->set_item(r, c, this->get_item(r, c) + p_a.get_item(r, c));
        }
    }
    return *this;
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

Matrix & Matrix::operator=(const Matrix & p_a)
{
    this->copy_items(p_a);
    return * this;
}

Matrix::Matrix(const Matrix & p_a)
{
    this->copy_items(p_a);
}
