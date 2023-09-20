#include "main.h"

unsigned int convert_signed_base(buffer_t *output, long int num, char *base,
		unsigned char flags, int width, int precision);
unisigned int convert_unsigned_base(buffer_t *output,
		unsigned long int num, char *base,
		unsigned char flags, int width, int precision);

/**
 * convert_signed_base - Converts a signed long to an inputted
 * base and stores the resul to a buffer contained in a struct
 * @output: A buffer_t struct containing an array of chars
 * @num: A signed long input
 * @base: A pointer to a string containing the base to convert to
 * @flags: Active flag modifiers
 * @width: Width modifiers
 * @precision: Precision modifiers
 *
 * Return: Number of bytes stored to the buffer
 */

unsigned int convert_signed_base(buffer_t *output, long int num, char *base,
		unsigned char flags, int width, int precision)
{
	int size;
	char digit, padding = '0';
	unsigned int rem = 1;

	for (size = 0; *(base + size);)
		size++;

	if (num >= size || num <= -size)
		rem += convert_signed_base(output, num / size, base,
				flags, width - 1, precision - 1);

	else
	{
		for (; precision > 1; precision--, width--)
			rem += _memory_copy(output, &padding, 1);

		if (F_MINUS == 0)
		{
			padding = (F_ZERO == 1) ? '0' : ' ';
			for (; width > 1; width--)
				rem += _memory_copy(output, &padding, 1);
		}
	}

	digit = base[(num < 0 ? -1 : 1) * (num % size)];
	_memory_copy(output, &digit, 1);

	return (rem);
}

/**
 * convert_unsigned_base - Converts an unsigned long to an inputted
 * base and stores the result to a buffer contained in a struct
 * @output: A buffer_t struct containing an array of char
 * @num: An unsigned long to be converted
 * @base: A pointer to a string containing the base to convert to
 * @flags: Flag modifiers
 * @width: Width modifier
 * @precision: Precision modifier
 *
 * Return: The number of bytes stored to the buffer
 */

unsigned int convert_unsigned_base(buffer_t *output, unsigned long int num,
		char *base, unsigned char flags, int width, int precision)
{
	unsigned int size, rem = 1;
	char digit, padding = '0', *l = "0x";

	for (size = 0; *(base + size);)
		size++;

	if (num >= size)
		rem += convert_unsigned_base(output, num / size, base,
				flags, width - 1, precision - 1);

	else
	{
		if (((flags >> 5) & 1) == 1)
		{
			width -= 2;
			precision -= 2;
		}
		for (; precision > 1; precision--, width--)
			rem += _memory_copy(output, &padding, 1);

		if (F_MINUS == 0)
		{
			padding = (F_ZERO == 1) ? '0' : ' ';
			for (; width > 1; width--)
				rem += _memory_copy(output, l, 2);
		}
		if (((flags >> 5) & 1) == 1)
			rem += _memory_copy(output, l, 2);
	}

	digit = base[(num % size)];
	_memory_copy(output, &digit, 1);

	return (rem);
}
