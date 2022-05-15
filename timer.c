#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define clear() printf("\033[H\033[J")

char* formattedDate(struct tm to_format) {
    char* temp = malloc(sizeof(char)*7);
    char* hour_char = to_format.tm_hour < 10 ? "0" : "";
    char* minute_char = to_format.tm_min < 10 ? "0" : "";
    char* second_char = to_format.tm_sec < 10 ? "0" : "";
    sprintf(temp, "%s%d:%s%d:%s%d",hour_char,to_format.tm_hour,minute_char,to_format.tm_min,second_char,to_format.tm_sec);
    return temp;
}

int main(int argc, char** argv) {
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    for (int i = 1; i < argc; i++) {
        int splitter = strlen(argv[i])-1;
        char* splitString = malloc(sizeof(char)*splitter);
        
        strncpy(splitString, argv[i], splitter);
        int number = atoi(splitString);
        char lastChar = argv[i][splitter];
        switch (lastChar) {
        case 'h':
            hours = number;
            printf("%d hours\n",hours);
            break;
        case 'm':
            minutes = number;
            printf("%d minutes\n",minutes);
            break;
        case 's':
            seconds = number;
            printf("%d seconds\n",seconds);
            break;
        default:
            printf("\"%c\" was not a valid input, ignoring\n",lastChar);
            break;
        }
    }
    long converted_into_seconds = seconds + minutes*60 + hours*3600;
    time_t start = time(NULL);
    time_t end = start + converted_into_seconds;
    time_t current = time(NULL);
    time_t delta = end - current;
    struct tm start_tm = *localtime(&start);
    struct tm end_tm = *localtime(&end);
    struct tm delta_tm;

    while (current < end) {
        current = time(NULL);
        delta = end - current;
        delta_tm = *localtime(&delta);
        --delta_tm.tm_hour;
        clear();
        printf("Time Started:\t%s\nTime End:\t%s\nTime Remaining:\t%s",formattedDate(start_tm),formattedDate(end_tm),formattedDate(delta_tm));
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
    return 0;
}
