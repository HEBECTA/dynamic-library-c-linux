#include <log.h>
#include <stdlib.h>
#include <stdio.h>
#include <argp.h>
#include <string.h>

const char *argp_program_version =
  "logs";
const char *argp_program_bug_address =
  "<log@logs.org>";

static char doc[] =
  "a program with options to print logs";

static char args_doc[] = "ARG1 ARG2";

static struct argp_option options[] = {
  {"program",   'P', "FILE", 0,
   "Name of the program" }
};

struct arguments
{
  char *output_file;
  int program_name;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{

  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'P':
      arguments->output_file = arg;
      arguments->program_name = 1;
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp argp = { options, parse_opt, NULL, doc };

int main(int argc, char *argv[]){

    struct arguments arguments;

    arguments.program_name = 0;
    arguments.output_file = "-";

    argp_parse (&argp, argc, argv, 0, 0, &arguments);

    int code = open_log();

    if ( code )
      exit(1);

    if ( arguments.program_name ){

        code = print_log(arguments.output_file );
    }
  
    else {

        code = print_log( NULL );
    }

    close_log();
    
    return code;
}