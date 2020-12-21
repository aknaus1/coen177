#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int pageno;
    int age;
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

//Returns index of first empty space
//If no empty space is found, returns index of oldest page
int findPlace(int placeInArray, ref_page cache[], int cacheSize) {
    int maxAge = -1, index = -1;

    for(int i = 0; i < cacheSize; i++) {
        if(cache[i].age == -1) {
            return i;
        } else if(cache[i].age > maxAge) {
            index = i;
            maxAge = cache[i].age;
        }
    }
    return index;
}

int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[10000]; // Cache that holds the input from test file

    int i;
    int totalRequests = 0;
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < C_SIZE; i++){ //initialise cache array  
         cache[i].pageno = -1;
         cache[i].age = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int

        //If index has item increase age
        for(int i = 0; i < C_SIZE; i++) {
            if(cache[i].age != -1)
                cache[i].age++;
        }

        int x = indexOfItem(page_num, cache, C_SIZE);

        if(x == -1) { //If not found in cache
            int placeInArray = findPlace(placeInArray, cache, C_SIZE);
            cache[placeInArray].pageno = page_num;
            cache[placeInArray].age = 0;
            totalFaults++;
        } else {
            cache[x].age = 0;
        }
        totalRequests++;
    }

    printf("%d - LRU\n", C_SIZE);
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
