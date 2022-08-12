#include "../lib/log.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 20

void genRandomText(int size, char *buffer)
{
    memset(buffer, 0, size);

    for (int i = 0; i < size; i++) {
        char symbol[size];
        int num = (rand() % (90 - 65 + 1)) + 65;
        sprintf(symbol,"%c", num);
        strcat(buffer, symbol); 
    }
}

int main(int argc, char *argv[]){

        char *buffer = NULL;

        srand(time(0));

        Log *log = (Log *) malloc(sizeof(Log));

        if ( log == NULL )
                exit(1);

        buffer = (char *) malloc(sizeof(char)*BUFF_SIZE);

        if ( buffer == NULL )
                exit(1);
        
        int file = open_log();

        if ( file ){

                fprintf(stderr, "Failed to open log file\n");
                free(log);
                free(buffer);
                exit(1);
        }

        for (int i = 0; i < 10; ++i){

                genRandomText(BUFF_SIZE, buffer);

                time_t now = time(0); 

                set_log(log, rand()%3, buffer, argv[0]+2, now);

                if ( write_log(log) ){

                        fprintf(stderr, "Failed to write into log\n");
                        free(buffer);
                        free(log);
                        close_log();
                        exit(1);
                }

                sleep(2);
        }

        free(buffer);
        free(log);
        close_log();
        
        return 0;
}