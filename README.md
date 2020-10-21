# Producers-Consumers-Problems
Solution for the multithreaded Producer Consumers problem using semaphores and mutexes. 

## Global Variables
#### cpBuffer
This is the buffer between the producer and the consumer. It's size is determined by BUFSIZE. We are using a relatively small buffer... only 10 entries... to make the problem interesting.

#### bufTop
The index of the next unused item in cpBuffer. As items are added, bufTop will increase. As items are removed, bufTop will decrease.

#### times_up
An integer that will get set to 1 when consumers and producers should stop consuming and producing.

#### n_full and n_empty
Counters to keep track of the number of times the buffer is full, and the number of times it is empty.

#### n_tot_prod and n_tot_cons
The total number of items produced and consumed.

#### trace
An integer flag to control how much output is produced. Turn trace on to get more. I've provided the capability of turning on trace when you compile by specifying the parameter -DTRACE when you compil


## Functions
#### void insert_item(int newVal)
A function to put it's argument into the shared buffer, using (and updating) bufTop. Asserts are used to make sure butTop is valid. This function also keeps track of the n_full and n_tot_prod statistics.

#### int remove_item()
A function to remove an item from the shared buffer, using (and updating) bufTop. Asserts are used to make sure butTop is valid. This function also keeps track of the n_empty and n_tot_cons statistics.

#### int main(int argc, char **argv)
The main function already does several things:
When we run our producers and consumers, we will force them to wait for some randomized time between productions or consumptions, but we want to control the average time. Therefore, we use two command line arguments to specify the number of micro-seconds (a micro-second is one-millionth of a second, so 100 microseconds is 0.0000001 seconds). The main function checks the command line arguments. If one or two command line arguments were specified, converts them from their character representation to an integer using the atoi() library function. If atoi() doesn't recognize the argument as a number, it will return 0, so we override 0, and make it 10. If nothing is specified, the default is 100.
You will need to start the producer and consumer threads, passing into these threads prodWait and consWait arguments.
The main function then sleeps for 5 seconds to allow producers and consumers to run. After 5 seconds, main sets the times_up flag to 1 to tell the producer and consumer that they should exit.
You will need to figure out how to close and clean up after the producer and consumer.
Finally, main prints statistics and exits.

#### void* producer(* args)
The producer function should print a "starting up" message, perform any initializations and start up required, including saving the parameter, an integer that defines wait times between productions. Then the producer should loop while times_up is 0. The body of the loop needs to do the following:

Produce a new item. For this demonstration, the new item can be a random number between 0 and 100. In C, you can get this using item=rand()%100;
1. Make sure there is room in the buffer to insert this item.
2. Obtain a lock for the producer critical section.
3. Invoke the insert_item function provided.
4. Release the critical section lock.
5. Tell the consumer that there is another space used in the buffer.
6. Calculate a random wait time based on the parameter. To make the random wait time on average the value specified by the parameter, we can choose a random number between 0 and twice the value of the wait time parameter. If the wait time parameter is in variable waittime, this can be done with the C code int sleeptime=rand()%(2*waittime);
7. Sleep for the number of milliseconds in sleeptime. This can be done by usleep(sleeptime);

At the end of the loop perform any cleanup required, print a leaving message, and exit.

#### void* consumer(* args)
Much like the producer function, the consumer function should print a "starting up" message, perform any initializations and start up required, including saving the parameter, an integer that defines wait times between consumptions. Then the consumer should loop while times_up is 0. The body of the loop needs to do the following:

1. Make sure there is data in the buffer to consume.
2. Obtain a lock for the producer critical section.
3. Invoke the remove_item function provided.
4. Release the critical section lock.
5. Tell the producer that there is another space available in the buffer.
6. Calculate a random wait time based on the parameter. To make the random wait time on average the value specified by the parameter, we can choose a random number between 0 and twice the value of the wait time parameter. If the wait time parameter is in variable waittime, this can be done with the C code int sleeptime=rand()%(2*waittime);
7. Sleep for the number of milliseconds in sleeptime. This can be done by usleep(sleeptime);

At the end of the loop perform any cleanup required, print a leaving message, and exit.

## Makefile
There is provided a Makefile with several targets

#### test
Runs the prodcons program three times with different command line parameters.

#### checkMem
Runs the prodcons program under the valgrind program to check for memory leaks, etc.

#### prodcons
Builds the prodcon program. (This is not an explicit target, but will work.)

#### prodcons_Trace
Builds the prodcons program with tracing turned on.

#### clean
Removes the files that Makefile created
