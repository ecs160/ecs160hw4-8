#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//test
int main(int argc, char** argv){
    FILE *csv_text;
    char str[100];
    char *eachline = NULL;
    size_t len = 1000;
    ssize_t line_size;

    if (argc != 2){
        printf("Not Valid Input\n");
        exit(0);
    }

    if (argc == 2){
        csv_text = fopen(argv[1], "r");
        if (csv_text == NULL) {
            printf("Can't open file\n");
            exit(0);
        }
        while (getline(&eachline, &len, csv_text) != -1){
            printf("%s\n",eachline);
        }
    }
    

    return 0;
}

//"cl-tweets-short-clean.csv"