#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>



//definizione variabili mutex
pthread_mutex_t mtx;
pthread_cond_t AT;
pthread_cond_t viaggio;
pthread_cond_t A;
//definizioni funzioni lock e unlock
void Lock(pthread_mutex_t *mtx);
void Unlock(pthread_mutex_t *mtx);
//definizioni funzioni turista e cabina
void *Turista(void *arg);
void *Cabina(void *arg);



