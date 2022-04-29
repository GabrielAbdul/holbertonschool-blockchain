#include "../utils/utils.h"


/**
 * info - info function
 * @args: command arguments
 * Return: status
 **/
int info(char **args)
{
	(void)args;
 	printf("Blocks in blockchain: %d\n", llist_size(blockchain->chain));
 	printf("Unspent transaction outputs remaining: %d\n", llist_size(blockchain->unspent));
	printf("Pending transactions in transaction pool: %d\n", llist_size(transaction_pool));
	return (0);
}
