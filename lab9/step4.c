#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    char cpy[strlen(argv[1])+1];
    cpy[0] = 'n';
    strcat(cpy,argv[1]);
    int size = atoi(argv[2]);
    char buffer[size];
    FILE *fp, *fp2;
    fp = fopen(argv[1], "rb");
    fp2 = fopen(cpy, "wb");
    while (fread(buffer, sizeof(buffer), 1, fp)){
        fwrite(buffer,sizeof(buffer),1,fp2);
    }
    fclose(fp);
    fclose(fp2);
}