#include "transaction.h"

/**
 * tx_in_sign - signs a transaction input, given the transaction id it is from
 * @in: transaction input to sign
 * @tx_id: contains the ID (hash) of the transaction of in
 * @sender: private key of transaction reciever
 * @all_unspent: list of all unspent transaction outputs to date
 * Return: pointer to resulting sig struct, else NULL on failure
 */
sig_t *tx_in_sign(tx_in_t *in, uint8_t const tx_id[SHA256_DIGEST_LENGTH],
	EC_KEY const *sender, llist_t *all_unspent)
{
	uint8_t pub[EC_PUB_LEN];
	unspent_tx_out_t *utx;
	ssize_t index;

	/* loop through all unspent transactions */
	for (index = 0; index < llist_size(all_unspent); index++)
	{
		/* verify the pub key from sender = the pub key stored in out hash */
		utx = llist_get_node_at(all_unspent, index);
		if (!memcmp(in->tx_out_hash, utx->out.hash, SHA256_DIGEST_LENGTH))
			break;
		utx = NULL;
	}

	/* if pub key failed to be verified return NULL */
	if (!utx || !ec_to_pub(sender, pub) || memcmp(pub, utx->out.pub, EC_PUB_LEN))
		return (NULL);

	/* sign the id using the senders private key */
	if (ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &in->sig) == NULL)
		return (NULL);

	return (&in->sig);
}
