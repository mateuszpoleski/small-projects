//creating iterator
#include <iostream>
#include <vector>

using namespace std;

template <class Container, class Predicate>
class Filter
{
    Container data;
    vector<Predicate> func;

public:
    typedef typename remove_reference<Container>::type::value_type value_type;
    typedef typename remove_reference<Container>::type::iterator con_iterator;
    typedef typename remove_reference<vector<Predicate>>::type::iterator vec_iterator;

    class iterator
    {
        con_iterator data_b;
        con_iterator data_e;
        vec_iterator func_b;
        vec_iterator func_e;

    public:
        iterator(con_iterator data_b_, con_iterator data_e_, vec_iterator func_b_, vec_iterator func_e_) : data_b(data_b_), data_e(data_e_), func_b(func_b_), func_e(func_e_)
        {
            vec_iterator tmp = func_b;
            for (; data_b != data_e; data_b++)
            {
                for (; func_b != func_e; func_b++)
                {
                    if (!(*func_b)(*data_b))
                    {
                        break;
                    }
                    if (func_b + 1 == func_e) // all functions passed
                    {
                        func_b = tmp;
                        return;
                    }
                }
                func_b = tmp;
            }
        }
        iterator operator++()
        {
            vec_iterator tmp = func_b;
            data_b++;
            for (; data_b != data_e; data_b++)
            {
                for (; func_b != func_e; func_b++)
                {
                    if (!(*func_b)(*data_b))
                    {
                        break;
                    }
                    if (func_b + 1 == func_e) // all functions passed
                    {
                        func_b = tmp;
                        return *this;
                    }
                }
                func_b = tmp;
            }
            return *this;
        }
        iterator operator++(int)
        {
            iterator tmp = *this;
            ++*this;
            return tmp;
        }
        value_type operator*()
        {
            return *data_b;
        }
        value_type *operator->()
        {
            return data_b;
        }
        bool operator!=(iterator it)
        {
            return data_b != it.data_b;
        }
        bool operator==(iterator it)
        {
            return !(*this != it);
        }
    };
    Filter(Container c, Predicate p) : data(c)
    {
        func.push_back(p);
    }
    iterator begin()
    {
        return iterator(data.begin(), data.end(), func.begin(), func.end());
    }
    iterator end()
    {
        return iterator(data.end(), data.end(), func.begin(), func.end());
    }
};
template <class Container, class Predicate>
Filter<Container, Predicate> make_filter(Container &&c, Predicate p)
{
    return Filter<Container, Predicate>(forward<Container>(c), p);
}