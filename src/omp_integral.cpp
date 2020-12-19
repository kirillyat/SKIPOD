// kirillyat
// 2020 CMC MSU


#include <omp.h>
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
    // Переменные для определения затраченного времени на вычисления
    double start_time = 0.0, end_time = 0.0;

    // Количество интервалов, на которые разбиваем область интегрирования
    const int N = 100000000;
 
    // Диапозон интегрирования
    double a = 1, b = 10;

    // Переменная для интегральной суммы (shered)
    double integral_sum = 0.0;
    
    // Фиксируем время перед вычислением
    #ifdef _OPENMP
        start_time = omp_get_wtime();
    #endif

    /*Основной Код*/
    
    #pragma omp parallel reduction(+ : integral_sum)
    {
        # pragma omp for
        for (size_t i = 0; i < N; i++)
            integral_sum += trapezium(a+(b-a)*(i)/N, a+(b-a)*(i+1)/N, my_function);;
    }

    // Фиксируем время после вычислений
    #ifdef _OPENMP
        end_time = omp_get_wtime();
    #endif

    cout << "Результат: " << integral_sum << endl;
    cout << "Время затраченное на вычисление: " << end_time - start_time << endl;


    return 0;
}