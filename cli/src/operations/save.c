#include "../utils/utils.h"

/**
 * save - saves blockchain in the desired path
 * @args: command arguments
 * Return: status
 **/
int save(char **args)
{
	int status;
	char *path;

	if (args && args[1])
		path = args[1];
	else
		path = default_hblk_file;

	status = blockchain_serialize(blockchain, path);
	if (status == 0)
		printf("Blockchain saved in %s\n", path);
	else
		print_error("save");
	return (status);
}