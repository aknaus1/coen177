#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// #define cacheSize 10
// #define CACHE_SIZE cacheSize

typedef struct {//to 
    int pageno;
    int bit;
} ref_page;

// ref_page cache[cacheSize]; // Cache that stores pages
// char pageCache[100]; // Cache that holds the input from test file
// int totalFaults = 0; // keeps track of the total page faults

//If bit is 0 it switches to 1
//If bit is 1 it switches to 0
int switchBit(int x) {
    if(x == 1)
        return 0;
    else
        return 1;
}

//If item is found in cache, returns the index
//Returns -1 if not found
int indexOfItem(int page_num, ref_page cache[], int cacheSize) {
    for(int i = 0; i < cacheSize; i++) {
        if(cache[i].pageno == page_num)
            return i;
    }
    return -1;
}

int findPlace(int placeInArray, ref_page cache[], int cacheSize) {
    int x = placeInArray;
    for(int i = placeInArray; i < cacheSize; i++) {
        if(cache[i].bit == 0)
            return i;
    }
    for(int i = 0; i < placeInArray; i++) {
        if(cache[i].bit == 0) {
            return i;
        }
    }
    return cacheSize - 1;
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
    char pageCache[100]; // Cache that holds the input from test file
    int placeInArray = 0;


    int i;
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int

        int x = indexOfItem(page_num, cache, C_SIZE);

        if(x == -1) {
            placeInArray = findPlace(placeInArray, cache, C_SIZE);
            cache[placeInArray].pageno = page_num;
            totalFaults++;
            placeInArray = incrementPlace(placeInArray, C_SIZE);
        } else {
            cache[x].bit = switchBit(cache[x].bit);
            placeInArray = incrementPlace(x, C_SIZE);
        }
    }

    printf("%d Total Page Faults", totalFaults);
    return 0;



}
