#include "utils.h"

/**
 * EC_KEY - Retrives EC_Key
 * @s: string representation of pub key
 * Return: EC KEY REP from string or null if failed
 **/
const EC_KEY *get_key(char *s)
{
	int i;
	uint8_t tmp, pub[EC_PUB_LEN];
	char buf[3];


	if (!s)
		return (NULL);

	for (i = 0; i < 2 * EC_PUB_LEN; i++)
		if (!is_numeric(s[i]) && !is_lowercase_alpha(s[i]))
			return (NULL);

	if (s[i] != '\0')
		return (NULL);

	for (i = 0; i < EC_PUB_LEN; i++) /* interpret hex string */
	{
		memcpy(buf, s + (2 * i), 2);
		tmp = strtoul(buf, NULL, 16);
		memcpy(pub + i, &tmp, sizeof(uint8_t));
	}

	return (ec_from_pub(pub));
}

/**
 * get_amount - gets amoun from String
 * @s: string to get the info from
 * Return: Amount detected
 **/
uint32_t get_amount(char *s)
{
	int i;

	if (!s)
		return (0);

	for (i = 0; s[i]; i++)
		if (s[i] < '0' || s[i] > '9')
			return (0);

	return ((uint32_t)strtoul(s, NULL, 10));
}
