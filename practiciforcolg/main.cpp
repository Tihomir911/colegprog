#include <iostream>
#include <vector>

using namespace std;

class Calculator
{
public:

    Calculator()
    {
        cout << "Объект Calculator создан." << endl;
    }


    int sum(int a, int b)
    {
        return a + b;
    }

    bool sum(bool a, bool b)
    {
        return a || b;
    }

    int sum(const vector<int>& array)
    {
        int result = 0;

        for (int number : array)
        {
            result += number;
        }

        return result;
    }
};


int main()
{
    Calculator calculator;

    int a;
    int b;

    cout << "\nВведите первое целое число: ";
    cin >> a;

    cout << "Введите второе целое число: ";
    cin >> b;

    cout << "Сумма целых чисел: "
         << calculator.sum(a, b)
         << endl;


    bool logical1;
    bool logical2;

    cout << "\nВведите первое логическое значение (0 или 1): ";
    cin >> logical1;

    cout << "Введите второе логическое значение (0 или 1): ";
    cin >> logical2;

    cout << "Результат суммы логических значений: "
         << calculator.sum(logical1, logical2)
         << endl;

    int size;

    cout << "\nВведите размер массива: ";
    cin >> size;

    vector<int> numbers(size);

    cout << "Введите элементы массива:" << endl;

    for (int i = 0; i < size; i++)
    {
        cout << "Элемент [" << i << "]: ";
        cin >> numbers[i];
    }


    cout << "Сумма элементов массива: "
         << calculator.sum(numbers)
         << endl;


    return 0;
}