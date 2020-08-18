/*


Jack Pharies 
pi2.c

to compile type:
	gcc pi2.c -lpthread
to run type:
	./outputFile numberOfThreads numberOfThrows

where outputFile is the name of your output file
		numberOfThreads is the number of threads you need
		and numberOFThrows is the ammount of darts you want thrown

Note: after testing it seems that at least 10,000,000 throws tends to get the most accurate results


the program is made so that only the first 3 decimals are printed out. That can be changed if needed.
To change this go to the approximate function and edit the print statement.




*/



#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h> 


void *threadThrow(void *threadid);
void throw(long id);
void approximate();

int total = 0;
int missTotal = 0;

int numThreads;
int numThrows;
int throwsPerThread;


int *hits;
int *misses;



 int main(int argc, char *argv[]) 
 {

 	numThreads = atoi(argv[1]);
 	numThrows = atoi(argv[2]);

 	if (!(numThrows % numThreads == 0))
 	{
 		exit(0);
 	}

 	throwsPerThread = numThrows / numThreads;

 	//printf("%d\n", throwsPerThread);
 	long t;


 	int hitPlace[numThreads];
 	int missPlace[numThreads];
 	hits = hitPlace;
 	misses = missPlace;


 	for(t=0; t<numThreads; t++)
 	{       
 		hits[t] = 0;
 		misses[t] = 0;
 	}


 	
 	pthread_t threads[numThreads];    
 	int rc;    
 	srand ( time ( NULL));
 	int i;


 	for(t=0; t<numThreads; t++)
 	{       
 		//printf("In main: creating thread %ld\n", t);       
 		rc = pthread_create(&threads[t], NULL, threadThrow, (void *)t);       
 		if (rc){         
 			 printf("ERROR; return code from pthread_create() is %d\n", rc);          
 			 exit(1);       
 			 }   
 		
 		
 	}

 	for(t=0; t<numThreads; t++)
 	{     
 		pthread_join(threads[t], NULL);  
 		total = total + hits[t];
 		//missTotal = missTotal + misses[t];
 	}
       
 	approximate();
 	//printf("%d, %d, %d\n", total , missTotal, total + missTotal);

 	// needs to be last thing
 	pthread_exit(NULL); 



 }



// "throws" the dart and checks if its misses or hits based on formula given
// randomizes two numbers between -1 and 1 as x and y
 void throw(long id)
 {

	
	float x = (double)rand()/RAND_MAX*2.0-1.0;
	float y = (double)rand()/RAND_MAX*2.0-1.0;


	float result = (x*x) + (y*y);
	

	if ( result <= 1)
	{
		hits[id] = hits[id] + 1;
	}
	else
	{
		misses[id] = misses[id] + 1;
	}

 }

// approximates the value of pi based on the following formula:
// 4 * (number of hits / number of darts thrown)
 void approximate()
 {

 	double piGuess = (double)4 * ((double)total / (double)numThrows);
 	printf("The approximation of %d throws is %.3f\n", numThrows ,piGuess);



 }




//function for the threads in order for them to throw the darts
// calls the throw method
 void *threadThrow(void *idnum)
 {

 	long id = (long) idnum;
 	int i;
 	for(i = 0; i < throwsPerThread; i++)
 	{
 	 	throw(id);

 	} 

 	//printf("Thread %ld done\n", id);

 }





