#include "hblk_crypto.h"

/**
 * ec_to_pub - extracts the public key from an EC_KEY
 *             opaque structure
 * @key: pointer to the EC_KEY structure to retrieve the pub key from
 * @pub: the address at which to store the extracted public key
 * Return: pointer to pub or NULL on failure
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_GROUP *group;
	const EC_POINT *point;

	if (key == NULL)
		return (NULL);
		
	/* retreive eliptic curve stored in EC_KEY struct*/
	group = EC_KEY_get0_group(key);

	/* retrieve public key (a point on the curve) */
	point = EC_KEY_get0_public_key(key);

	if (point == NULL || group == NULL)
		return (NULL);

	/* convert from EC_POINTS to octet string */
	if (EC_POINT_point2oct(group, point,
		POINT_CONVERSION_UNCOMPRESSED, pub, EC_PUB_LEN, NULL) == 0)
		return (NULL);
	return (pub);
}
