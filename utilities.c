#include "utilities.h"
//creazione array char per stampare nomi fermate
char s[]="STAZIONE";
char c[]="CENTRO";
char p[9];




//funzioni di lock e unlock per i mutex
void Lock(pthread_mutex_t *mtx){
    if (pthread_mutex_lock(mtx) != 0){
        perror("lock");
        exit(EXIT_FAILURE);
    }
}

void Unlock(pthread_mutex_t *mtx){
    if (pthread_mutex_unlock(mtx) != 0){
        perror("unlock");
        exit(EXIT_FAILURE);
    }
}

