#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define MAX 16
#define MAX_THREAD 4

int a[] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220 };
int sum[4] = { 0 };
int max = 0;
int maxop = 0;
int sumOp = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* sum_array(void * arg)
{
    int thread_part = *((int*) arg);
    for (int i = thread_part * (MAX / MAX_THREAD); i < (thread_part + 1) * (MAX / MAX_THREAD); i++)
        sum[thread_part] += a[i];
}

void* FindMax(void* arg)
{
    int thread_part = *((int*) arg);
    for (int i = thread_part * (MAX / MAX_THREAD); i < (thread_part + 1) * (MAX / MAX_THREAD); i++)
        if (a[i] > max)
        {
            pthread_mutex_lock(&mutex);
            if (a[i] > max)
            {
                max = a[i];
            }
            pthread_mutex_unlock(&mutex);
        }
}

void SumArOpenMp (){
    #pragma omp parallel
        {
            #pragma omp for
            for (int i = 0; i < MAX; i++)
            sumOp += a[i];
        }
}

void FindMaxOpenMP(){
#pragma omp parallel
    {
    for (int i = 0; i < MAX; i++)
        if (a[i] > maxop)
        #pragma ompcritical
            if (a[i] > maxop)
            {
                maxop = a[i];
            }
    }
}

int main(){

clock_t time;
time = clock();

//Вычисление суммы элементов массива
    pthread_t threadsSum[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; i++){
        int *thread_num = (int*) malloc(sizeof(int));
        *thread_num = i;
        pthread_create(&threadsSum[i], NULL, sum_array, thread_num);
    }

    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threadsSum[i], NULL);


    int total_sum = 0;
    for (int i = 0; i < MAX_THREAD; i++)
        total_sum += sum[i];

    printf("sum is %d ", total_sum);

//Нахождение максимального числа в массиве
    pthread_t threadsMax[MAX_THREAD];


    for (int i = 0; i < MAX_THREAD; i++){
        int *thread_num = (int*) malloc(sizeof(int));
        *thread_num = i;
        pthread_create(&threadsMax[i], NULL, FindMax, thread_num);
    }


    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threadsMax[i], NULL);

    printf("Max is %d ", max);
    pthread_mutex_destroy(&mutex);
    time = time - clock();
    printf(" %f", (double) time/CLOCKS_PER_SEC);

//OpenMP
    time = clock();
    SumArOpenMp();
    printf("SumOpenMP is %d ", sumOp);

    FindMaxOpenMP();
    printf("MaxOpenMP is %d ", maxop);
    time = time - clock();
    printf(" %f", (double) time/CLOCKS_PER_SEC);
    return 0;
}
