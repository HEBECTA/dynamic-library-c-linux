#ifndef LOG_H
#define LOG_H

#define LOG_MESSAGE_BUFFER_SIZE 250
#define LOG_PROGRAM_NAME_MAX_SIZE 100

#include <stdio.h>
#include <time.h>
#include <sqlite3.h>

typedef enum message_level {LOG_INFO, LOG_WARNING, LOG_ERROR} message_level;

const char log_file[] = "/var/log/my_log_file";

static const char *sql_init = "CREATE TABLE if not exists LOGS ("
        "ID                     INTEGER PRIMARY KEY,"
        "Message_level          INT,"
        "Message                TEXT,"
        "Program_name           TEXT,"
        "Date                   TEXT);";

typedef struct Log {

    enum message_level msg_lvl;
    char message[LOG_MESSAGE_BUFFER_SIZE];
    char program_name[LOG_PROGRAM_NAME_MAX_SIZE];
    time_t date;
} Log;

void set_log(Log *log_ptr, message_level msg_lvl, const char *msg, const char *prog_name, time_t date);

int open_log();

void close_log();

int write_log(const Log *ptr_log);

int print_log(const char *program_name);

static sqlite3 *db;

#endif