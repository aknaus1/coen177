#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int pageno;
} ref_page;

//If item is found in cache, returns the index
//Returns -1 if not found
int indexOfItem(int page_num, ref_page cache[], int cacheSize) {
    for(int i = 0; i < cacheSize; i++) {
        if(cache[i].pageno == page_num) //If found in cache
            return i;
    }
    return -1;
}

int incrementPlace(int index, int cacheSize) {
    if(index + 1 == cacheSize)
        return 0;
    else 
        return index + 1;
}


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[10000]; // Cache that holds the input from test file
    int placeInArray = 0;

    int i;
    int totalRequests = 0;
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int

        if(indexOfItem(page_num, cache, C_SIZE) == -1) { //If not found in cache
            cache[placeInArray].pageno = page_num;
            totalFaults++;
            placeInArray = incrementPlace(placeInArray, C_SIZE);
        }
        totalRequests++;
    }

    printf("%d - FIFO\n", C_SIZE);
    printf("numMisses: %d\n", totalFaults);
    printf("numRequests: %d\n", totalRequests);
    double numMisses = totalFaults;
    double numRequests = totalRequests;
    double missRate = numMisses / numRequests;
    double hitRate = 1 - missRate;
    printf("Hit Rate = %f\n", hitRate);
    printf("\n");
    return totalFaults;
}
