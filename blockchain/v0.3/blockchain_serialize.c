#include "blockchain.h"

/**
 * spwrite - writes an attribute into a file in the proper endian
 * @fd: file descriptor
 * @endianess: file endian
 * @attr: attribute to write
 * @size: size of attribute
 **/
static void spwrite(int fd, int endianess, void *attr, size_t size)
{
	if (!endianess)
		_swap_endian((uint8_t *)attr, size);
	write(fd, attr, size);
}

/**
 * block_content - serializes blocks
 * @fd: file descriptor
 * @endian: file endianess
 * @list: list of blocks
 **/
static void block_content(int fd, int endian, llist_t *list)
{
	block_t *block;
	int i;

	for (i = 0; i < llist_size(list); i++)
	{
		block = llist_get_node_at(list, i);
		spwrite(fd, endian, &block->info.index,      sizeof(block->info.index));
		spwrite(fd, endian, &block->info.difficulty, sizeof(block->info.difficulty));
		spwrite(fd, endian, &block->info.timestamp,  sizeof(block->info.timestamp));
		spwrite(fd, endian, &block->info.nonce,      sizeof(block->info.nonce));
		spwrite(fd, endian, block->info.prev_hash,   sizeof(block->info.prev_hash));
		spwrite(fd, endian, &block->data.len,        sizeof(block->data.len));
		spwrite(fd, endian, block->data.buffer,      block->data.len);
		spwrite(fd, endian, block->hash,             sizeof(block->hash));
	}
}

/**
 * blockchain_serialize - serializes a Blockchain into a file
 * @blockchain: points to the Blockchain to be serialized,
 * @path: contains the path to a file to serialize the Blockchain into
 *            * If path points to an existing file, it must be overwritten
 * Return: 0 upon success, or -1 upon failure
 **/
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	int fd, num_blocks;
	uint8_t endiannes = _get_endianness();

	if (!blockchain || !path)
		return (-1);
	fd = open(path, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (-1);
	num_blocks = llist_size(blockchain->chain);
	write(fd, HBLK_MAGIC,   strlen(HBLK_MAGIC));
	write(fd, HBLK_VERSION, strlen(HBLK_VERSION));
	write(fd, &endiannes,  sizeof(endiannes));
	write(fd, &num_blocks,  sizeof(num_blocks));
	block_content(fd, endiannes, blockchain->chain);
	close(fd);
	return (0);
}
