#include "blockchain.h"

/**
 * blockchain_destroy - deletes an existing Blockchain, and Blocks it contains
 * @blockchain: points to the Blockchain structure to delete
 **/
void blockchain_destroy(blockchain_t *blockchain)
{
	if (blockchain == NULL)
		return;
	llist_destroy(blockchain->chain, 1,
		(void (*)(llist_node_t))block_destroy, NULL);
	llist_destroy(blockchain->chain, 1, free);
	free(blockchain);
}
