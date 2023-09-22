#include "main.h"

unsigned int _free_buffer(buffer_t *output);
unsigned int _memory_copy(buffer_t *output, const char *src, unsigned int m);
buffer_t *initialize_buffer(void);

/**
 * _free_buffer - Frees a buffer_t struct
 * @output: The buffer_t to be freed
 */

void _free_buffer(buffer_t *output)
{
	free(output->start);
	free(output);
}

/**
 * _memory_copy - Copies m bytes from memory area src to
 * the buffer contained in buffer_t struct
 * @output: A buffer_t struct
 * @src: A pointer to the memory area to copy
 * @m: Number of bytes to be copied
 *
 * Return: Number of bytes copied
 */

unsigned int _memory_copy(buffer_t *output, const char *src, unsigned int m)
{
	unsigned int indx;

	for (indx = 0; indx < n; indx++)
	{
		*(output->buffer) = *(src + indx);
		(output->length)++;

		if (output->length == 1024)
		{
			write(1, output->start, output->length);
			output->buffer = output->start;
			output->len = 0;
		}

		else
			(output->buffer)++;
	}

	return (m);
}

/**
 * initialize_buffer - Initializes a variable of struct type buffer_t
 *
 * Return: Pointer to the initialized buffer_t
 */

buffer_t *initialize_buffer(void)
{
	buffer_t *output;

	output = malloc(sizeof(buffer_t));
	if (output == NULL)
	{
		return (NULL);
	}

	output->buffer = malloc(sizeof(char) * 1024);
	if (output->buffer == NULL)
	{
		free(output);
		return (NULL);
	}

	output->start = output->buffer;
	output->length = 0;

	return (output);
}
