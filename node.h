#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

template<typename T>

struct node
{
    T data;
    int count;
    node *left, *right;


    node();
    node(T d, int c = 1);
    node(const node<T> &other);
    node<T>& operator=(const node<T> &other);
    ~node();

    template<typename U>
    friend
    ostream& operator<<(ostream& out, node<U> &n);

    template<typename U>
    friend
    istream& operator>>(istream& in, node<U> &n);

    template<typename U>
    friend
    bool operator<(node<U> a, node<U> b);

    template<typename U>
    friend
    bool operator>(node<U> a, node<U> b);


    template<typename U>
    friend
    bool operator==(node<U> a, node<U> b);


    template<typename U>
    friend
    bool operator<=(node<U> a, node<U> b);


    template<typename U>
    friend
    bool operator>=(node<U> a, node<U> b);


    template<typename U>
    friend
    bool operator!=(node<U> a, node<U> b);
};

template<typename T>
node<T>::node()
{
    left = right = NULL;
    count = 0;
}

template<typename T>
node<T>::node(T d, int c, int pos)
{
    data = d;
    count = c;
    left = right = NULL;
}


template<typename T>
node<T>::node(const node<T> &other)
{
    left = right = NULL;
    data = other.data;
    count = other.count;
}

template<typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this != &other)
    {
        left = right = NULL;
        data = other.data;
        count = other.count;
    }
    return *this;
}

template<typename T>
node<T>::~node()
{
    count = 0;
    left = right = NULL;
}

template<typename U>
ostream& operator<<(ostream& out, node<U> &n)
{
    out<<n.data<<"["<<n.count<<"] ";
    return out;
}

template<typename U>
istream& operator>>(istream& in, node<U> &n)
{
    char junk;
    U data;
    int count;
    if(in>>data>>junk>>count>>junk)
    {
        n.data = data;
        n.count = count;
        n.left = n.right = NULL;
    }
    return in;
}



template<typename U>
bool operator<(node<U> a, node<U> b)
{
    return a.data < b.data;
}


template<typename U>
bool operator>(node<U> a, node<U> b)
{
    return a.data > b.data;
}


template<typename U>
bool operator==(node<U> a, node<U> b)
{
    return a.data == b.data;
}


template<typename U>
bool operator<=(node<U> a, node<U> b)
{
    return a.data <= b.data;
}


template<typename U>
bool operator>=(node<U> a, node<U> b)
{
    return a.data >= b.data;
}


template<typename U>
bool operator!=(node<U> a, node<U> b)
{
    return a.data != b.data;
}

#endif // NODE_H
