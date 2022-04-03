#include "transaction.h"

/**
 * tx_out_create - allocates and initializes a transaction output structure
 * @amount: amount of the transaction
 * @pub: public key of the transaction receiver
 * Return: created transaction output upon success, or NULL upon failure
 */
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *transaction;

	transaction = malloc(sizeof(tx_out_t));

	if (transaction == NULL)
		return (NULL);

	transaction->amount = amount;
	memcpy(transaction->pub, pub, sizeof(transaction->pub));
	sha256((int8_t const *)transaction,
			sizeof(transaction->amount) + sizeof(transaction->pub),
			transaction->hash);

	return (transaction);
}
