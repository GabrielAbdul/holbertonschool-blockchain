#define BUFSIZE 4096
#define NULL_CLEAN (close(fd), free(blockchain), NULL)
#define LIN (close(fd), free(block), llist_destroy(blockchain->chain, 1, NULL))
#define READBUF(x) ((memset(buf, 0, BUFSIZE)), read(fd, buf, x))
#define SPREADBUF(x) ((memset(buf, 0, BUFSIZE)), spread(fd, endianess, buf, x))
#include "blockchain.h"
llist_t *read_blocks(blockchain_t *blockchain, size_t size,
		int fd, uint8_t endianess);
/**
 * spread - writes an attribute into a file in the proper endian
 * @fd: file descriptor
 * @endianess: file endian
 * @attr: attribute to read
 * @size: size of attribute
 **/
static void spread(int fd, int endianess, void *attr, size_t size)
{
	read(fd, attr, size);
	if (!endianess)
		_swap_endian((uint8_t *)attr, size);
}

/**
 * blockchain_deserialize - Loads a blockchain structure from path
 * @path: path to get the info from
 *
 * Return: Blockchain structure
 */
blockchain_t *blockchain_deserialize(char const *path)
{
	int fd;
	blockchain_t *blockchain = NULL;
	char buf[BUFSIZE];
	uint8_t endianess;
	uint8_t size = 0;

	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	READBUF(strlen(HBLK_MAGIC));
	if (strcmp(buf, HBLK_MAGIC))
		return (NULL_CLEAN);
	READBUF(strlen(HBLK_VERSION));
	if (strcmp(buf, HBLK_VERSION))
		return (NULL_CLEAN);
	READBUF(1);
	endianess = *buf;
	blockchain = blockchain_create();
	block_destroy((block_t *)llist_pop(blockchain->chain));
	SPREADBUF(4);
	size = *buf;
	blockchain->chain = read_blocks(blockchain, size, fd, endianess);
	if (!(blockchain->chain))
		return (NULL);
	close(fd);
	return (blockchain);
}
/**
 * read_blocks - reads blocks from the the structure
 * @blockchain: blockchain structure
 * @size: size of blocks
 * @fd: file descriptor or readed file
 * @endianess: endianess file conf
 * Return: Blockchain structure or null in error
 */
llist_t *read_blocks(blockchain_t *blockchain,
		size_t size, int fd, uint8_t endianess)
{
	size_t i;
	block_t *block = NULL;
	char buf[BUFSIZE];

	for (i = 0; i < size; i++)
	{
		block = calloc(1, sizeof(*block));
		if (!block)
			return (NULL);
		SPREADBUF(sizeof(block->info.index));
		memcpy(&(block->info.index), buf, sizeof(block->info.index));
		SPREADBUF(sizeof(block->info.difficulty));
		memcpy(&(block->info.difficulty), buf, sizeof(block->info.difficulty));
		SPREADBUF(sizeof(block->info.timestamp));
		memcpy(&(block->info.timestamp), buf, sizeof(block->info.timestamp));
		SPREADBUF(sizeof(block->info.nonce));
		memcpy(&(block->info.nonce), buf, sizeof(block->info.nonce));
		SPREADBUF(sizeof(block->info.prev_hash));
		memcpy(block->info.prev_hash, buf, sizeof(block->info.prev_hash));
		SPREADBUF(sizeof(block->data.len));
		memcpy(&(block->data.len), buf, sizeof(block->data.len));
		SPREADBUF(block->data.len);
		memcpy(block->data.buffer, buf, block->data.len);
		SPREADBUF(sizeof(block->hash));
		memcpy(block->hash, buf, sizeof(block->hash));
		llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
	}
	return ((llist_t *) blockchain->chain);
}
