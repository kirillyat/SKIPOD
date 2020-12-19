// kirillyat
// 2020 CMC MSU

#include <cmath>
#include <iostream>

using namespace std;

// Тип функции
typedef double (*func)(double);

// Интегрируемая функция
double my_function(double x)
{
    return pow(x, 4) + sin(x)*log(3*x) + sqrt(x) + 1;
}

// Площадь одной трапеции
double trapezium(double a, double b, func f)
{
    return (f(a)+f(b))*(b-a)/2;
}


int main(int argc, char* argv[])
{
    // Количество интервалов, на которые разбиваем область интегрирования
    const int N = 100000000;

    // Диапозон интегрирования
    double a = 1, b = 10;

    // Переменная для интегральной суммы (shered)
    double integral_sum = 0.0;
    
    /*Основной Код*/
    
    for (size_t i = 0; i < N; i++)
        integral_sum += trapezium(a+(b-a)*(i)/N, a+(b-a)*(i+1)/N, my_function);;
    
    cout << "Результат: " << integral_sum << endl;

    return 0;
}
