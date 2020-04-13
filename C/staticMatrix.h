//some more complicated templates
#include <iostream>

using namespace std;

class Uninitialized
{
};
class MatrixException : public runtime_error
{
public:
    MatrixException() : runtime_error("wrong dimension.") {}
};

template <typename T, size_t N, size_t M>
class Matrix
{
    T data[N][M];

public:
    Matrix()
    {
        cout << "constructor of static " << N << " x " << M << " matrix" << endl;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                data[i][j] = T{};
            }
        }
    }
    Matrix(initializer_list<initializer_list<T>> data_)
    {
        cout << "constructor of static " << N << " x " << M << " matrix from initializer_list" << endl;
        int i = 0, j = 0;
        for (auto row : data_)
        {
            for (auto num : row)
            {
                data[i][j] = num;
                j++;
            }
            i++;
            j = 0;
        }
    }
    Matrix(Uninitialized, size_t p = 0, size_t q = 0)
    {
        cout << "constructor of static uninitialized matrix" << endl;
    }
    explicit Matrix(const Matrix<T, 0, 0> &m)
    {
        cout << " conversion from dynamic to static matrix" << endl;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                data[i][j] = m(i + 1, j + 1);
            }
        }
    }
    Matrix(const Matrix &toCopy)
    {
        cout << "copy constructor of static matrix" << endl;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                data[i][j] = toCopy.data[i][j];
            }
        }
    }
    const T &operator()(const int &i, const int &j) const
    {
        return data[i - 1][j - 1];
    }
    T &operator()(const int &i, const int &j)
    {
        return data[i - 1][j - 1];
    }
    static int numberOfRows()
    {
        return N;
    }
    static int numberOfColumns()
    {
        return M;
    }
};
template <typename T, size_t U1, size_t U2, size_t V1, size_t V2>                    //TODO - without T,N,M?
Matrix<T, U1, U2> addition(const Matrix<T, U1, U2> &m1, const Matrix<T, V1, V2> &m2) //TODO - why friend?
{
    Matrix<T, U1, U2> ans(Uninitialized{}, m1.numberOfRows(), m1.numberOfColumns());
    for (int i = 1; i < m1.numberOfRows() + 1; i++)
    {
        for (int j = 1; j < m1.numberOfColumns() + 1; j++)
        {
            ans(i, j) = m1(i, j) + m2(i, j);
        }
    }
    return ans;
}
template <typename T, size_t N, size_t M>                                       //TODO - without T,N,M?
Matrix<T, N, M> operator+(const Matrix<T, N, M> &m1, const Matrix<T, N, M> &m2) //TODO - why friend?
{
    return addition<T>(m1, m2);
}
template <typename T, size_t N, size_t M, size_t U1, size_t U2, size_t V1, size_t V2>
Matrix<T, N, M> product(const Matrix<T, U1, U2> &m1, const Matrix<T, V1, V2> &m2)
{
    Matrix<T, N, M> ans(Uninitialized{}, m1.numberOfRows(), m2.numberOfColumns());
    for (int i = 1; i <= m1.numberOfRows(); i++)
    {
        for (int j = 1; j <= m2.numberOfColumns(); j++)
        {
            T tmp{};
            for (int k = 1; k <= m1.numberOfColumns(); k++)
            {
                tmp += m1(i, k) * m2(k, j);
            }
            ans(i, j) = tmp;
        }
    }
    return ans;
}
template <typename T, size_t R, size_t U, size_t S>
Matrix<T, R, S> operator*(const Matrix<T, R, U> &m1, const Matrix<T, U, S> &m2)
{
    return product<T, R, S>(m1, m2);
}

template <typename T, size_t N, size_t M>
Matrix<T, M, N> transpose(const Matrix<T, N, M> &m)
{
    Matrix<T, M, N> ans(Uninitialized{}, m.numberOfColumns(), m.numberOfRows());
    for (size_t i = 1; i <= m.numberOfRows(); i++)
    {
        for (size_t j = 1; j <= m.numberOfColumns(); j++)
        {
            ans(j, i) = m(i, j);
        }
    }
    return ans;
}
