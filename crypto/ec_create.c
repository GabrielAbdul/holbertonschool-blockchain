#include "hblk_crypto.h"

/**
 * ec_create - creates a new EC Key pair
 * Return: pointer to EC_KEY structure or NULL
 */
EC_KEY *ec_create(void)
{
	EC_KEY *keys;

	/* create EC_KEY structure */
	keys = EC_KEY_new_by_curve_name(EC_CURVE);
	if (keys == NULL)
		return (NULL);


	/* generate private and public keys for EC_KEY */
	if (EC_KEY_generate_key(keys) == 0)
	{
		EC_KEY_free(keys);
		return (NULL);
	}

	return (keys);
}
