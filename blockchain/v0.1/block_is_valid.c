#include "blockchain.h"

/**
 * is_genesis_block - checks if a block is the Genesis block
 * @block: pointer to block
 * Return: 1 if it is, 0 if it isn't
 **/
static int is_genesis_block(block_t const *block)
{
	static uint8_t buf[SHA256_DIGEST_LENGTH] = {0};

	return (
		block->data.len == sizeof(DATA) - 1 &&
		!memcmp(block->data.buffer, DATA, block->data.len) &&
		!block->info.index &&
		!block->info.difficulty &&
		!block->info.nonce &&
		block->info.timestamp == TIMESTAMP &&
		!memcmp(block->info.prev_hash, buf, sizeof(buf))
	);
}

/**
 * block_is_valid - verifies that a Block is valid
 * @block: points to Block to check
 * @prev_block: previous Block in the Blockchain, or NULL if block is first one
 * Return: 1 if valid, else 0
 **/
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t tmp[SHA256_DIGEST_LENGTH];

	if (!block)
		return (1);
	if (!block->info.index)
		return (prev_block || !is_genesis_block(block));
	if (!prev_block)
		return (1);
	if (block->info.index != prev_block->info.index + 1)
		return (1);
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);
	if (!block_hash(block, tmp))
		return (1);
	if (memcmp(tmp, block->hash, sizeof(tmp)))
		return (1);
	if (!block_hash(prev_block, tmp))
		return (1);
	if (memcmp(tmp, block->info.prev_hash, sizeof(tmp)))
		return (1);
	return (0);
}
