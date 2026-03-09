#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t count_cond = PTHREAD_COND_INITIALIZER;

void *thread1_run(void *arg)
{
    (void)arg;

    while (count < 5) {
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Thread 1, count is %d\n", count);
        pthread_cond_signal(&count_cond);
        pthread_mutex_unlock(&count_mutex);
        sleep(1);
    }

    return NULL;
}

void *thread2_run(void *arg)
{
    (void)arg;
    

    while (1) {
        pthread_mutex_lock(&count_mutex);
        pthread_cond_wait(&count_cond, &count_mutex);
        printf("Thread 2, count is %d\n", count);
        pthread_mutex_unlock(&count_mutex);
        if (count >= 5){
            break;    
        }
  
    }

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1_run, NULL);
    pthread_create(&t2, NULL, thread2_run, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}

// with sleep 3 it will sometimes not reconz=ize thread 2 untill count 4 and 5