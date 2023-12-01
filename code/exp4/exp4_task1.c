#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int buf[2];
int in;
sem_t n;
sem_t rw[2];
sem_t c;

void r1(){

    FILE *fp = fopen("1.dat","r");
    while(1){
        sem_wait(&n);
        sem_wait(&rw[0]);

        fscanf(fp,"%d",&buf[in]);
        if(in == 1) sem_post(&c);
        in = (in + 1) % 2;
        sem_post(&rw[0]);

        char c11 = fgetc(fp);
        if(c11=='\n' || c11==EOF) break;
    }

}

void r2(){

    FILE *fp = fopen("2.dat","r");
    while(1){
        sem_wait(&n);
        sem_wait(&rw[0]);

        fscanf(fp,"%d",&buf[in]);
        if(in == 1) sem_post(&c);
        in = (in + 1) % 2;
        sem_post(&rw[0]);

        char c11 = fgetc(fp);
        if(c11=='\n' || c11==EOF) break;
    }

}

void w1(){

    while(1)
    {
        sem_wait(&rw[1]);

        sem_wait(&c);
        printf("Plus:%d+%d=%d\n",buf[0],buf[1],buf[0]+buf[1]);

        sem_post(&n);
        sem_post(&n);

        sem_post(&rw[1]);

    }
}

void w2(){

    while(1)
    {
        sem_wait(&rw[1]);

        sem_wait(&c);
        printf("Multi:%d*%d=%d\n",buf[0],buf[1],buf[0]*buf[1]);

        sem_post(&n);
        sem_post(&n);

        sem_post(&rw[1]);
    }
}

int main(){
    pthread_t id1, id2, id3, id4;
    int ret1, ret2, ret3, ret4;

    sem_init(&n, 0, 2);
    sem_init(&rw[0], 0, 1);
    sem_init(&rw[1], 0, 1);
    sem_init(&c,0,0);
    ret1 = pthread_create(&id1, NULL, (void *)r1, NULL);
    if(ret1){
        printf("ERROR:	failed to create thread r1!\n");
    }
    ret3 = pthread_create(&id3, NULL, (void *)w1, NULL);
    if(ret3){
        printf("ERROR:	failed to create thread w1!\n");
    }
    ret4 = pthread_create(&id4, NULL, (void *)w2, NULL);
    if(ret4){
        printf("ERROR:	failed to create thread w2!\n");
    }
    ret2 = pthread_create(&id2, NULL, (void *)r2, NULL);
    if(ret2){
        printf("ERROR:	failed to create thread r2!\n");
    }
    /*ret3 = pthread_create(&id3, NULL, (void *)w1, NULL);
    if(ret3){
        printf("ERROR:	failed to create thread w1!\n");
    }*/
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    pthread_join(id3, NULL);
    pthread_join(id4, NULL);

    return 0;
}





