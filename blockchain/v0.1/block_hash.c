#include "blockchain.h"

/**
 * block_hash - computes the hash of a Block
 * @block: points to the Block to be hashed
 * @hash_buf: buf to store hash
 * Return: pointer to @hash_buf
 */
uint8_t *block_hash(block_t const *block,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t len = sizeof(block->info) + block->data.len;

	sha256((int8_t const *)block, len, hash_buf);
	return (hash_buf);
}
