#include "utils/utils.h"


/**
 * startup - startup globals
 */
__attribute__((constructor))int startup(void)
{
	wallets = llist_create(MT_SUPPORT_FALSE);
	if (!wallets)
		return (error_out("wallets list failed to initialize"));
	transaction_pool = llist_create(MT_SUPPORT_FALSE);
	if (!transaction_pool)
		return (error_out("local transaction pool failed to initialize"));
	line_size = 0;
	line = NULL;
	running = 1;
	current_wallet = NULL;
	blockchain = blockchain_deserialize(default_hblk_file);
	if (!blockchain)
		blockchain = blockchain_create();
	if (!blockchain)
		return (error_out("could not load blockchain"));
	prev_block = llist_get_node_at(blockchain->chain, 0);
	return (0);
}

/**
 * cleanup - clean up
 */
__attribute__((destructor))void cleanup(void)
{
	printf("destroying wallets...\n");
	llist_destroy(wallets, 1, (node_dtor_t)EC_KEY_free);
	printf("destorying blockchain\n");
	blockchain_destroy(blockchain);
	printf("destroying line\n");
	free(line);
}


/**
 * main - Entry Point for the CLI
 * @ac: args quantity
 * @av: args array
 * Return: status
 **/
int main(int ac, char **av)
{
	char **args = NULL;
	size_t args_size = 0;
	int prev_status, status = 0;

	program_name = av[0];

	if (ac > 1)
	{
		print_help();
		exit(1);
	}

	while (running)
	{
		printf("%s", default_prompt);

		memset(line, 0, line_size);
		if (getline(&line, &line_size, stdin) == -1)
		{
			status = error_out("getline");
		}
		args = getargs(args, &args_size, line);
		if (!args)
		{
			status = error_out("getargs");
		}
		else
		{
			prev_status = status;
			status = execute(args);
			if (status == KEEP_PREVIOUS_STATUS)
				status = prev_status;
		}
	}
	free(args);
	return (status);
}
