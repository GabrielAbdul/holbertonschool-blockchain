#include "transaction.h"

/**
 * tx_in_create - initializes a transaction input structure
 * @unspent: unspent transaction output to be converted to input
 * Return: created transaction input upon success, or NULL upon failure
 */
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *t;

	t = malloc(sizeof(tx_in_t));

	if (t == NULL || unspent == NULL)
		return (NULL);

	/* init data */
	memcpy(t, unspent, sizeof(t->block_hash) + sizeof(t->tx_id));
	memcpy(t->tx_out_hash, &unspent->out.hash, sizeof(t->tx_out_hash));
	memset(&t->sig, 0, sizeof(t->sig));

	return (t);
}
