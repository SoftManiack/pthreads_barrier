#define _POSIX_C_SOURCE 200112L // включение функций из POSIX (pthread_barrier_t, pthread_spinlock_t)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_barrier_t barrier_t;

int arg[20] = {};
int arr1[10] = {2,5,5,1,5,100,9,11,0,11};
int arr2[10] = {82,28,8,1,5,8,189,180,58,11};

// Структура барьераW

void * sort_thr_fn(){

}

int compare_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void merge(){

}   

int main(){


    // создать массив чисел для сортировки

    //pthread_barrier_wait();

    qsort(arr1, sizeof(arr1) / sizeof(arr1[0]), sizeof(int), compare_int);
    qsort(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), compare_int);

    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    return 0;
    
}
