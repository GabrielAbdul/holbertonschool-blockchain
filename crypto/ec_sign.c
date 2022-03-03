#include "hblk_crypto.h"

/**
 * ec_sign - signs a given set of bytes using a given EC_KEY private key
 * @key: points to EC_KEY struct containing private key to be used
 * @msg: points to characters to be signed
 * @msglen: msg length
 * @sig: holds the address at which to store the signature
 * Return: pointer to signature buffer on success, NULL on failure
 */
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
				 size_t msglen, sig_t *sig)
{

	unsigned int siglen;

	if (key == NULL || msg == NULL || sig == NULL)
		return (NULL);

	siglen = sig->len;
	if (ECDSA_sign(0, msg, msglen, sig->sig, &siglen, (EC_KEY *)key) == 0)
		return (NULL);

	sig->len = siglen - 1;
	return (sig->sig);
}
