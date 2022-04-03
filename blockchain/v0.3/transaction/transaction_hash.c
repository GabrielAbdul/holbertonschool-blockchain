#include "transaction.h"

/**
 * transaction_hash - computes the ID (hash) of a transaction
 * @transaction: transaction to compute hash of
 * @hash_buf: buffer to store the computed hash
 * Return: pointer to hash_buf
 */
uint8_t *transaction_hash(transaction_t const *transaction,
						  uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
    
}