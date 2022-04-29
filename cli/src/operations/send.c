#include "../utils/utils.h"


/**
 * send - send function
 * @args: command arguments
 * Return: status
 **/
int send(char **args)
{
	uint32_t amount;
	const EC_KEY *address;
	transaction_t *transaction;

	if (!blockchain)
	{
		fprintf(stderr, "ERROR: No blockchain loaded.\n");
		fprintf(stderr, "Use command `load` to load a blockchain.\n");
		return (-1);
	}

	if (!args[1] || !args[2])
	{
		fprintf(stderr, "Usage: send <amount> <address>\n");
		return (-1);
	}

	if (!(amount = get_amount(args[1])))
	{
		fprintf(stderr, "Amount must be positive integer\n");
		return (-1);
	}

	if (!(address = get_key(args[2])))
	{
		fprintf(stderr, "ERROR: Invalid wallet address\n");
		return (-1);
	}
	if (
		!(transaction = transaction_create(
								current_wallet,
								address,
								amount,
								blockchain->unspent
								))
	)
	{
		print_error("send: could not create transaction");
		return (errno);
	}
	if (!transaction_is_valid(transaction, blockchain->unspent))
	{
		print_error("send: could not validate transaction");
		transaction_destroy(transaction);
		return (-1);
	}
	if (llist_add_node(transaction_pool, transaction, ADD_NODE_REAR) == -1)
	{
		print_error("send: could not add transaction to transaction pool");
		transaction_destroy(transaction);
		return (errno);
	}
	printf("Transaction added to transaction pool\n");
	return (0);
}
