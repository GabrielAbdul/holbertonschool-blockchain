#include "blockchain.h"


/**
 * blockchain_create - creates block block of Blockchain
 * Return: newly initialized Blockchain structure
 * TODO ADD COMMENTS, UPDATE FUNCTION DOCS
 */
blockchain_t *blockchain_create(void)
{
	block_t *block;
	blockchain_t *blockchain = calloc(1, sizeof(blockchain_t));

	block = calloc(1, sizeof(block_t));

	if (block == NULL || blockchain == NULL)
	{
		free(block);
		free(blockchain);
		return (NULL);
	}

	blockchain->chain = llist_create(MT_SUPPORT_FALSE);

	if (blockchain->chain == NULL)
	{
		free(blockchain);
		free(block);
		return (NULL);
	}

	block->info.index = 0;
	block->info.difficulty = 0;
	block->info.timestamp = TIMESTAMP;
	block->info.nonce = 0;
	memset(block->info.prev_hash, 0, sizeof(block->info.prev_hash));
	block->data.len = DATA_LEN;
	memset(block->data.buffer, 0, sizeof(block->data.buffer));
	memcpy(block->data.buffer, DATA, block->data.len);
	memset(block->hash, 0, sizeof(HASH));
	memcpy(block->hash, HASH, sizeof(HASH));
	if (llist_add_node(blockchain->chain, block, ADD_NODE_FRONT) == -1)
	{
		llist_destroy(blockchain->chain, KEEP_NODES, NULL);
		free(block);
		free(blockchain);
		return (NULL);
	}
	block->transactions = NULL;
	return (blockchain);
}
