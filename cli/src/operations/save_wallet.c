#include "../utils/utils.h"


/**
 * wallet_save - wallet_save function
 * @args: command arguments
 * Return: status
 **/
int wallet_save(char **args)
{
	char *folder = args[1] ? args[1] : ".";

	if (!current_wallet)
	{
		fprintf(stderr, "ERROR: No wallet is currently loaded.\n");
		fprintf(stderr, "Use `wallet_load` to create a new wallet.\n");
		return (-1);
	}

	if (ec_save(current_wallet, folder) == -1)
	{
		print_error("wallet_save: failed to save wallet");
		return (errno);
	}

	if (!args[1])
		printf("Wallet saved in current folder.\n");
	else
		printf("Wallet saved in folder [%s]\n", folder);

	return (0);
}
