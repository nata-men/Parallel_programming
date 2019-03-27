#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void *heavy_task(void *i) {

int thread_num = *((int*) i);

printf("\tThread #%d started\n", thread_num);


pthread_mutex_lock(&mutex);
printf("\t\tThread #%d acquired mutex\n", thread_num);

counter++;
printf("\t\t\tThread #%d, counter: %d\n", thread_num, counter);

printf("\t\tThread #%d released mutex\n", thread_num);
pthread_mutex_unlock(&mutex);

int result = 0;

for (int i = 0; i < 1e8; i++) {
result += i;

}

printf("\tThread #%d finished\n", thread_num);

free(i);
return 0;
}


void pthreads(int threads_num) {

pthread_t threads[threads_num];
int status;

for (int i = 0; i < threads_num; i++) {

printf("MAIN: starting thread %d\n", i);

int *thread_num = (int*) malloc(sizeof(int));
*thread_num = i;

status = pthread_create(&threads[i], NULL, heavy_task, thread_num);

if (status != 0) {
fprintf(stderr, "pthread_create failed, error code %d\n", status);
exit(EXIT_FAILURE);
}
}

for (int i = 0; i < threads_num; i++) {
pthread_join(threads[i], NULL);
}
}


int main(int argc, char** argv) {

int threads_num = atoi(argv[1]);

pthreads(threads_num);

pthread_mutex_destroy(&mutex);

return 0;
}
