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
    int quotes_tracker = 0;
    int name_col = 0;

    if (argc != 2){
        printf("Invalid Input Format\n");
        exit(0);
    }

    if (argc == 2){
        csv_text = fopen(argv[1], "r");
        
        if (csv_text == NULL) {
            printf("Invalid Input Format\n");
            exit(0);
        }

        int counter_line = 0;

        int name_header_there = 0;

        while (getline(&eachline, &len, csv_text) != -1){
            if (strlen(eachline) > 1024){
                printf("Invalid Input Format\n");
                exit(0);
            }

            if (counter_line >= 20000){
                printf("Invalid Input Format\n");
                exit(0);
            }
            char* token = NULL;
            int counter_col = 0;

            // have to check each token, it just takes away all the blanks for some reason
            // I used strsep because it can also take in zero-string lengths
            while ((token = strsep(&eachline, ","))!= NULL) {

                //this is just for header
                //check for single quote
                if (counter_line == 0 && strlen(token) == 1 && !strncmp(&token[0],"\"",1) && !strncmp(&token[strlen(token) - 1],"\"",1)){
                    printf("Invalid Input Format\n");
                    exit(0);
                //check for matching parentheses
                } else if (counter_line == 0 && !strncmp(&token[0],"\"",1) && !strncmp(&token[strlen(token) - 1],"\"",1)){
                    quotes_checker[quotes_tracker] = 1;
                    quotes_tracker++;
                //check for no quotes at beginning and end
                } else if (counter_line == 0 && strncmp(&token[0],"\"",1) && strncmp(&token[strlen(token) - 1],"\"",1)){
                    //printf("working no quotes\n");
                    quotes_checker[quotes_tracker] = 0;
                    quotes_tracker++;
                // if single quote is at beginning
                } else if (counter_line == 0 && !strncmp(&token[0],"\"",1)) {
                    printf("Invalid Input Format\n");
                    exit(0);
                // if single quote is at end
                } else if (counter_line == 0 && !strncmp(&token[strlen(token) - 1],"\"",1)) {
                    printf("Invalid Input Format\n");
                    exit(0);
                }

                // find "name" in the csv header file first line
                // !strncmp(token, name, 5) finds the "name"
                if (counter_line == 0 && (!strncasecmp(token, name, 5) || !strncasecmp(token, quoted_name, 7))){
                    //assign the column where the names are to use for comparison later
                    name_col = counter_col;
                    name_header_there++;
                }

                //checks for consistency for each token in each line with the header
                if (counter_line > 0) {
                    if (strlen(token) == 1 && !strncmp(&token[0],"\"",1) && !strncmp(&token[strlen(token) - 1],"\"",1)){
                        printf("Invalid Input Format\n");
                        exit(0);
                    //check for matching parentheses
                    } else if (!strncmp(&token[0],"\"",1) && !strncmp(&token[strlen(token) - 1],"\"",1)){
                        int non_header_quoted = 1;
                        if (non_header_quoted != quotes_checker[counter_col]){
                            printf("Invalid Input Format\n");
                            exit(0);
                        }
                    //check for no quotes at beginning and end
                    } else if (strncmp(&token[0],"\"",1) && strncmp(&token[strlen(token) - 1],"\"",1)){
                        int non_header_quoted = 0;
                        if (non_header_quoted != quotes_checker[counter_col]){
                            printf("Invalid Input Format\n");
                            exit(0);
                        }
                    // if single quote is at beginning
                    } else if (!strncmp(&token[0],"\"",1)) {
                        printf("Invalid Input Format\n");
                        exit(0);
                    // if single quote is at end
                    } else if (!strncmp(&token[strlen(token) - 1],"\"",1)) {
                        printf("Invalid Input Format\n");
                        exit(0);
                    }
                }

                //check the specific column for the name
                if (counter_line > 0 && counter_col == name_col) {
                    int found_match = 0;
                    for (int i = 0; i < array_tracker; i++){
                        // if they have the same name, then increment the count
                        if (!strncasecmp(token, static_arr[i], strlen(static_arr[i]) + 1)) {
                            count_arr[i] = count_arr[i]+ 1;
                            found_match = 1;
                            break;
                        }
                    }

                    //If no match was found for the name
                    if (found_match == 0){
                            static_arr[array_tracker] = token;
                            count_arr[array_tracker] = count_arr[array_tracker] + 1;
                            array_tracker++;
                    }
                }
                counter_col++; 
            }

            if (name_header_there == 0){
                printf("Invalid Input Format\n");
                exit(0);
            } else if (name_header_there > 1){
                printf("Invalid Input Format\n");
                exit(0);
            }

            counter_line++;
        }
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
            // if the column does have quotes
            if (quotes_checker[name_col] == 1){
                char* test_trial = static_arr[max_index];
                //remove the quotes when printing
                int unquoted_length = strlen(static_arr[max_index]) - 2;
                printf("%.*s", unquoted_length, test_trial + 1);
                printf(": %d\n", count_arr[max_index]);
                count_arr[max_index] = -1;
            // if the column does not have quotes
            } else {
                printf("%s: %d\n", static_arr[max_index], count_arr[max_index]);
                count_arr[max_index] = -1;
            }
        }
    }
    return 0;
}