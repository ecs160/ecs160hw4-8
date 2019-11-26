#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//test
struct count_tweeters{
        int capacity;
        char* list_names[2];
        int count[2];
    };

int main(int argc, char** argv){
    FILE *csv_text;
    char *eachline = NULL;
    char* name = "name";
    struct count_tweeters map;
    // Assign Capacity
    int initial_cap = 2;
    map.capacity = initial_cap;

    //char str[100];
    size_t len = 1024;
    size_t line_size;
    int array_tracker = 0;

    char* static_arr[20000] = {[0 ... 19999] = ""};
    int count_arr[20000] = {[0 ... 19999] = 0};

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

        while (getline(&eachline, &len, csv_text) != -1){
            
            char* token = NULL;
            //printf("%s\n", token);
            int counter_col = 0;

            // have to check each token, it just takes away all the blanks for some reason
            // I used strsep because it can also take in zero-string lengths
            while ((token = strsep(&eachline, ","))!= NULL) {
                // find "name" in the csv header file first line
                // !strncmp(token, name, 5) finds the "name"
                if (counter_line == 0 && !strncmp(token, name, 5)) {
                    printf("Strcmp #: %d ",  counter_col);
                    printf("Strlen: %lu, String: %s\n", strlen(token), token);
                    //assign the column where the names are to use for comparison later
                    name_col = counter_col;
                }

                //check the specific column for the name
                if (counter_line > 0 && counter_col == name_col) {
                    //need to make a key and value sort of thing in c
                    //No maps in c, so use a struct???
                    int found_match = 0;
                    
                    //seg fault
                    for (int i = 0; i < 19999; i++){
                        // if they have the same name, then increment the count
                        if (!strncmp(token, static_arr[i], strlen(static_arr[i]) + 1)) {
                            count_arr[i] = count_arr[i]+ 1;
                            int found_match = 1;
                            break;
                        }
                        //map.list_names[counter_line - 1] = token;
                        //map.count[counter_line - 1] = map.count[0]+ 1;
                    
                        //If no match was found for the name
                    
                        if (found_match == 0){
                            if (array_tracker == 20000){
                                exit(0);
                            }
                            static_arr[array_tracker] = token;
                            count_arr[array_tracker] = count_arr[array_tracker] + 1;

                            //map.list_names[array_tracker] = token;
                            //map.count[array_tracker] = map.count[array_tracker]+ 1;
                            //array_tracker++;
                            //printf("array_tracker: %d", array_tracker);
                            array_tracker++;
                            break;
                        }

                         
                    }
                    //printf("%s\n", token);
                }
                //token = strtok(NULL, ",");
                //printf("%s\n", token);
                counter_col++; 
            }
            //printf("%s\n", token);
            //printf("%s\n",eachline);
            counter_line++;
        }
    }
    
    //Not causing seg fault
    //Print the tweeters with their respective count
    for (int i = 0; i < 8; i++) {
        //printf("%s : %i\n", map.list_names[i], map.count[i]);
        printf("Strings: %s, Count: %d\n", static_arr[i], count_arr[i]);
    }
    
    return 0;
}

//"cl-tweets-short-clean.csv"