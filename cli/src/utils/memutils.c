#include "utils.h"


/**
 * realloc_array - reallocates an array
 * @arr: pointer to array
 * @arr_size: pointer to array size
 * Return: pointer to reallocated array
 **/
void *realloc_array(void *arr, size_t *arr_size)
{
	*arr_size += (3 * sizeof(char *));
	return (realloc(arr, *arr_size));
}