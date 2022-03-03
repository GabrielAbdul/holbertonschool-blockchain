#include "hblk_crypto.h"

/**
 * ec_verify - verifies a given set of bytes using a given EC_KEY private key
 * @key: points to EC_KEY struct containing private key to be used
 * @msg: points to characters to be signed
 * @msglen: msg length
 * @sig: holds the address at which to store the signature
 * Return: 1 if sig is valid else 0
 */
int ec_verify(EC_KEY const *key, uint8_t const *msg,
			  size_t msglen, sig_t const *sig)
{
	if (key == NULL || msg == NULL || sig == NULL || sig->len == 0)
		return (0);

	if (ECDSA_verify(0, msg, msglen, sig->sig, sig->len, (EC_KEY *)key) == 0)
		return (0);

	return (1);
}
