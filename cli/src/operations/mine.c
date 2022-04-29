#include "../utils/utils.h"

/**
 * mine - mine function
 * @args: command arguments
 * Return: -1 on error 0 if success
 **/
int mine(char **args)
{
	block_t *block;
	size_t size = llist_size(transaction_pool);
	size_t i;
	transaction_t *tx;
	
	(void)args;
	
	block = block_create(prev_block, NULL, 0);
	if (!block)
	{
		print_error("mine: failed to create block");
		return (-1);
	}

	for (i = 0; i < size; i++)
	{
		tx = llist_get_node_at(transaction_pool, i);
		if (transaction_is_valid(tx, blockchain->unspent))
			llist_add_node(block->transactions, tx, ADD_NODE_REAR);
	}

	block_mine(block);

	if (!block_is_valid(block, prev_block, blockchain->unspent))
	{
		block_destroy(block);
		fprintf(stderr, "mine: mined block was invalid\n");
		return (-1);
	}

	if (llist_add_node(blockchain->chain, block, ADD_NODE_REAR) == -1)
	{
		block_destroy(block);
		fprintf(stderr, "mine: could not add mined block to blockchain\n");
		return (-1);
	}
	prev_block = block;
	return (0);
}