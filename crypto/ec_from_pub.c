#include "hblk_crypto.h"

/**
 * ec_from_pub - creates an EC_KEY structure given a public key
 * @pub: contains the public key to be converted
 * Return: pointer to created EC_KEY structure, or NULL
 */
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *keys;
	const EC_GROUP *curve;
	EC_POINT *public_key;

	if (pub == NULL)
		return (NULL);
		
	/* create EC_KEY structure based on curve*/
	keys = EC_KEY_new_by_curve_name(EC_CURVE);
	/* retrieve curve from newly created key struct */
	curve = EC_KEY_get0_group(keys);
	/* retrieve public key (point on curve) from curve */
	public_key = EC_POINT_new(curve);

	/* check return values */
	if (keys == NULL || curve == NULL || public_key == NULL)
	{
		EC_KEY_free(keys);
		EC_POINT_free(public_key);
		return (NULL);
	}

	/* convert EC_POINT into octet | set public key to corresponding EC_KEY obj */
	if (
		(EC_POINT_oct2point(curve, public_key, pub, EC_PUB_LEN, NULL) == 0) ||
		(EC_KEY_set_public_key(keys, public_key) == 0)
	)
	{
		EC_KEY_free(keys);
		EC_POINT_free(public_key);
		return (NULL);
	}

	EC_POINT_free(public_key);

	return (keys);
}
