#include "../utils/utils.h"


/**
 * load - Loads data from pub key
 * @args: command arguments
 * Return: status
 **/
int load(char **args)
{
	char *path;
	blockchain_t *tmp;
	int i, num_blocks;
	block_t *prev_block = NULL, *block;

	if (args && args[1])
		path = args[1];
	else
		path = default_hblk_file;

	tmp = blockchain_deserialize(path);
	if (!tmp)
	{
		print_error("load");
		return (errno);
	}
	num_blocks = llist_size(tmp->chain);
	for (i = 0; i < num_blocks; i++)
	{
		block = llist_get_node_at(tmp->chain, i);
		if (block_is_valid(block, prev_block, tmp->unspent) == 1)
		{
			print_error("load: Invalid blockchain");
			blockchain_destroy(tmp);
			return (-1);
		}
		prev_block = block;
	}
	printf("Saving current blockchain into file save.hblk... ");
	save(NULL);
	blockchain = tmp;
	return (0);
}