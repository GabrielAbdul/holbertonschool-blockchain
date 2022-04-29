#ifndef _UTILS_H
#define _UTILS_H


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <blockchain.h>
#define default_prompt ">>> "
#define default_hblk_file "save.hblk"
#define KEEP_PREVIOUS_STATUS INT_MIN
#define is_numeric(x) ((x) >= '0' && (x) <= '9')
#define is_lowercase_alpha(x) ((x) >= 'a' && (x) <= 'z')

/* GLOBALS */
char *program_name;
int running;
llist_t *wallets;
EC_KEY *current_wallet;
blockchain_t *blockchain;
llist_t *transaction_pool;
size_t line_size;
char *line;
block_t *prev_block;

/**
 * struct blockchain_cli_command_s - associates a cli thingie command with a function
 * @command: command (string)
 * @func: associated function that performs command
 **/
typedef struct blockchain_cli_command_s
{
	char *command;
	int (*func)(char **args);
} blockchain_cli_command_t;

#define HELP_STRING \
"\
Valid commands:\n\
    * help\n\
    * load [path-of-blockchain-file] (\"./save.hblk\" by default)\n\
    * save [path-of-blockchain-file] (\"./save.hblk\" by default)\n\
    * wallet_load\n\
    * wallet_save\n\
    * info\n\
	* mine\n\
	* send\n\
"

void print_error(char *msg);
void print_help(void);
int error_out(char *msg);
char **getargs(char **args, size_t *args_size, char *line);
int execute(char **args);
int wallet_save(char **args);
int wallet_load(char **args);
int send(char **args);
int mine(char **args);
int info(char **args);
int save(char **args);
int load(char **args);
int my_exit(char **args);
const EC_KEY *get_key(char *s);
uint32_t get_amount(char *s);
void *realloc_array(void *arr, size_t *arr_size);
#endif /* _UTILS_H */
