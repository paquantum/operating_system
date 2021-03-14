#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int sum = 0; // a shared variable

sem_t sem;

void *counter(void *param) {
    int k;
    for (k = 0; k < 10000; k++) {
        // entry section
        sem_wait(&sem);

        // critical section
        sum += 1;

        // exit section
        sem_post(&sem);

        // remainder section
    }
    pthread_exit(0);
}

int main()
{
    pthread_t tid[5]; int i;
    sem_init(&sem, 0, 5);
    /* 5개인경우 5만이 아님 4만 때의 숫자가 나옴
    열쇠가 5개고 프로세스가 5개로 race condition발생으로
    mutex가 되지 않음 5를 1로 바꿔서(열쇠가 1개처럼) 하면 5만 잘 나옴
    */
    for (i = 0; i < 5; i++)
        pthread_create(&tid[i], NULL, counter, NULL);
    for (i = 0; i < 5; i++)
        pthread_join(tid[i], NULL);
    printf("sum = %d\n", sum);

    return 0;
}