#define _POSIX_C_SOURCE 200112L // включение функций из POSIX (pthread_barrier_t, pthread_spinlock_t)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> 

pthread_barrier_t barrier_t;

struct ParamThread {
    int* arr;
    int thread_num;
};

void * sort_thr(void *arg){
    struct ParamThread* param_thread = (struct ParamThread*)arg;

    clock_t start, end;
    double cpu_time;

    //qsort(arr, n, sizeof(int), compare);

    start = clock();

    end = clock();

    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Поток %d отсортировал массива за %.6f секунд\n", param_thread->thread_num, cpu_time);

    return NULL;
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int random(int min, int max){
    return min + rand() % ( max - min + 1);
}

void merge(){

}   

int main(){

    srand(time(NULL));

    // создать массив чисел для сортировки

    int* arr1 = malloc(random(8899,9000)  * sizeof(int));
    int* arr2 = malloc(random(89999,99999)  * sizeof(int));
    int* arr3 = malloc(random(10000,34000)  * sizeof(int));
    int* arr4 = malloc(random(1000,2000)  * sizeof(int));

    printf("%d",  sizeof(arr1) / sizeof(int));

    struct ParamThread params_thread[4] = {
        {arr1, 1},
        {arr2, 2},
        {arr3, 3},
        {arr4, 4},
    };
    
    //pthread_barrier_wait();

    //qsort(arr1, sizeof(arr1) / sizeof(arr1[0]), sizeof(int), compare_int);
    //qsort(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), compare_int);

    printf("Массив 1 %d \n", sizeof(params_thread[0].arr) / sizeof(int));
    printf("Массив 2 %d \n", sizeof(params_thread[1].arr) / sizeof(int));
    printf("Массив 3 %d \n", sizeof(params_thread[2].arr) / sizeof(int));
    printf("Массив 4 %d \n", sizeof(params_thread[3].arr) / sizeof(int));
    printf("\n");

    return 0;
    
}
