#include "main.h"

unsigned int _print_string_width(buffer_t *output, unsigned char flags,
		int width, int precision, int size);
unsigned int _print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int width);
unsigned int _print_negative_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int width);

/**
 * _print_string_width - Stores leading spaces to a buffer for a width
 * modifier
 * @flags: Flag modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @size: Size of the string
 *
 * Return: Number of bytes stored to the buffer
 */

unsigned int _print_string_width(buffer_t *output, unsigned char flags,
		int width, int precision, int size)
{
	char wid = ' ';
	unsigned int rem;

	rem = 0;

	if (F_MINUS == 0)
	{
		width -= (precision == -1) ? size : precision;
		for (; width > 0; width--)
		{
			rem += _memory_copy(output, &wid, 1);
		}
	}

	return (rem);
}

/**
 * _print-width - Stores leading spaces to a buffer for a width modifier
 * @output: buffer_t struct containing an array of char
 * @printed: Current number of chars already printed to the output for a
 * given number of specifiers
 * @flags: Flag modifier
 * @width: Width modifier
 *
 * Return: Number of bytes stored to the buffer
 */

unsigned int _print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int width)
{
	char wid = ' ';
	unsigned int rem;

	rem = 0;

	if (F_MINUS == 0)
	{
		for (width -= printed; width > 0;) 
		{
			rem += _memory_copy(output, &wid, 1);
		}
	}

	return (rem);
}

/**
 * _print_negative_width - Stores trailing spaces to a buffer for '-' flag
 * @output: buffer_t struct containing an array of char
 * @printed: Current number of bytes already stored to output for given
 * number of specifier
 * @flags: Flag modifier
 * @width: Width modifier
 *
 * Return: Number of bytes stored to the buffer
 */

unsigned int _print_negative_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int width)
{
	char wid = ' ';
	unsigned int rem;

	rem = 0;

	if (F_MINUS == 1)
	{
		for (width -= printed; width > 0; width--)
		{
			rem += _memory_copy(output, &wid, 1);
		}
	}

	return (rem);
}
