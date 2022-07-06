#include "Matrix.h"
#include <ios>

using namespace std;

Matrix::Matrix(const int p_rows, const int p_cols, const int p_val)
{
    m_items = vector<vector<int>>(p_rows, vector<int>(p_cols, p_val));
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
