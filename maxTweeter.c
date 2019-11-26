#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//test
struct count_tweeters{
        char* list_names[10];
        int count[10];
    };

int main(int argc, char** argv){
    FILE *csv_text;
    char str[100];
    char *eachline = NULL;
    size_t len = 1000;
    size_t line_size;
    struct count_tweeters map;
    int array_tracker;
    char* name = "name";

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
        int name_col = 0;
        while (getline(&eachline, &len, csv_text) != -1){
            char* token = NULL;
            //printf("%s\n", token);
            int counter_col = 0;
            // have to check each token, it just takes away all the blanks for some reason
            // I used strsep because it can also take in zero-string lengths
            while ((token = strsep(&eachline, ","))!= NULL) {
                //trying to print out name
                // also not necessarily column 8, have to fix
                // strcmp doesn't compare the exact string
                //while(strcmp(token, "name") != 0)
                if (counter_line == 0 && !strncmp(token, name, 5)) {
                    printf("Strcmp #: %d, \n",  counter_col);
                    //printf("Token: %lu, Name: %lu\n", strlen(token), strlen("name "));
                    //assign the column where the names are to use for comparison later
                    name_col = counter_col;
                    printf("%lu,%s\n", strlen(token), token);
                    //printf("%s\n", token); 
                }

                //check the specific column for the name
                if (counter_line > 0 && counter_col == name_col) {
                    //need to make a key and value sort of thing in c
                    //No maps in c, so use a struct???
                    int found_match = 0;
                    
                    //seg fault
                    for (int i = 0; i < 10; i++){
                        // if they have the same name, then increment the count
                        // if (strcmp(token, map.list_names[i]) == strlen(token)){
                        //      map.count[i] = map.count[i]+ 1;
                        //      int found_match = 1;
                        // }
                    //map.list_names[counter_line - 1] = token;
                    //map.count[counter_line - 1] = map.count[0]+ 1;
                    
                    //If no match was found for the name
                    
                    // if (found_match == 0){
                    //     map.list_names[array_tracker] = token;
                    //     map.count[array_tracker] = map.count[array_tracker]+ 1;
                    //     array_tracker++;
                    // }

                    printf("%s\n", token); 
                    }
                }
                token = strtok(NULL, ",");
                counter_col++; 
            }
            //printf("%s\n", token);
            //printf("%s\n",eachline);
            counter_line++;
        }
    }
    
    //Not causing seg fault
    //Print the tweeters with their respective count
    //for (int i = 0; i < 10; i++) {
    //    printf("%s : %i\n", map.list_names[i], map.count[i]);
    //}
    
    return 0;
}

//"cl-tweets-short-clean.csv"