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

struct ParamThread* params;
int size_params;
int* merge_arr_indexes;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int random(int min, int max){
    return min + rand() % ( max - min + 1);                                                             
}

int search_new_min_num(struct ParamThread* params){
    
    int new_min = params[0].arr[merge_arr_indexes[0]];
    for(int i = 0; i < size_params; i++){
        if(params[i].arr[merge_arr_indexes[i]] < new_min ){
            new_min = params[i].arr[merge_arr_indexes[i]];
        }
    }
    
    return new_min;
}

int* merge(struct ParamThread* params)
{
    
    int merge_size = 0;
    int max_size = params[0].size;
    int* merge_arr;

    // создание merge_arr_indexes тут хранится index min наченияя каждого массива
    merge_arr_indexes = malloc(size_params * sizeof(int));

    printf("size_params: %d\n", size_params);
    printf("max_size: %d\n", max_size);

    for(int i = 0; i < size_params; i++){
        merge_arr_indexes[i] = 0;
    }

    // создание merge_arr куда сольются все значения из массивов
    for(int i = 0; i < size_params; i++){
        merge_size += params[i].size;
    }   
    
    merge_arr = malloc(merge_size * sizeof(int));

    // получить длинну саммог большого массива
    for(int i = 0; i < size_params; i++){

        if(params[i].size > max_size){
            max_size = params[i].size;
        }
    }

    // вывод длинны масссива и всех кго значений

    for(int i = 0; i < size_params; i++){

        printf(" Массив %d размер %d\n", i, params[i].size);

        for(int j = 0; j < params[i].size; j++){
            printf("%d ,", params[i].arr[j]);
        }

        printf("\n");
    }   

    // max_size

    printf("max_size: %d\n", max_size );

    // вывод merge_arr

    // вывод merger_arr_indexes

    printf("merge_arr_indexes: %d\n", merge_arr_indexes[0]);
    printf("merge_arr_indexes: %d\n", merge_arr_indexes[1]);
    printf("merge_arr_indexes: %d\n", merge_arr_indexes[2]);
    printf("merge_arr_indexes: %d\n", merge_arr_indexes[3]);

    // вывод min

    int min_num = search_new_min_num(params);

    int merge_arr_index = 0;


    printf("min_num: %d\n", min_num);

    printf("слитый массив\n");
    for(int i = 0; i < merge_size; i++){
        printf("%d, ", merge_arr[i]);
    }

    printf("\n");

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

    int size_arr_1 = random(1,4);
    int size_arr_2 = random(1,4);
    int size_arr_3 = random(1,4);
    int size_arr_4 = random(1,4);

    int* arr1 = malloc(size_arr_1  * sizeof(int));
    if (arr1 == NULL) {
        printf("Ошибка выделения памяти!\n");
        return -1;
    }

    int* arr2 = malloc(size_arr_2  * sizeof(int));
    int* arr3 = malloc(size_arr_3  * sizeof(int));
    int* arr4 = malloc(size_arr_4  * sizeof(int));

    for(int i = 0; i < size_arr_1; i++) arr1[i] = random(2,6);
    for(int i = 0; i < size_arr_2; i++) arr2[i] = random(1,3);
    for(int i = 0; i < size_arr_3; i++) arr3[i] = random(1,3);
    for(int i = 0; i < size_arr_4; i++) arr4[i] = random(1,5);

    size_params = 4;

    
    for(int i = 0; i < size_arr_1; i++){
        printf("элемент массива 1: %d\n", arr1[i]);
    }

    for(int i = 0; i < size_arr_2; i++){
        printf("элемент массива 2: %d\n", arr2[i]);
    }

    for(int i = 0; i < size_arr_3; i++){
        printf("элемент массива 3: %d\n", arr3[i]);
    }

    for(int i = 0; i < size_arr_4; i++){
        printf("элемент массива 4: %d\n", arr4[i]);
    }

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
