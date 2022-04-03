#include "blockchain.h"

/**
 * blockchain_serialize -  serializes a Blockchain into a file
 * @blockchain: points to blockchain to be serialized
 * @path: contains the path to a file to serialize blockchain into
 *        if path points to an existing file, it must be overwritten
 * Return: 0 on succes, -1 failure
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	int fd;
	uint8_t encoding = _get_endianness();

	if (blockchain == NULL || path == NULL)
		return (-1);

	fd = open(path, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (-1);

	serialize_blockchain(fd, encoding, blockchain);
	serialize_blocks(fd, blockchain->chain);
	close(fd);
	return (0);
}

/**
 * serialize_blockchain - serializes a Blockchain into a file
 * @fd: file descriptor
 * @encoding: encoding
 * @blockchain: chain of blocks
 **/
void serialize_blockchain(int fd, int encoding, blockchain_t const *blockchain)
{
	int blocks;

	blocks = llist_size(blockchain->chain);
	write(fd, HBLK_MAGIC, sizeof(HBLK_MAGIC) - 1);
	write(fd, HBLK_VERSION, sizeof(HBLK_VERSION) - 1);
	write(fd, &encoding,  sizeof(encoding));
	write(fd, &blocks,  sizeof(blocks));
}

/**
 * serialize_blocks - serializes blocks
 * @fd: file descriptor
 * @chain: chain of blocks
 **/
void serialize_blocks(int fd, llist_t *chain)
{
	int i;

	for (i = 0; i < llist_size(chain); i++)
	{
		block_t *block = llist_get_node_at(chain, i);

		write(fd, &block->info.index, sizeof(block->info.index));
		write(fd, &block->info.difficulty, sizeof(block->info.difficulty));
		write(fd, &block->info.timestamp, sizeof(block->info.timestamp));
		write(fd, &block->info.nonce, sizeof(block->info.nonce));
		write(fd, block->info.prev_hash, sizeof(block->info.prev_hash));
		write(fd, &block->data.len, sizeof(block->data.len));
		write(fd, block->data.buffer, block->data.len);
		write(fd, block->hash, sizeof(block->hash));
	}
}
