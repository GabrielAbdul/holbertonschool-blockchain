#include "blockchain.h"

/**
 * blockchain_create - creates Genesis block of Blockchain
 * Return: newly initialized Blockchain structure
 */
blockchain_t *blockchain_create(void)
{
	block_t *block;
	blockchain_t *blockchain;
	char *hash = "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"; /* c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803 */

	block = calloc(1, sizeof(block_t));
	blockchain = malloc(sizeof(blockchain_t));

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
	block->info.timestamp = 1537578000;
	block->info.nonce = 0;
	memcpy(&(block->data.buffer), "Holberton School", 16);
	block->data.len = 16;
	memcpy(&(block->hash), hash, 256);

	printf("Here\n");
	if (llist_add_node(blockchain->chain, block, ADD_NODE_FRONT) == -1)
	{
		llist_destroy(blockchain->chain, KEEP_NODES, NULL);
		free(block);
		free(blockchain);
		return (NULL);
	}
	return (blockchain);
}
