#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
    FILE *csv_text;
    char *eachline = NULL;
    char* name = "name";
    char* quoted_name = "\"name\"";
    // Assign Capacity
    int initial_cap = 2;

    size_t len = 1024;
    size_t line_size;
    int array_tracker = 0;

    char* static_arr[20000] = {""};
    int count_arr[20000] = {[0 ... 19999] = 0};
    int top_tweeters[10] = {[0 ... 9] = 0};

    //additional checks
    //check each column's header to see if they have parentheses 
    int quotes_checker[16] = {[0 ... 15] = 0};

    if (argc != 2){
        printf("Invalid Input Format\n");
        exit(0);
    }

    if (argc == 2){
        csv_text = fopen(argv[1], "r");
        
        if (csv_text == NULL) {
            printf("Invalid File Format\n");
            exit(0);
        }

        int counter_line = 0;
        int name_col = 0;

        int name_header_there = 0;

        while (getline(&eachline, &len, csv_text) != -1){
            
            char* token = NULL;
            //printf("%s\n", token);
            int counter_col = 0;

            // have to check each token, it just takes away all the blanks for some reason
            // I used strsep because it can also take in zero-string lengths
            while ((token = strsep(&eachline, ","))!= NULL) {
                // find "name" in the csv header file first line
                // !strncmp(token, name, 5) finds the "name"
                if (counter_line == 0 && (!strncasecmp(token, name, 5) || !strncasecmp(token, quoted_name, 7))){
                    //printf("Strcmp #: %d ",  counter_col);
                    //printf("Strlen: %lu, String: %s\n", strlen(token), token);
                    //assign the column where the names are to use for comparison later
                    name_col = counter_col;
                    name_header_there++;
                }

                //check the specific column for the name
                if (counter_line > 0 && counter_col == name_col) {
                    //need to make a key and value sort of thing in c
                    //No maps in c, so use a struct???
                    int found_match = 0;
                    
                    //seg fault
                    for (int i = 0; i < array_tracker; i++){
                        // if they have the same name, then increment the count
                        //printf("Comparing %s with %s\n", token, static_arr[i]);
                        if (!strncasecmp(token, static_arr[i], strlen(static_arr[i]) + 1)) {
                            //printf("Incrementing count for %s\n", static_arr[i]);
                            //printf("Old count: %d\n", count_arr[i]);
                            count_arr[i] = count_arr[i]+ 1;
                            found_match = 1;
                            break;
                        }
                    }

                    //If no match was found for the name
                    if (found_match == 0){
                            static_arr[array_tracker] = token;
                            count_arr[array_tracker] = count_arr[array_tracker] + 1;
                            //printf("array_tracker: %d", array_tracker);
                            array_tracker++;
                    }
                    //printf("%s\n", token);
                }
                //token = strtok(NULL, ",");
                //printf("%s\n", token);
                counter_col++; 
            }
            //printf("%s\n", token);
            //printf("%s\n",eachline);

            if (name_header_there == 0){
                printf("Name header not found\n");
                exit(0);
            } else if (name_header_there > 1){
                printf("Duplicate name headers\n");
                exit(0);
            }

            counter_line++;
        }
    }
    
    //Not causing seg fault
    //Print the tweeters with their respective count
    for (int i = 0; i < 10; i++) {
         //printf("%s : %i\n", map.list_names[i], map.count[i]);
        //printf("Strings: %s, Count: %d\n", static_arr[i], count_arr[i]);
    }
    
    //Calculating the top ten tweeters
    int reps = 10;
    if (array_tracker < 10){
        reps = array_tracker;
    }
    for (int i = 0; i < reps; i++){
        int max_num = 0;
        int max_index = 0;
        for (int j = 0; j < array_tracker; j++){
            if (count_arr[j] > max_num){
                max_num = count_arr[j];
                max_index = j;
            }
        }
        //Set it to -1 since we are done with it and nothing can be less than 0;
        if (i >= reps) {
            break;
        } else if (i < reps){
            printf("%s : %d\n", static_arr[max_index], count_arr[max_index]);
            count_arr[max_index] = -1;
        }
    }
    //printf("%d\n", max_num);

    return 0;
}

//"cl-tweets-short-clean.csv"