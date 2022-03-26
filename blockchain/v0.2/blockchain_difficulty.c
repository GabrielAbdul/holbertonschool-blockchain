#include "blockchain.h"

/**
 * blockchain_difficulty - computes difficulty to assign to next b in chain
 * @blockchain: pointer to blockchain to analyze
 * Return: difficulty to be assigned to a potential next b
 **/
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *b, *last_block;
	uint64_t time;

	if (blockchain == NULL)
		return (0);

	b = llist_get_tail(blockchain->chain);
	if (b == NULL)
		return (0);

	if (b->info.index && !(b->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL))
	{
		last_block = llist_get_node_at(blockchain->chain, b->info.index
										- DIFFICULTY_ADJUSTMENT_INTERVAL + 1);
		time = b->info.timestamp - last_block->info.timestamp;

		if (time < EXPECTED_TIME_BETWEEN_ADJUSTMENTS / 2)
			return (b->info.difficulty + 1);

		if (time > EXPECTED_TIME_BETWEEN_ADJUSTMENTS * 2)
			return (b->info.difficulty - !!b->info.difficulty);
	}

	return (b->info.difficulty);
}
