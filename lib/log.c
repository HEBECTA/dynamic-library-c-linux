#include "log.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int callback(void *data, int argc, char **argv, char **azColName){
        
   for(int i = 0; i<argc; i++)
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   
   printf("\n");

   return 0;
}

void set_log(Log *log_ptr, message_level msg_lvl, const char *msg, const char *prog_name, time_t date){

        log_ptr->msg_lvl = msg_lvl;

        strncpy(log_ptr->message, msg, LOG_MESSAGE_BUFFER_SIZE);

        strncpy(log_ptr->program_name, prog_name, LOG_PROGRAM_NAME_MAX_SIZE);

        log_ptr->date = date;
}

int open_log(){

        int rc = sqlite3_open(log_file, &db);
    
        if (rc != SQLITE_OK) {
                
                //fprintf(stderr, "open_log cannot open log file: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                
                return 1;
        }

        return 0;
}

void close_log(){

        sqlite3_close(db);
}

int write_log(const Log *ptr_log){

        char *err_msg = 0;

        int rc = sqlite3_exec(db, sql_init, 0, 0, &err_msg);

        if (rc != SQLITE_OK ) {
                
                //fprintf(stderr, "Failed to create table\n");
                //fprintf(stderr, "SQL error: %s\n", err_msg);
                sqlite3_free(err_msg);
        } 

        char sql[LOG_MESSAGE_BUFFER_SIZE+LOG_PROGRAM_NAME_MAX_SIZE+100];

        sprintf(sql, "INSERT INTO LOGS (Message_level, Message, Program_name, Date) "  \
         "VALUES (%d, \"%s\", \"%s\", \"%s\");", ptr_log->msg_lvl, ptr_log->message, \
          ptr_log->program_name, ctime(&ptr_log->date));
     
        rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
        
        if (rc != SQLITE_OK ) {
                
                //fprintf(stderr, "Failed to write into table\n");
                //fprintf(stderr, "SQL error: %s\n", err_msg);
                //sqlite3_free(err_msg);
        } 
        
        return 0;
}

int print_log(const char *program_name){

        char *zErrMsg = 0;

        char sql[LOG_PROGRAM_NAME_MAX_SIZE+20];

        if (program_name == NULL )
                strcpy(sql, "SELECT * from LOGS;");
        

        else 
                sprintf(sql, "SELECT * from LOGS WHERE Program_name = \"%s\";", program_name);
               
        int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

        if( rc != SQLITE_OK ) {

                //fprintf(stderr, "print_log: SQL error: %s\n", zErrMsg);
                //sqlite3_free(zErrMsg);
                return 1;
        }

        return 0;
}
