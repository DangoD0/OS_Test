#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* fun1(void *arg)
{
    printf("This is first thread!\n");
    int *n = (int*)arg;
    int a = *n + 4;
    printf("%d + 4 is %d\n",*n,a);
}
void* fun2(void *arg)
{   
    printf("This is second thread!\n");
    char *c = (char *)arg;
    printf("character is %s\n",c);
}
int main(int argc,char **argv)
{
    pthread_t myThread1,myThread2;
    char* c = argv[1];
    int n = argv[2][0] - '0';
    pthread_create(&myThread1,NULL,fun1,(void *)&n);
    pthread_create(&myThread2,NULL,fun2,(void *)c);
    pthread_join(myThread1,NULL);
    pthread_join(myThread2,NULL);
    printf("Finish main process!");
}
