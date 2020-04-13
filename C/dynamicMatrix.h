//templates cd
#include <iostream>
#include "staticMatrix.h"

using namespace std;

template <typename T>
class Matrix<T, 0, 0>
{
    size_t n, m;
    T *data;

public:
    Matrix() : n(T{}), m(T{}), data(nullptr){};
    Matrix(int n_, int m_) : n(n_), m(m_), data(n * m ? new T[n * m] : nullptr)
    {
        fill(data, data + (n * m), T{});
        cout << "constructor of " << n << 'x' << m << " dynamic matrix" << endl;
    }
    Matrix(initializer_list<initializer_list<T>> data_)
    {
        size_t max_size = 0;

        for (auto &row : data_)
        {
            max_size = max(max_size, row.size());
        }

        int data_size = max_size * data_.size();
        n = data_.size();
        m = max_size;
        data = new T[data_size];
        size_t ctr = 0;

        fill(data, data + data_size, 0);
        for (auto &row : data_)
        {
            copy(row.begin(), row.end(), data + (ctr * max_size));
            ctr++;
        }
        cout << "constructor of " << n << 'x' << m << " dynamic matrix from initializer list" << endl;
    }
    Matrix(Uninitialized, size_t n_ = 0, size_t m_ = 0) : n(n_), m(m_)
    {
        data = new T[n * m];
        cout << "constructor of uninitialized dynamic matrix" << endl;
    }
    template <size_t N, size_t M>
    explicit Matrix(const Matrix<T, N, M> &a) : n(N), m(M)
    {
        cout << " conversion from static to dynamic matrix" << endl;
        data = new T[n * m];
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                data[(i * m) + j] = a(i + 1, j + 1);
            }
        }
    }
    Matrix(const Matrix &toCopy) : m(toCopy.m), n(toCopy.n), data(n * m ? new T[n * m] : nullptr)
    {
        cout << "copy constructor of dynamic matrix" << endl;
        copy(toCopy.data, toCopy.data + (n * m), data);
    }
    Matrix &operator=(const Matrix &toCopy)
    {
        cout << "copy assignment operator" << endl;
        if (this != &toCopy)
        {
            delete[] data;
            m = toCopy.m;
            n = toCopy.n;
            data = n * m ? new T[n * m] : nullptr;
            copy(toCopy.data, toCopy.data + (n * m), data);
        }
        return *this;
    }
    Matrix(Matrix &&toMove) : n(toMove.n), m(toMove.m), data(toMove.data)
    {
        cout << "move constructor " << endl;
        toMove.data = nullptr;
        toMove.n = T{};
        toMove.m = T{};
    }
    Matrix &operator=(Matrix &&toMove)
    {
        cout << "move assignment operator " << endl;
        if (this != &toMove)
        {
            delete[] data;
            n = toMove.n;
            m = toMove.m;
            data = toMove.data;
            toMove.data = nullptr;
            toMove.n = T{};
            toMove.m = T{};
        }
        return *this;
    }
    T &operator()(const int &i, const int &j)
    {
        return data[((i - 1) * m) + j - 1];
    }
    T &operator()(const int &i, const int &j) const
    {
        return data[((i - 1) * m) + j - 1];
    }
    size_t numberOfRows() const
    {
        return n;
    }
    size_t numberOfColumns() const
    {
        return m;
    }

    ~Matrix()
    {
        delete[] data;
    }
};

template <typename T>
Matrix<T, 0, 0> operator*(const Matrix<T, 0, 0> &m1, const Matrix<T, 0, 0> &m2)
{
    if (m1.numberOfColumns() != m2.numberOfRows())
    {
        throw MatrixException();
    }
    return product<T, 0, 0>(m1, m2);
}
template <typename T, size_t R, size_t S>
Matrix<T, 0, 0> operator*(const Matrix<T, R, S> &m1, const Matrix<T, 0, 0> &m2)
{
    if (m1.numberOfColumns() != m2.numberOfRows())
    {
        throw MatrixException();
    }
    return product<T, 0, 0>(m1, m2);
}
template <typename T, size_t R, size_t S>
Matrix<T, 0, 0> operator*(const Matrix<T, 0, 0> &m1, const Matrix<T, R, S> &m2)
{
    if (m1.numberOfColumns() != m2.numberOfRows())
    {
        throw MatrixException();
    }
    return product<T, 0, 0>(m1, m2);
}
template <typename T>                                                           //TODO - without T,N,M?
Matrix<T, 0, 0> operator+(const Matrix<T, 0, 0> &m1, const Matrix<T, 0, 0> &m2) //TODO - why friend?
{
    if (m1.numberOfRows() != m2.numberOfRows() || m1.numberOfColumns() != m2.numberOfColumns())
    {
        throw MatrixException();
    }
    return addition<T>(m1, m2);
}
template <typename T, size_t N, size_t M>                                       //TODO - without T,N,M?
Matrix<T, N, M> operator+(const Matrix<T, N, M> &m1, const Matrix<T, 0, 0> &m2) //TODO - why friend?
{
    if (m1.numberOfRows() != m2.numberOfRows() || m1.numberOfColumns() != m2.numberOfColumns())
    {
        throw MatrixException();
    }
    return addition<T>(m1, m2);
}
template <typename T, size_t N, size_t M>                                       //TODO - without T,N,M?
Matrix<T, N, M> operator+(const Matrix<T, 0, 0> &m1, const Matrix<T, N, M> &m2) //TODO - why friend?
{
    if (m1.numberOfRows() != m2.numberOfRows() || m1.numberOfColumns() != m2.numberOfColumns())
    {
        throw MatrixException();
    }
    return addition<T>(m2, m1);
}