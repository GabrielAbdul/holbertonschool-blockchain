#include "blockchain.h"

/**
 * block_destroy - deletes an existing block
 * @block: block to delete
 */
void block_destroy(block_t *block)
{
	free(block);
}
