#include "transaction.h"

/**
 * hash_tx_in - llist action func to hash inputs
 * @txn: tx_in_t * struct
 * @i: index of transaction
 * @addr: address to write to
 * Return: 0 if success else 1
 */
int hash_tx_in(llist_node_t txn, unsigned int i, void *addr)
{
	(void)i;
	memcpy(*(uint8_t **)addr, txn, SHA256_DIGEST_LENGTH * 3);
	*(uint8_t **)addr += SHA256_DIGEST_LENGTH * 3;
	return (0);
}

/**
 * hash_tx_out - llist action func to hash outputs
 * @txn: tx_out_t * struct
 * @i: index of transaction
 * @addr: pointer to address to write to
 * Return: 0 if success else 1
 */
int hash_tx_out(llist_node_t txn, unsigned int i, void *addr)
{
	(void)i;
	memcpy(*(uint8_t **)addr, ((tx_out_t *)txn)->hash, SHA256_DIGEST_LENGTH);
	*(uint8_t **)addr += SHA256_DIGEST_LENGTH;
	return (0);
}

/**
 * transaction_hash - computes hash of given transaction
 * @transaction: pointer to tx to hash
 * @hash_buf: buffer to save hash
 * Return: ptr to buffer or NULL
 */
uint8_t *transaction_hash(transaction_t const *transaction,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	ssize_t len;
	uint8_t *_buf, *buf;

	if (!transaction)
		return (NULL);
	len = SHA256_DIGEST_LENGTH * 3 * llist_size(transaction->inputs)
		+ SHA256_DIGEST_LENGTH * llist_size(transaction->outputs);
	_buf = buf = calloc(1, len);
	if (!_buf)
		return (NULL);
	llist_for_each(transaction->inputs, hash_tx_in, &buf);
	llist_for_each(transaction->outputs, hash_tx_out, &buf);
	if (!sha256((const int8_t *)_buf, len, hash_buf))
		hash_buf = NULL;
	free(_buf);
	return (hash_buf);
}
