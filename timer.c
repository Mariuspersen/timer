#include <stdio.h> 
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

#define clear() printf("\033[H\033[J")

int formattedDate(char* buffer,struct tm to_format) {
  sprintf(buffer,"%02u:%02u:%02u", to_format.tm_hour, to_format.tm_min,to_format.tm_sec);
  return 1;
}

int main(int argc, char **argv) {
  time_t hours = 0;
  time_t minutes = 0;
  time_t seconds = 0;

  if (argc == 1) {
    printf("usage:\ttimer <operation> [...]\noperations:\n\ttimer -h <hours>\n\ttimer -m <minutes>\n\ttimer -s <seconds>\n\n use timer for available options\n");
    return EXIT_FAILURE;
  }

  for (int opt = getopt(argc,argv,":h:m:s:"); opt != -1; opt = getopt(argc,argv,":h:m:s:")) {

    time_t number_from_arg;
    if (optarg == NULL) {
      printf("Option needs a value\n");
      return EXIT_FAILURE;
    }

    number_from_arg = strtoul(optarg, NULL, 10);

    if (number_from_arg == 0) {
      printf("Option did not have a real value\n");
      return EXIT_FAILURE;
    }

    switch (opt) {
      case 'h': {
        hours = number_from_arg;
      } break;
      case 'm': {
        minutes = number_from_arg;
      } break;
      case 's': {
        seconds = number_from_arg;
      } break;
    }
  }

  time_t start = time(NULL);
  time_t end = start + (seconds + minutes * 60 + hours * 3600);
  time_t current = time(NULL);
  time_t delta = end - current;

  struct tm start_tm = *localtime(&start);
  struct tm end_tm = *localtime(&end);
  struct tm delta_tm;

  char formatted_start[9];
  char formatted_end[9];
  char formatted_delta[9];
  
  while (current < end) {
    current = time(NULL);
    delta = end - current;
    delta_tm = *localtime(&delta);
    --delta_tm.tm_hour;
    clear();

    formattedDate(formatted_start,start_tm);
    formattedDate(formatted_end,end_tm);
    formattedDate(formatted_delta,delta_tm);
    
    printf("Time Started:\t%s\nTime End:\t%s\nTime Remaining:\t%s",
      formatted_start,
      formatted_end,
      formatted_delta);
    
    fflush(stdout);
    sleep(1);
  }
  printf("\n");
  return EXIT_SUCCESS;
}
