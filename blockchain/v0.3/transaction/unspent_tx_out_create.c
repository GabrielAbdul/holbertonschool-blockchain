#include "transaction.h"

/**
 * unspent_tx_out_create - initializes an unspent transaction output structure
 * @block_hash: hash of the Block where transaction is stored
 * @tx_id: hash of a transactino in the Block block_hash
 * @out: points to the referenced transaction output
 * Return: created unspent transaction output on success, NULL upon failure
 */
unspent_tx_out_t *unspent_tx_out_create(
										uint8_t block_hash[SHA256_DIGEST_LENGTH],
										uint8_t tx_id[SHA256_DIGEST_LENGTH],
										tx_out_t const *out)
{
	unspent_tx_out_t *t;

	t = malloc(sizeof(unspent_tx_out_t));

	if (t == NULL)
		return (NULL);

	memcpy(t->block_hash, block_hash, sizeof(t->block_hash));
	memcpy(t->tx_id, tx_id, sizeof(t->tx_id));
	memcpy(&t->out, out, sizeof(t->out));

	return (t);

}
