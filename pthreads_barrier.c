#define _POSIX_C_SOURCE 200112L // включение функций из POSIX (pthread_barrier_t, pthread_spinlock_t)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> 

pthread_barrier_t barrier;

struct ParamThread {
    int* arr;
    int size;
    pthread_t thread_num;
};

int size_params = 0;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int random(int min, int max){
    return min + rand() % ( max - min + 1);                                                             
}

int* merge(struct ParamThread* params)
{
    
    int merge_size = 0;
    int max_size = params[0].size;
    int* merge_arr = malloc(merge_size * sizeof(int));
    int* arr_indexes = malloc(size_params * sizeof(int));

    for(int i = 0; i < size_params; i++){
        merge_size += params[i].size;
    }   

    for(int i = 0; i < size_params; i++){

        if(params[i].size < max_size){
            max_size = params[i].size;
        }
    }

    int merge_arr_index = 0;

    for(int i = 0; i < merge_size; i++) {
        merge_arr[i] = 0;

        int current_num = 0;


    }

    //for(int i = 0; i){
    //
    //}

    // [1,1,1,2,3,4,5]
    // [1,2,2,3,4,4,4]
    // [1,1,1,2,2,2,8]
    // [10,11,100,111,111,111,111]

    // 1-1 2-1 3-1 4-2
    // 1-1 
    // 1-1 2-1 3-1

    // 1-1 2-1 3-1 4-1 5-1 6-1 7-1 8-2


    // [1],[]

    return merge_arr;
}   

void * sort_thr(void *arg){
    struct ParamThread* param_thread = (struct ParamThread*)arg;

    clock_t start, end;
    double cpu_time;

    qsort(param_thread->arr, param_thread->size, sizeof(int), compare);

    start = clock();

    end = clock();

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

    int size_params = 4;

    struct ParamThread params_thread[4] = {
        {arr1, size_arr_1, 1},
        {arr2, size_arr_2, 2},
        {arr3, size_arr_3, 3},
        {arr4, size_arr_4, 4},
    };


    if (pthread_barrier_init(&barrier, NULL, 5) != 0) {
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
    merge(params_thread);

    pthread_barrier_destroy(&barrier);

    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);

    return 0;
}
