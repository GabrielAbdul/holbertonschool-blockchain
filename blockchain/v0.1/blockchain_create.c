#include "blockchain.h"

/**
 * blockchain_create - creates Genesis block of Blockchain
 * Return: newly initialized Blockchain structure
 */
blockchain_t *blockchain_create(void)
{
	llist_t *chain;
	block_t *block;
	blockchain_t *blockchain;
	char *hash = "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"; /* c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803 */

	chain = calloc(1, sizeof(llist_t));
	block = malloc(sizeof(block_t));
	blockchain = malloc(sizeof(blockchain_t));

	if (chain == NULL ||  block == NULL || blockchain == NULL)
	{
		free(chain);
		free(block);
		free(blockchain);
		return (NULL);
	}

	block->info.index = 0;
	block->info.difficulty = 0;
	block->info.timestamp = 1537578000;
	block->info.nonce = 0;
	memcpy(&(block->data.buffer), "Holberton School", 16);
	block->data.len = 16;
	memcpy(&(block->hash), hash, 256);

	llist_add_node(chain, block, ADD_NODE_FRONT);
	blockchain->chain = chain;
	return (blockchain);
}
