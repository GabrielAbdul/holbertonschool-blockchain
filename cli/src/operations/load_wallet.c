#include "../utils/utils.h"

#define PRINT printf("hello\n")

/**
 * wallet_load - wallet_load function
 * @args: command arguments
 * Return: status
 **/
int wallet_load(char **args)
{
	char *folder = args[1] ? args[1] : ".";
	EC_KEY *wallet;
	uint8_t pub[EC_PUB_LEN], i;

	wallet = ec_load(folder);
	if (!wallet)
	{
		printf("No wallet in folder [%s]\n", folder);
WALLET_LOAD_CREATE_KEY_CONFIRM:
		printf("Create new key? [y/n]: ");
		getline(&line, &line_size, stdin);

		if (*line != 'y' && *line != 'n')
		{
			printf("Invalid input\n");
			goto WALLET_LOAD_CREATE_KEY_CONFIRM;
		}

		if (*line == 'n')
		{
			printf("Aborting.\n");
			return (-1);
		}

		printf("Creating new wallet\n");
		wallet = ec_create();

		if (!wallet)
		{
			print_error("wallet_load: failed to create wallet");
			return (errno);
		}

		if (ec_save(wallet, folder) == -1)
		{
			print_error("wallet_load: failed to save wallet");
			return (errno);
		}
	}

	if (llist_add_node(wallets, wallet, ADD_NODE_REAR) == -1)
	{
		print_error("wallet_load: failed to add to wallets list");
		EC_KEY_free(wallet);
		return (errno);
	}

	printf("Wallet loaded");

	if (strcmp(folder, "."))
		printf(" from %s\n", folder);
	else
		printf("\n");

	printf("Wallet address: ");
	ec_to_pub((const EC_KEY *)wallet, pub);
	for (i = 0; (size_t)i < sizeof(pub) / sizeof(uint8_t); i++)
		printf("%02x", pub[i]);
	printf("\n");


	current_wallet = wallet;
	llist_add_node(wallets, wallet, ADD_NODE_REAR);

	return (0);
}
