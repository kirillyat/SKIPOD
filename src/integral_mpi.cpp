
#include <mpi.h>
#include <cmath>
#include <iostream>

using namespace std;

typedef double (*func)(double);

double my_function(double x)
{
    return pow(x, 4) + sin(x)*log(3*x) + sqrt(x) + 1;
}

double trapezium(double a, double b, func f)
{
    return (f(a)+f(b))*(b-a)/2;
}


int main(int argc, char* argv[])
{
    int errCode;
    if ((errCode = MPI_Init(&argc, &argv)) != 0)
        return errCode;

    double start_time, end_time;

    const int N = 100000000;
    const double a = 1, b = 10, h = (b-a)/N;

    double integral_sum = 0.0;

    int myrank, ranksize,i;

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    MPI_Comm_size(MPI_COMM_WORLD, &ranksize);
    
    double cur_a, cur_b, cur_h, d_ba;
    double *sbuf = NULL;

    
    if (!myrank) { 
        d_ba = (b-a)/ranksize;
        sbuf = new double[ranksize*3];
        cur_a = a;
        for (i = 0; i < ranksize; i++) {
            cur_b=cur_a+d_ba;
            sbuf[i*3]=cur_a;
            sbuf[i*3+1]=cur_b;
            sbuf[i*3+2]=h;
            cur_a+=d_ba;
        }
    }

    double rbuf[3];


    MPI_Scatter(sbuf, 3, MPI_DOUBLE, rbuf, 3, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if(sbuf) 
        delete []sbuf;

    cur_a=rbuf[0];
    cur_b=rbuf[1];
    cur_h=rbuf[2];

 
    for( ;cur_a < cur_b;cur_a+=cur_h)
        integral_sum += trapezium(cur_a, cur_a + cur_h, my_function);

    rbuf[0] = integral_sum;

    if(!myrank) sbuf=new double[ranksize];

    MPI_Gather(rbuf, 1, MPI_DOUBLE, sbuf, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    if (!myrank) { 
        for(i = 0, integral_sum = 0; i < ranksize; i++)
            integral_sum += sbuf[i];
        printf("Integral value: %.4f\n",integral_sum);
        delete []sbuf;
    }
    
    MPI_Finalize();
    return 0;
}