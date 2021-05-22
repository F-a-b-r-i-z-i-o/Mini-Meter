#include "utilities.c"

    /*FUNZIONAMENTO PROGRAMMA*/
    // .inizio alla stazione
    // .cabina in attesa della salita di 4 turisti
    // .e' presente un ciclo infinito in cui :
    // .una volta che la cabina si e' riempita parte. Recandosi alla fermata opposta
    // .dando il segnali di arrivo i turisti scendono e si svuota la cabina
    // .i turisti si rimettono in fila per salire sulla cabina
    // .qui la cabina in attesa aspetta la nuova salita dei turisti e riparte verso fermata da dove era partita
    // .la cabina parte sempre quando sono saliti esattamente 4 turisti



//varibili globali utilizzate successivamente nel programma.
//contatore dei turisti
//cabina per monitorare spostamento cabina
//array id

int cabina;
int contatore = 0;
int Tcabina[4];
    




//funzione per il controllo della cabina
void *Cabina(void *arg){
    //funzione di libreria che copia stringa da locazione all'altra
    //utilizzio questa funzione per far meno confusione sui print delle fermate e non star a riscrivere i nomi delle fermate.
    strcpy (p, s);
    strcpy (p, c);
    
    int id = (intptr_t)arg;

    //1 cabina e' in STAZIONE
    //0 cabina e' in CENTRO
    cabina = 1;
    printf("[CABINA] attende in stazione:\t %d\n", id);
    fflush(stdout);
    //ciclo infinto per spostamento cabina
    while (1){
        Lock(&mtx);

        //aggiornamento riempimento cabina
        while (contatore < 4){
            pthread_cond_wait(&AT, &mtx); 
            printf("[CABINA] posti in cabina: %d\n",contatore);
            fflush(stdout);
        }

        printf("CABINA:\n");
        for(int i = 0; i < 4; i++){
            printf("TURISTA [%d]\n", Tcabina[i]);
        }
        printf("[CABINA] posti occupati : %d su 4\n",contatore);
        fflush(stdout);
        //avviso spostamento cabina
        printf("[CABINA] PARTE...direzione...");
        if(cabina){
            printf("\t%s\n", c);
        } else{
            printf("\t%s.\n", s);
        }
        //invio del segnale ai turisti per la partenza
        pthread_cond_broadcast(&viaggio); 

        Unlock(&mtx);
        //durata del viaggio
        sleep(2);

        Lock(&mtx);
        //fine della corsa
        printf("[CABINA] FINE CORSA arrivo a destinazione:  ");
        //aggiornamento cabina e cambio della fermata per il prossimo viaggio
        if(cabina){
            printf("\t%s.\n", c);
            cabina = 0; 
        } else{
            printf("\t%s.\n", s);
            cabina = 1; 
        }
        printf("[CABINA]: scendere e lasciare liberi i posti per la prossima corsa.\n\n");
        fflush(stdout);
        //avvisa di arrivo a destinazione facendo cosi' scendere i turisti
        pthread_cond_broadcast(&A); 
        //resetto l'array id
        for(int i = 0; i < 4; i++){
            Tcabina[i] = -1;
        }
        //svuoto cabina
        contatore = 0;
        printf("SVUOTAMENTO [CABINA]\n");
        printf("POSTI ATTUAlMENTE OCCUPATI %d\n", contatore);

        fflush(stdout);
        
        Unlock(&mtx);
    }
    pthread_exit(NULL);
    return NULL;
}
//funzione per il controllo dei turisti
void *Turista(void *arg){
    //funzione di libreria che copia stringa da locazione all'altra
    //utilizzio questa funzione per far meno confusione sui print delle fermate e non star a riscrivere i nomi delle fermate.
    strcpy (p, s);
    strcpy (p, c);
    int id = (intptr_t)arg;
    //1 cabina e' in STAZIONE
    //0 cabina e' in CENTRO
    int turista;

    //1 salita cabina
    //0 fuori cabina
    int salita = 0;

    //inizializzazione dei turisti, 4 alla stazione e 1 in centro
    if(id < 4){
        turista = 1;
    } else{
        turista = 0;
    }
    
    //situazione iniziale dei turisti
    printf("[TURISTA %d] attende cabina per: ", id);
    //controlli per i turisti in base ad i posti e a dove sono.
    if(turista){
        printf("\t%s\n", c);
    } else{
        printf("\t%s\n", s);
    }
    if(turista == 0){
        printf("[TURISTA %d] resta fuori, POSTI TERMINATI\n", id);
    }
    fflush(stdout);
    //ciclo infinito di salita dei turisti
    while (1){
        Lock(&mtx);

        //controllo se la cabina e' alla stessa fermata del turista, se non lo è si mette in attesa ed esegue l'unlock del mutex
        if (turista != cabina){
            Unlock(&mtx);
            sleep(4);
        }
        //la cabina si trova nella stessa fermata del turista
        //controllo per verificare se c'e' posto dentro la cabina per salire
        else{ 
            if (contatore < 4){
                if(Tcabina[contatore] < 0){ 
                    printf("[TURISTA %d]  sale nella cabina\n", id);
                    //inserisco l'id del turista all'interno dell'array in una posizione vuota
                    Tcabina[contatore] = id;
                    ++contatore;
                    salita = 1;
                    //avverte la cabina che è entrato il turista e incomincia riempimento della cabina
                    pthread_cond_signal(&AT); 
                }
            }
            if(salita){
                //aspetta segnale della partenza della cabina
                pthread_cond_wait(&viaggio, &mtx); 
                printf("[TURISTA %d] viaggia verso ", id);
                if(turista){
                    printf("\t%s\n", c);
                } else{
                    printf("\t%s\n", s);
                }
                fflush(stdout); 
                //appena arriva il segnale il turista inizia a scendere   
                pthread_cond_wait(&A, &mtx); 
                printf("[TURISTA %d] scendo dalla cabina ", id);
                if(turista){
                    printf("in centro \n");
                } else{
                    printf("alla stazione \n");
                }
                fflush(stdout);
                Unlock(&mtx);
                //fa un giro di due secondi e si rimette in fila
                sleep(2);
                Lock(&mtx);
                printf("[TURISTA %d] vado a prendere una birra e mi rimetto in fila per la prossima corsa\n", id); 
                fflush(stdout);
                //cambio la destinazione del turista
                if(turista){
                    turista = 0;
                } else{
                    turista = 1;
                }
                //il turista fuori cabina
                salita = 0; 
                Unlock(&mtx);
                printf("\n");
            } else{
                sleep(3);
                Unlock(&mtx);
                }
        }
        sleep(3);
    }
    pthread_exit(NULL);
    return NULL;
}

