#include <stdio.h>
#include <stdlib.h> // for rand
#include <unistd.h> // for usleep
#include <assert.h>
#include <semaphore.h> // for semaphores used and avail
#include <pthread.h>// pthread lib for creating threads and mutex

/* Global variables,
-----------------------------------------------------------------------------*/
#define BUFSIZE 10
int cpBuffer[BUFSIZE];
int bufTop=0; // Pointer to the next unused entry in cpBuffer
volatile int times_up=0;
int n_full=0; // Count the number of times the buffer is full
int n_empty=0; // Count the number of times the buffer is empty
int n_tot_cons=0; // Count the total number of items consumed
int n_tot_prod=0; // Count the total number of items produced
int trace=0; // provide more detailed information if 1

// declarations for semaphores and mutexes
sem_t avail;
sem_t used;
pthread_mutex_t mutex;


/* Function Declarations
-----------------------------------------------------------------------------*/
void insert_item(int newVal); // Push new value onto cpBuffer
int remove_item(); // Retrieve and return value from cpBuffer
void* producer(void* args); // declaring producer function 
void* consumer(void* args);// declaring consumer function


/* Main function
-----------------------------------------------------------------------------*/
int main(int argc,char **argv) {

#ifdef TRACE
	trace=1;
#endif
	
	//buffer
	setbuf(stdout, 0);
	setbuf(stderr, 0);
	
	// pregiven stuff
	int prodWait=100;
	int consWait=100;
	if (argc>1) prodWait=atoi(argv[1]);
	if (argc>2) consWait=atoi(argv[2]);
	if (prodWait==0) prodWait=10;
	if (consWait==0) consWait=10;


	/* TODO: Start producer and consumer */
	// thread declarations
	pthread_t prod, cons;
	int waittime = 100;
	pthread_mutex_init(&mutex, NULL);
	sem_init(&avail, 0, BUFSIZE);
	sem_init(&used, 0, 0);
	
	//start producer and consumer threads
	pthread_create(&prod, NULL, producer, &waittime);
	pthread_create(&cons, NULL, consumer, &waittime);
	

	/* Sleep long enough to see what happens*/
	sleep(5); // wait for 5 seconds
	times_up=1; // Tell producer and consumer that time is up

	/* TODO: close/clean up after producer and consumer */
	pthread_join(prod,NULL); //closing up threads
	pthread_join(cons,NULL); //closing up threads
	
	pthread_mutex_destroy(&mutex); //clean up the mutex
	sem_destroy(&avail);// clean up available sempaphore
	sem_destroy(&used);//clean up used semaphore

	printf("Produced a total of %d items and consumed %d items\n",n_tot_prod,n_tot_cons);
	printf("Buffer was empty %d times, and full %d times\n",n_empty,n_full);
	return 0; // Everything worked
}

/* insert_item function
-----------------------------------------------------------------------------*/
void insert_item(int newVal) {
	assert(bufTop>=0);
	assert(bufTop<BUFSIZE);
	cpBuffer[bufTop]=newVal;
	bufTop++;
	if (bufTop==BUFSIZE) {
		n_full++;
		if (trace) printf("^^^^^^^^^^^^^ BUFFER FULL\n");
	}
	n_tot_prod++;
	if (trace) printf("Produced item %d\n",newVal);
}

/* remove_item function
-----------------------------------------------------------------------------*/
int remove_item() {
	bufTop--;
	assert(bufTop>=0);
	assert(bufTop<BUFSIZE);
	if (bufTop==0) {
		n_empty++;
		if (trace) printf("vvvvvvvvvvvvv BUFFER EMPTY\n");
	}
	n_tot_cons++;
	if (trace) printf("Consumed item %d\n",cpBuffer[bufTop]);
	return cpBuffer[bufTop];
}

/* producer function
-----------------------------------------------------------------------------*/
void* producer(void* args){
	printf("Starting up Producer!\n");
	int waittime = *((int*)args);
	int item;
	int sleeptime;
	while(times_up == 0){
		item = rand()%100;
		sem_wait(&avail);
		//critical section start
		pthread_mutex_lock(&mutex);
		insert_item(item);
		pthread_mutex_unlock(&mutex);
		//critical section end
		sem_post(&used);
		//sleep for consuming process
		sleeptime = rand()%(2*waittime);
		usleep(sleeptime);
			
	}
	printf("Ending Producer!\n");
	return NULL;
}


/* consumer function 
-----------------------------------------------------------------------------*/
void* consumer(void* args){
	printf("Starting up Consumer!\n");
	int waittime = *((int*)args);
	int sleeptime;
	while(times_up == 0){
		sem_wait(&used);
		// critical section start
		pthread_mutex_lock(&mutex);
		remove_item();
		pthread_mutex_unlock(&mutex);
		//critical section end
		sem_post(&avail);
		//sleep for consuming process
		sleeptime = rand()%(2*waittime);
		usleep(sleeptime);
	}	
	
	printf("Ending Consumer!\n");
	return NULL;
}

















