#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//test
int main(int argc, char** argv){
    FILE *csv_text;
    char str[100];

    if (argc != 2){
        printf("Not Valid Input\n");
        return 0;
    }

    if (argc == 2){
        csv_text = fopen(argv[0], "r");
        char *column_text = strtok("hi", ",");
        printf(column_text);
        while (fgets(str, 100, csv_text) != NULL)
            printf("%s", str);
        fclose(csv_text);
    }
    printf("hello\n");

    return 0;
}

//"cl-tweets-short-clean.csv