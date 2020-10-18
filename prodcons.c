#include <stdio.h>
#include <stdlib.h> // for rand
#include <unistd.h> // for usleep
#include <assert.h>

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

/* Function Declarations
-----------------------------------------------------------------------------*/
void insert_item(int newVal); // Push new value onto cpBuffer
int remove_item(); // Retrieve and return value from cpBuffer


/* Main function
-----------------------------------------------------------------------------*/
int main(int argc,char **argv) {

#ifdef TRACE
	trace=1;
#endif

	int prodWait=100;
	int consWait=100;
	if (argc>1) prodWait=atoi(argv[1]);
	if (argc>2) consWait=atoi(argv[2]);
	if (prodWait==0) prodWait=10;
	if (consWait==0) consWait=10;


	/* TODO: Start producer and consumer */

	/* Sleep long enough to see what happens*/
	sleep(5); // wait for 5 seconds
	times_up=1; // Tell producer and consumer that time is up

	/* TODO: close/clean up after producer and consumer */

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
void producer(void){
	int item;
	while(TRUE){
		item = 
	}
}





/* consumer function 
-----------------------------------------------------------------------------*/



















