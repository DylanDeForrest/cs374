#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int val = 6;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread1_run(void *arg)
{
    (void)arg;

    pthread_mutex_lock(&mutex);
    while (val > 3)
        pthread_cond_wait(&cond, &mutex);
    printf("Half way there!\n");
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *thread2_run(void *arg)
{
    (void)arg;

    pthread_mutex_lock(&mutex);
    while (val > 0)
        pthread_cond_wait(&cond, &mutex);
    printf("Liftoff!\n");
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1_run, NULL);
    pthread_create(&t2, NULL, thread2_run, NULL);

    while (val > 0) {
        pthread_mutex_lock(&mutex);
        val--;
        printf("%d\n", val);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}