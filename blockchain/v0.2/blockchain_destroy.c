#include "blockchain.h"

/**
 * blockchain_destroy - deletes an existing Blockchain, and Blocks it contains
 * @blockchain: points to the Blockchain structure to delete
 **/
void blockchain_destroy(blockchain_t *blockchain)
{
	llist_destroy(blockchain->chain, REMOVE_NODES, NULL);
	free(blockchain);
}
