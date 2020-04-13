//matrix implementation with initializer_list and move constructors
#include <iostream>
#include <string>

using namespace std;

class Matrix
{
    int n, m;
    double *data;

public:
    Matrix() : n(0), m(0), data(nullptr){};
    Matrix(int n_, int m_) : n(n_), m(m_), data(n * m ? new double[n * m] : nullptr)
    {
        fill(data, data + (n * m), 0);
        cout << "constructor of " << n << 'x' << m << " matrix" << endl;
    }
    Matrix(initializer_list<initializer_list<double>> data_)
    {
        size_t max_size = 0;

        for (auto &row : data_)
        {
            max_size = max(max_size, row.size());
        }

        int data_size = max_size * data_.size();
        n = data_.size();
        m = max_size;
        data = new double[data_size];
        size_t ctr = 0;

        fill(data, data + data_size, 0);
        for (auto &row : data_)
        {
            copy(row.begin(), row.end(), data + (ctr * max_size));
            ctr++;
        }
        cout << "constructor of " << n << 'x' << m << " matrix from initializer list" << endl;
    }
    friend void swap(Matrix &first, Matrix &second)
    {
        using std::swap;
        swap(first.n, second.n);
        swap(first.m, second.m);
        swap(first.data, second.data);
    }
    Matrix(const Matrix &toCopy) : m(toCopy.m), n(toCopy.n), data(n * m ? new double[n * m] : nullptr)
    {
        cout << "copy constructor" << endl;
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
            data = n * m ? new double[n * m] : nullptr;
            copy(toCopy.data, toCopy.data + (n * m), data);
        }
        return *this;
    }
    Matrix(Matrix &&toMove) : n(toMove.n), m(toMove.m), data(toMove.data)
    {
        cout << "move constructor " << endl;
        toMove.data = nullptr;
        toMove.n = 0;
        toMove.m = 0;
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
            toMove.n = 0;
            toMove.m = 0;
        }
        return *this;
    }
    Matrix operator-() const
    {
        Matrix tmp = Matrix(this->n, this->m);
        for (int i = 0; i < this->n * this->m; i++)
        {
            tmp.data[i] = -(this->data[i]);
        }
        return tmp;
    }
    double &operator()(const int &i, const int &j)
    {
        return data[(i * m) + j];
    }
    double &operator()(const int &i, const int &j) const
    {
        return data[(i * m) + j];
    }
    friend ostream &operator<<(ostream &out, Matrix &matrix);

    ~Matrix()
    {
        delete[] data;
    }
};

ostream &operator<<(ostream &out, Matrix &matrix)
{
    for (int i = 0; i < matrix.n; i++)
    {
        out << '{';
        for (int j = 0; j < matrix.m; j++)
        {
            out << matrix(i, j);
            if (j != matrix.m - 1)
            {
                out << ", ";
            }
        }
        out << '}' << endl;
    }
    return out;
}

class MatrixWithLabel : public Matrix
{
    string label = "A";

public:
    //konstruktory z Marix
    using Matrix::Matrix;
    MatrixWithLabel(string label_, int n_, int m_) : Matrix(n_, m_), label(label_) {}
    MatrixWithLabel(string label_, initializer_list<initializer_list<double>> data_) : Matrix(data_), label(label_) {}
    MatrixWithLabel(const MatrixWithLabel &toCopy) : Matrix(toCopy), label(toCopy.label) {}
    MatrixWithLabel(MatrixWithLabel &&toMove) = default;
    MatrixWithLabel &operator=(const MatrixWithLabel &toCopy) = default;
    MatrixWithLabel &operator=(MatrixWithLabel &&toMove) = default;
    void setLabel(string new_lable)
    {
        label = new_lable;
    }
    string getLabel()
    {
        return label;
    }
};

int main()
{
    Matrix m1;                                              // default constructor: N=M=0, data=nullptr
    Matrix m2(3, 4);                                        // N = 3, M = 4, data = N*M doubles set to 0.0
    Matrix m3({{1, 2, 3}, {32, 23, 22}, {3, 234, 23, 44}}); // from initializer_list
    cout << m2(1, 1) << endl;                               // 0 - the first element in data (we count from 1)
    cout << m3(2, 2) << endl;                               // 23
    cout << m3;
    cout << endl;

    cout << "Copy semantics \n";
    Matrix m4 = m2; // copy constructor that makes deep copy of the matrix m2
    m4 = m3;        // copy assignment makes deep copy of the matrix m3
    cout << endl;

    cout << "Move semantics \n";
    Matrix m7 = std::move(m2);
    m4 = -m3;
    cout << endl;

    cout << "Copy elision \n";
    Matrix m6 = -m4;
    Matrix *pm = new Matrix(-m4);
    //cout << m6;
    cout << m6(1, 0) << endl; // 32, indeksowanie od 0,zamiast (2,1)

    cout << endl;
    cout << "Inheritance \n";
    MatrixWithLabel l0("B", 3, 4);
    MatrixWithLabel l1({{1, 2}, {4, 5}});
    l1.setLabel("A");
    MatrixWithLabel l2 = l1;
    MatrixWithLabel l3 = std::move(l1);
    cout << l2.getLabel() << " " << l3.getLabel() << endl;
    cout << l1.getLabel() << endl;

    return 0;
}