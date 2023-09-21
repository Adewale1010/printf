#include "main.h"

unsigned int convert_lower_hexa(va_list arg_list,
		buffer_t *output, unsigned char flags,
		int width, int precision, unsigned char length);
unsigned int convert_upper_hexa(va_list arg_list,
		buffer_t *output, unsigned char flags,
		int width, int precision, unsigned char length);

/**
 * convert_lower_hexa - Converts an unsigned int to hex
 * using abcdef
 * @arg_list: List of arguments
 * @flags: Flag modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: buffer_t struct containing an array of char
 *
 * Return: The number of bytes stored to the buffer
 */

unsigned int convert_lower_hex(va_list arg_list,
		buffer_t *output, unsigned char flags,
		int width, int precision, unsigned char length)
{
	unsigned int rem;
	unsigned long int num;
	char *l = "0x";

	rem = 0;

	if (length == LONG)
		num = va_arg(arg_list, unsigned long int);
	else
		num = va_arg(arg_list, unsigned int);
	if (length == SHORT)
		num = (unsigned short)num;

	if (F_HASH == 1 && num != 0)
	{
		rem += convert_unsigned_base(output, num, "0123456789abcdef",
				flags, width, precision);
	}

	rem += _print_negative_width(output, rem, flags, width);

	return (rem);
}

/**
 * convert_upper_base - Converts an unsigned int to hex
 * using ABCDEF
 * @arg_list: List of arguments
 * @flags: Flag modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: buffer_t struct containing an array of char
 *
 * Return: Number of bytes containing an array of char
 */

unsigned int convert_upper_hex(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length)
{
	unsigned int rem;
	unsigned long int num;
	char *l = "0X";

	rem = 0;

	if (length == LONG)
	{
		num =  va_arg(arg_list, unsigned long);
	}
	else
	{
		num = va_arg(arg_list, unsigned int);
	}
	if (length == SHORT)
	{
		num = (unsigned short)num;
	}

	if (F_HASH == 1 && num != 0)
	{
		rem += _memory_copy(output, l, 2);
	}

	if (!(num == 0 && precision == 0))
	{
		rem += convert_unsigned_base(output, num, "0123456789ABCDEF",
				flags, width, precision);
	}

	rem += _print_negative_width(output, rem, flags, width);

	return (rem);
}
