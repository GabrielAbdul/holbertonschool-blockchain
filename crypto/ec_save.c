#include "hblk_crypto.h"

/**
 * ec_save - saves an existing EC Key pair on the disk
 * @key: EC_KEY strucutre containing key pair
 * @folder: path to the folder to save the keys
 *          MUST BE CREATED IF IT DOESNT EXIST
 * Return: 1 on success or 0 on failure
 */
int ec_save(EC_KEY *key, char const *folder)
{
	if (key == NULL || folder == NULL)
		return (0);

	/* create directory if it isnt there */
	if (mkdir(folder, 0775) < 0)
		return (0);

	if (
		/* attempt to write public key to file */
		save_key_to_file(key, folder, PUBKEY) == 0 ||
		/* attempt to write private key to file */
		save_key_to_file(key, folder, PRIVKEY) == 0
	)
		return (0);

	return (1);
}

/**
 * save_key_to_file - writes the public or private key to a file
 *                    inside of folder
 * @key: EC_KEY structure to extract keys from
 * @folder: folder where files will be written to
 * @key_type: either Private or Public key
 * Return: 1 on success, 0 on failure
 */
int save_key_to_file(EC_KEY *key, char const *folder, int key_type)
{
	FILE *f;
	char file_path[FILE_PATH_LEN];

	switch (key_type)
	{
		case PUBKEY:

			/* form file path using folder */
			sprintf(file_path, "%s/%s", folder, PUB_FILENAME);

			/* open the file and write the private key */
			f = fopen(file_path, "w");
			if (f == NULL || PEM_write_EC_PUBKEY(f, key) == 0)
			{
				fclose(f);
				return (0);
			}
			break;
		case PRIVKEY:

			/* form file path using folder */
			sprintf(file_path, "%s/%s", folder, PRI_FILENAME);

			/* open the file and write the private key */
			f = fopen(file_path, "w");
			if (
				f == NULL ||
				PEM_write_ECPrivateKey(f, key, NULL, NULL, 0, NULL, NULL) == 0
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
