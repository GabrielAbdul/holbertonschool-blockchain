#include "hblk_crypto.h"

/**
 * ec_load - loads an existing EC Key pair from the disk
 * @folder: path to the folder to save the keys
 * Return: pointer to created EC_key pair on success, or NULL on failure
 */
EC_KEY *ec_load(char const *folder)
{
	EC_KEY *keys = NULL;

	if (folder == NULL)
		return (NULL);

	if (
		/* attempt to load public key from file */
		load_key_from_file(&keys, folder, PUBKEY) == 0 ||
		/* attempt to load private key from file */
		load_key_from_file(&keys, folder, PRIVKEY) == 0
	)
	{
		EC_KEY_free(keys);
		return (0);
	}

	if (keys == NULL)
		printf("%p\n", (void *)keys);
	return (keys);
}

/**
 * load_key_from_file - loads the public or private key from a file
 * @keys: double pointer to EC_KEY pair obj
 * @folder: folder where files will be written to
 * @key_type: either Private or Public key
 * Return: 1 on success, 0 on failure
 */
int load_key_from_file(EC_KEY **keys, char const *folder, int key_type)
{
	FILE *f;
	char file_path[FILE_PATH_LEN];

	switch (key_type)
	{
		case PUBKEY:

			/* form file path using folder */
			sprintf(file_path, "%s/%s", folder, PUB_FILENAME);

			/* open the file and read the private key */
			f = fopen(file_path, "r");
			if (f == NULL || PEM_read_EC_PUBKEY(f, keys, NULL, NULL) == 0)
			{
				fclose(f);
				return (0);
			}
			break;
		case PRIVKEY:

			/* form file path using folder */
			sprintf(file_path, "%s/%s", folder, PRI_FILENAME);

			/* open the file and read the private key */
			f = fopen(file_path, "r");
			if (
				f == NULL ||
				PEM_read_ECPrivateKey(f, keys, NULL, NULL) == 0
			)
			{
				fclose(f);
				return (0);
			}
			break;
	}
	fclose(f);
	return (1);
}
