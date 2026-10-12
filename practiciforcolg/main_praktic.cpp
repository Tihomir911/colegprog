#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <iostream>

using namespace std;

class DemoArray
{
private:

    vector<int> data;

public:

    DemoArray(size_t size) : data(size, 0) {}

    DemoArray(const int arr[], size_t size)
        : data(arr, arr + size) {}

    size_t size() const
    {
        return data.size();
    }

    int& operator[](size_t index)
    {
        return data.at(index);
    }

    const int& operator[](size_t index) const
    {
        return data.at(index);
    }

    void print() const
    {
        for (int x : data){
            cout << x << ' ';
        }
    }

    DemoArray operator-() const
    {
        DemoArray result(data.size());

        for (size_t i = 0; i < data.size(); ++i)
            result[i] = -data[i];

        return result;
    }

    DemoArray operator+() const
    {
        DemoArray result(data.size());

        for (size_t i = 0; i < data.size(); ++i)
            result[i] = std::abs(data[i]);

        return result;
    }

    DemoArray& operator++()
    {
        for (int& x : data)
            ++x;

        return *this;
    }

    DemoArray& operator--()
    {
        for (int& x : data)
            --x;

        return *this;
    }

    DemoArray operator+(int number) const
    {
        DemoArray result(data.size());

        for (size_t i = 0; i < data.size(); ++i)
            result[i] = data[i] + number;

        return result;
    }

    DemoArray operator+(const DemoArray& other) const
    {
        if (data.size() != other.data.size())
            throw std::runtime_error("Different array sizes");

        DemoArray result(data.size());

        for (size_t i = 0; i < data.size(); ++i)
            result[i] = data[i] + other.data[i];

        return result;
    }

    DemoArray operator-(int number) const
    {
        DemoArray result(data.size());

        for (size_t i = 0; i < data.size(); ++i)
            result[i] = data[i] - number;

        return result;
    }

    bool operator&(const DemoArray& other) const
    {
        if (data.size() != other.data.size())
            return false;

        for (size_t i = 0; i < data.size(); ++i)
            if (data[i] != other.data[i])
                return false;

        return true;
    }

    explicit operator bool() const
    {
        if (data.empty())
            return false;

        for (int x : data)
            if (x <= 0)
                return false;

        return true;
    }
};