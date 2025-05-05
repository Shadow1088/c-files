#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define ID_SIZE 10
#define INPUT_FILE "data.csv"
#define OUTPUT_FILE "sum.txt"

typedef struct{
    short Hours;
    short Minutes;
}TIME_HHMM;

typedef struct{
    char UserID[ID_SIZE];
    TIME_HHMM Session_start_time;
    TIME_HHMM Session_end_time;
    long Transfer;
}LOG;

typedef struct{
    char UserID[ID_SIZE];
    char Logs[];
}USER_LOGS;

void readFileFillArray(char* input_file, LOG** global_logs_arr, int* length){
    FILE* read_file = fopen(input_file, "r");

    if (read_file==NULL){
        printf("Failed to open %s", input_file);
    }

    // fill dynamic file_lines array
    char line[100];


    int token_index = 0;
    while(fgets(line, sizeof(line), read_file)!=NULL){
        (*length)++;
        LOG* tmp = realloc(*global_logs_arr, sizeof(**global_logs_arr) * (*length));
        if (!tmp){
            free(global_logs_arr);
            fclose(read_file);
            exit(EXIT_FAILURE);
        }
        *global_logs_arr = tmp;
        char *charpointer = strtok(line, " :");
        token_index=0;
        while (charpointer!=NULL){
            switch (token_index) {
                case 0:
                    strcpy((*global_logs_arr)[(*length)-1].UserID, charpointer);
                    break;
                case 1:
                    (*global_logs_arr)[(*length)-1].Session_start_time.Hours = atoi(charpointer);
                    break;
                case 2:
                    (*global_logs_arr)[(*length)-1].Session_start_time.Minutes = atoi(charpointer);
                    break;
                case 3:
                    (*global_logs_arr)[(*length)-1].Session_end_time.Hours = atoi(charpointer);
                    break;
                case 4:
                    (*global_logs_arr)[(*length)-1].Session_end_time.Minutes = atoi(charpointer);
                    break;
                case 5:
                    (*global_logs_arr)[(*length)-1].Transfer = atoi(charpointer);
                    break;
            }
            charpointer = strtok(NULL, " :");
            token_index++;
        }
    }

    fclose(read_file);
}


// Sorts file's lines based on userID, which is typically located at the line's beginning, by Bubble Sort
void sortArrByPrefix(LOG** global_logs_arr, int *length){

    // sort the dynamic array via Bubble Sort
    for(int i=0; i<(*length)-1;i++){  // iteration is equal to its length
        int lowest_value_index = i;
        int lowest_value = atoi((*global_logs_arr)[i].UserID+2);
        for (int j=i; j<(*length);j++){
            if ((atoi((*global_logs_arr)[j].UserID+2) < atoi((*global_logs_arr)[i].UserID+2)) && atoi((*global_logs_arr)[j].UserID+2) < lowest_value){
                lowest_value_index = j;
                lowest_value = atoi((*global_logs_arr)[j].UserID+2);
            }
        }
        if (lowest_value < atoi((*global_logs_arr)[i].UserID+2)){
            LOG lowest_value_temp = (*global_logs_arr)[lowest_value_index];
            (*global_logs_arr)[lowest_value_index] = (*global_logs_arr)[i];
            (*global_logs_arr)[i] = lowest_value_temp;
        }
    }
}

int timeConvertHMtoM(int hours, int minutes){
    return hours*60+minutes;
}

void writeFileWithLogSum(LOG** global_logs_arr, int *length){
    FILE* fw = fopen(OUTPUT_FILE, "w"); //clears file
    fclose(fw);

    FILE* fa = fopen(OUTPUT_FILE, "a");

    int duration_total_mins = 0;
    long transfer_total_bytes = 0;
    LOG* user_logs = NULL;
    int user_logs_count = 0;
    for(int i=0; i<(*length); i++){
        // if same ID, collect info
        if(i==0 || atoi((*global_logs_arr)[i-1].UserID+2) == atoi((*global_logs_arr)[i].UserID+2)){
            user_logs_count++;
            user_logs = realloc(user_logs, sizeof(LOG) * user_logs_count);
            user_logs[user_logs_count-1] = (*global_logs_arr)[i];
            duration_total_mins += timeConvertHMtoM((*global_logs_arr)[i].Session_end_time.Hours, (*global_logs_arr)[i].Session_end_time.Minutes) - timeConvertHMtoM((*global_logs_arr)[i].Session_start_time.Hours, (*global_logs_arr)[i].Session_start_time.Minutes);
            transfer_total_bytes += (*global_logs_arr)[i].Transfer;
            continue;
        }
        // if different user:
        //      print header with last user
        //      print logs of last user
        //
        //      reset collected info to current user first info
        //      reset user logs to current user first log

        fprintf(fa, "%s       %4d min  %9ld bytes\n", (*global_logs_arr)[i-1].UserID, duration_total_mins, transfer_total_bytes);
        for(int j=0; j<user_logs_count; j++){
            fprintf(fa, "    %02d:%02d   %02d:%02d   %9ld\n", user_logs[j].Session_start_time.Hours,  user_logs[j].Session_start_time.Minutes,  user_logs[j].Session_end_time.Hours, user_logs[j].Session_end_time.Minutes, user_logs[j].Transfer);
        }
        duration_total_mins = timeConvertHMtoM((*global_logs_arr)[i].Session_end_time.Hours, (*global_logs_arr)[i].Session_end_time.Minutes) - timeConvertHMtoM((*global_logs_arr)[i].Session_start_time.Hours, (*global_logs_arr)[i].Session_start_time.Minutes);
        transfer_total_bytes = (*global_logs_arr)[i].Transfer;
        free(user_logs);
        user_logs = NULL;
        user_logs_count = 1;
        user_logs = realloc(user_logs, sizeof(LOG) * user_logs_count);
        user_logs[user_logs_count-1] = (*global_logs_arr)[i];
    }
    fprintf(fa, "%s       %4d min %9ld bytes\n", (*global_logs_arr)[(*length)-1].UserID, duration_total_mins, transfer_total_bytes);
    for(int j=0; j<user_logs_count; j++){
        fprintf(fa, "    %02d:%02d   %02d:%02d   %9ld\n", user_logs[j].Session_start_time.Hours,  user_logs[j].Session_start_time.Minutes,  user_logs[j].Session_end_time.Hours, user_logs[j].Session_end_time.Minutes, user_logs[j].Transfer);
    }
    fclose(fa);
}

int main(){
    LOG* logs = NULL;
    int logs_length = 0;
    readFileFillArray(INPUT_FILE, &logs, &logs_length);
    sortArrByPrefix(&logs, &logs_length);
    writeFileWithLogSum(&logs, &logs_length);

    free(logs);
    return 0;
}
