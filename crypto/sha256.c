#include "hblk_crypto.h"

/**
 * sha256 - computes the has of a sequence of bytes
 * @s: sequence of bytes to be hased
 * @len: number of bytes to hash in s
 * @digest: buffer
 * Return: pointer to digest or NULL
 */
uint8_t *sha256(int8_t const *s, size_t len,
				uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (s == NULL || digest == NULL)
		return (NULL);

	return (SHA256((const unsigned char *)s, len, digest));
}
