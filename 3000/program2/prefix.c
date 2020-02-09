//Jack Edwards

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int* numbers;
int* newNums;
pthread_barrier_t barrier;
int size;
int* dist;

//pthread
//pthreadjoin
//pthreadbarrier

int fileSize(const char* filename){
    FILE* f = fopen(filename, "r");    
    int size = 0;
    int i = 0;
    if(f == NULL){
        printf("File could not be opened.");
        exit(0);
    }else{
        
        while(!feof(f)){
            if(fscanf(f, "%d", &i) == 1){
                size++;
            }
        }
        fclose(f);
    }
    return size;

}

int* fileToArray(const char* filename, int size){
    int* numbers = (int *)malloc(sizeof(int)*size);
    FILE* f = fopen(filename, "r");

    if(f == NULL){
        printf("File could not be opened.");
        free(numbers);
        exit(0);
    }else{
        int i = 0;
        int num = 0;
        while(!feof(f)){
            if(fscanf(f, "%d", &num) == 1){
                numbers[i] = num;
                i++;
            }
        }
        fclose(f);
        return numbers;
    }
}

void printIntArray(int* A, int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%i\n", A[i]);  
    }

}

//copy array A into array B.
void arrayCopy(int* A, int* B, int size){
    int i;
    for(i = 0; i < size; i++){
        B[i] = A[i];
    }
}

void* computePrefix(void* index){
    int i = (int)index;
	if(ceil(log2(dist[0])) == i){
		newNums[i] = numbers[i];
	}else if(i - dist[0] >= 0){
        newNums[i] = numbers[i - dist[0]] + numbers[i];
	
	}else{
		
	}
	//pthread_barrier_wait(&barrier);
    pthread_exit(NULL);
        
        
//pthread_barrier_wait(&barrier);
    
}


int main(int argc, const char** argv){
    if(argc > 1){
        
        const char* filename = argv[1];
        size = fileSize(filename);
        numbers = fileToArray(filename, size);
        newNums = (int *)malloc(sizeof(int)*size);

        printIntArray(numbers, size);
        //make threads
        pthread_attr_t tattr;
        pthread_t tid[size];

        pthread_attr_init (&tattr);
        pthread_attr_setscope (&tattr, PTHREAD_SCOPE_SYSTEM);

        pthread_barrier_init(&barrier, NULL, size + 1);        
        
		void** ptr;
		
        int i;
        int j;
		//int d = 1;
        dist = (int*)malloc(sizeof(int));
		dist[0] = 1;
        for(i = 0; i < ceil(log2(size)); i++){
            for(j = 0; j < size; j++){
                pthread_create(&tid[j], &tattr, computePrefix, (void*)j);
				
			    //pthread_barrier_wait(&barrier);
            }
			
			int k;
			for(k = 0; k < size; k++){
				pthread_join(tid[k], NULL);
			}
			
			dist[0] = dist[0] * 2;
            //pthread_barrier_wait(&barrier);
			arrayCopy(newNums, numbers, size);
			printf("Round %i, The array contains:\n", i);
			printIntArray(numbers, size);
			printf("\n");
        }
		
		printf("The final answer is: %i\n", numbers[size - 1]);
		
    }

}














