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
        int counter_line = 0;
        while (getline(&eachline, &len, csv_text) != -1){
            char* token = NULL;
            //printf("%s\n", token);
            int counter_col = 0;
            // have to check each token, it just takes away all the blanks for some reason
            // I used strsep because it can also take in zero-string lengths
            while ((token = strsep(&eachline, ","))!= NULL) {
                //trying to print out name
                if (counter_line == 0 && counter_col == 8) {
                    printf("%s\n", token); 
                }
                if (counter_line > 0 && counter_col == 8) {
                    printf("%s\n", token); 
                }
                token = strtok(NULL, ",");
                counter_col++; 
            }
            //printf("%s\n", token);
            //printf("%s\n",eachline);
            counter_line++;
        }
    }
    

    return 0;
}

//"cl-tweets-short-clean.csv"