//Jack Edwards
//CSCI 3000
//4-1-18
//Producer Consumer

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int const BUFFER_SIZE = 10;
int* buffer;

//number of integers to write to the buffer, give by the user
int x;

//number of intergers that have been written to the buffer
int numsInBuffer; 


sem_t mutex;

//sizeOfNullTerminatedString(S) returns the size of null terminated string S.
int sizeOfNullTerminatedString(const char* S){
	int size = 0;
	while(S[size] != '\0'){
		size++;	
	}
	return size;
}

//charArrayToInt(numbers) returns string numbers as an integer.
int charArrayToInt(const char* numbers){
	int n = 0;
	int place = 1;
	
    int i = sizeOfNullTerminatedString(numbers) - 1;
	
	while(numbers[i] != '\0'){
		n += (numbers[i] - (int) '0') * place; 
		place = place * 10;		
		i--;
	}
    return n;
}

//produce() writes random nuumbers to the buffer. 
//The random numbers are also written to a file named
//production.
void* produce(){	
	FILE *f;
	f = fopen("production", "w+");
   
	while(x > 0){

		sem_wait(&mutex);

		int i;
		int n;
		for(i = 0; i < BUFFER_SIZE && x > 0; i++){
			n = rand() % 100 + 1;
			buffer[i] = n;
			printf("Producer: %d\n", n);
			fprintf(f, "%d\n", n);
			x--;
		}
        numsInBuffer = i;

		sem_post(&mutex);

		sleep(1);
	}

	pthread_exit(0);
	
}

//consume() reads random nuumbers to the buffer. 
//The random numbers and their swuare are also written 
//to a file named cunsumption.
void* consume(){
	FILE *f;
	f = fopen("consumption", "w+");
    
    int true = 1;    
    
	while(true){
		sem_wait(&mutex);

		int i;
		int n;
		for(i = 0; i < numsInBuffer; i++){
			n = buffer[i];
			printf("Consumer: %d, %d\n", n, n * n);
			fprintf(f, "%d, %d\n", n, n * n);
		}

		sem_post(&mutex);
        if(x == 0){
            break;
        }
		sleep(1);
	}
	
	pthread_exit(0);
   
}


int main(int argc, const char** argv){

	buffer = (int *)malloc(sizeof(int)*BUFFER_SIZE);
	
	sem_init(&mutex, 1, 1);
	
	if(argc == 2){
		x = charArrayToInt(argv[1]);
		printf("x is: %d\n", x);

        //make threads
        pthread_attr_t tattr;
        pthread_t tid[2];

        pthread_attr_init (&tattr);
        pthread_attr_setscope (&tattr, PTHREAD_SCOPE_SYSTEM);
        
        srand(time(0));

        pthread_create(&tid[0], &tattr, produce, NULL);
		pthread_create(&tid[1], &tattr, consume, NULL);
	       
        
        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);
        printf("Threads joining\n");
	}else{
		printf("ERROR no argument given.\n");
	}
	
	return 0;
}
