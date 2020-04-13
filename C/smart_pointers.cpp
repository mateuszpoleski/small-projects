//string implementation with smart pointers
#include <iostream>
#include <string>
#include <string.h>
#include <memory>
#include <algorithm>

using namespace std;

class String
{
    shared_ptr<string> p;

public:
    String(size_t size = 0) : p(make_shared<string>(size, ' ')) {} // creates an empty string
    String(const char *str) : p(make_shared<string>())
    {
        for (int i = 0; i < strlen(str); i++)
        {
            *p += str[i];
        }
    }                                             // copy C-string
    String(const String &toCopy) : p(toCopy.p) {} // no copy
    String operator=(const String &toCopy)
    {
        if (this != &toCopy)
        {
            p = toCopy.p;
        }
        return *this;
    } // no copy
      // makes a copy of a string if it has more than one reference.
    char &operator[](int i)
    {
        if (!p.unique())
        {
            cout << "creating copy" << endl;
            p = make_shared<string>(*p);
        }
        return (*p)[i];
    }
    // no copy
    char operator[](int i) const
    {
        return (*p)[i];
    }
    // concatenation creates a new string only if both strings are non empty
    friend String operator+(String a, String b);
    // no copy
    friend std::ostream &operator<<(std::ostream &out, String s);
};
String operator+(String a, String b)
{
    if (a.p->length() && b.p->length())
    {
        cout << "creating copy" << endl;
        String tmp = String();
        *(tmp.p) += (*a.p) + (*b.p);
        return tmp;
    }
    else if (a.p->length())
    {
        return a;
    }
    else
    {
        return b;
    }
}
std::ostream &operator<<(std::ostream &out, String s)
{
    out << *s.p;
    return out;
}

int main()
{
    String a("hi");
    String b;
    const String c = a; // no copy
    String d = a + b;   // no copy
    cout << d << endl;
    a[0] = 'l';                    // copy
    a[1] = 'l';                    // no copy
    d = c + a;                     // copy elision
    cout << c << " " << d << endl; // hi hill (no copy)
    cout << c[0] << endl;          // l (no copy)
    cout << a[0] << endl;

    return 0;
}