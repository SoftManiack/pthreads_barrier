#define _POSIX_C_SOURCE 200112L // включение функций из POSIX (pthread_barrier_t, pthread_spinlock_t)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> 

pthread_barrier_t barrier;

struct ParamThread {
    int* arr;
    int size;
    int thread_num;
};

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int random(int min, int max){
    return min + rand() % ( max - min + 1);
}

void merge(){

}   

void * sort_thr(void *arg){
    struct ParamThread* param_thread = (struct ParamThread*)arg;

    printf("ss");
    clock_t start, end;
    double cpu_time;

    qsort(param_thread->arr, param_thread->size, sizeof(int), compare);

    start = clock();

    end = clock();

    for(int i = 0; i < 100; i++){
        printf("%d\n", param_thread->arr[i]);
    }

    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Поток %d отсортировал массива за %.6f секунд\n", param_thread->thread_num, cpu_time);

    pthread_barrier_wait(&barrier);

    return NULL; // успешное завершение
}

int main(){

    srand(time(NULL));

    // создать массив чисел для сортировки

    int size_arr_1 = random(8899,9000);
    int size_arr_2 = random(89999,99999);
    int size_arr_3 = random(10000,34000);
    int size_arr_4 = random(1000,2000);

    printf("size %d\n", size_arr_1);

    int* arr1 = malloc(size_arr_1  * sizeof(int));
    if (arr1 == NULL) {
        printf("Ошибка выделения памяти!\n");
        return -1;
    }

    int* arr2 = malloc(size_arr_2  * sizeof(int));
    int* arr3 = malloc(size_arr_3  * sizeof(int));
    int* arr4 = malloc(size_arr_4  * sizeof(int));

    for(int i = 0; i < size_arr_1; i++) arr1[i] = random(1,999);
    for(int i = 0; i < size_arr_2; i++) arr2[i] = random(1,999);
    for(int i = 0; i < size_arr_3; i++) arr3[i] = random(1,999);
    for(int i = 0; i < size_arr_4; i++) arr4[i] = random(1,999);

    struct ParamThread params_thread[4] = {
        {arr1, size_arr_1, 1},
        {arr2, size_arr_2, 2},
        {arr3, size_arr_3, 3},
        {arr4, size_arr_4, 4},
    };

    printf("%d",  sizeof(params_thread[0].arr) / sizeof(int));  

    //pthread_barrier_wait();

    //qsort(arr1, sizeof(arr1) / sizeof(arr1[0]), sizeof(int), compare_int);
    //qsort(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), compare_int);

    //printf("Массив 1 %d \n", sizeof(params_thread[0].arr) / sizeof(int));
    //printf("Массив 2 %d \n", sizeof(params_thread[1].arr) / sizeof(int));
    //printf("Массив 3 %d \n", sizeof(params_thread[2].arr) / sizeof(int));
    //printf("Массив 4 %d \n", sizeof(params_thread[3].arr) / sizeof(int));
    //printf("\n");

    if (pthread_barrier_init(&barrier, NULL, 4) != 0) {
        printf("Ошибка инициализации барьера\n");
        return 1;
    }

    for(int i = 0; i < 4; i++){ 
        if(pthread_create(&params_thread[i].thread_num, NULL, sort_thr, &params_thread[i]) != 0){
            printf("Ошибка создания потока\n");
            return 1;
        }   
    }

    pthread_barrier_wait(&barrier);

    printf("все потоки завершенны \n");

    //merge();

    //pthread_join(&params_thread[0].thread_num, NULL);

    //  pthread_barrier_destroy(&barrier);
    return 0;
    
}
