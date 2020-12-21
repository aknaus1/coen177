#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define someNumber 10000
#define capNumber 100


int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer [sizeof(int)];
    int i;
    fp = fopen("testInput.txt", "w");
    srand(time(NULL));
    for (i=0; i<someNumber; i++) {
        sprintf(buffer, "%d\n", rand()%capNumber);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}