int main(void){
    //inizializzazione array 
    //inizializzazione variabili dei thread e mutex
    //creazione thread
    int i = 0;
    for(; i < 4; i++){
        Tcabina[i] = -1;
    }
    pthread_t threads;
    contatore = 0;
    if (pthread_cond_init(&A, NULL) != 0){
        fprintf(stderr, "pthread_cond_init fallita\n");
        exit(EXIT_FAILURE);
    }
    if (pthread_cond_init(&viaggio, NULL) != 0){
        fprintf(stderr, "pthread_cond_init fallita\n");
        exit(EXIT_FAILURE);
    }
    if (pthread_mutex_init(&mtx, NULL) != 0){
        fprintf(stderr, "pthread_mutex_init fallita\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_cond_init(&AT, NULL) != 0){
        fprintf(stderr, "pthread_cond_init fallita\n");
        exit(EXIT_FAILURE);
    }
 
    for (int i=0; i < 5; i++){
        if (pthread_create(&threads, NULL, Turista, (void *)(intptr_t)i) != 0){
            fprintf(stderr, "pthread_create failed\n");
            exit(EXIT_FAILURE);
        }
    }
    if (pthread_create(&threads, NULL, Cabina, (void *)(intptr_t)0) != 0){
        fprintf(stderr, "pthread_create failed\n");
        exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);
    return 0;
}

