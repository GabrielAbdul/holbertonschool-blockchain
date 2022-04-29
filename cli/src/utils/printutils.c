#include "utils.h"

/**
 * print_help - Prints help string
 **/
void print_help(void)
{
	printf(HELP_STRING);
}

/**
 * error_out - Prints error & exit CLI
 * @msg: message
 **/
int error_out(char *msg)
{
	print_error(msg);
	running = 0;
	return (errno);
}

/**
 * getargs - function
 * @args: args
 * @args_size: size of args
 * @line: line where args are taken from
 * Return: status
 **/
char **getargs(char **args, size_t *args_size, char *line)
{
	size_t i;
	char *token;

	if (*args_size == 0)
		args = realloc_array(args, args_size);

	for (i = 0; (token = strtok(line, " \n")); i++)
	{
		line = NULL;
		if (i == *args_size)
			args = realloc_array(args, args_size);
		args[i] = token;
	}

	args[i] = NULL;
	return (args);
}

/**
 * execute - execute function
 * @args: command arguments
 * Return: status
 **/
int execute(char **args)
{
	blockchain_cli_command_t commands[] = {
		{"wallet_load", wallet_load},
		{"wallet_save", wallet_save},
		{"send", send},
		{"mine", mine},
		{"info", info},
		{"load", load},
		{"save", save},
		{"exit", my_exit}
	};

	size_t i;

	if (!args || !(*args))
	{
		print_help();
		return (1);
	}

	for (i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
		if (!strcmp(args[0], commands[i].command))
			return (commands[i].func(args));

	fprintf(stderr, "%s: \"%s\": Unknown command\n", program_name, args[0]);
	print_help();
	return (1);
}

/**
 * print_error - function
 * @msg: message
 **/
void print_error(char *msg)
{
	char error_msg[64];

	sprintf(error_msg, "%s: %s", program_name, msg);
	perror(error_msg);
}
