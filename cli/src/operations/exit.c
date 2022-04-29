#include "../utils/utils.h"

/**
 * my_exit - my_exit function
 * @args: command arguments
 * Return: status
 **/
int my_exit(char **args)
{
	(void)args;
	printf("goodbye\n");
	running = 0;
	return (KEEP_PREVIOUS_STATUS);
}
