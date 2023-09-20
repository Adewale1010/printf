#include "main.h"

unsigned int _convert_unsigned_c(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char len);
unsigned int _convert_percent(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length);
unsigned int _convert_addr_hex(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length);

/**
 * _convert_unsigned_c - Converts an argument to an unsigned char
 * and stores it to a buffer contained in a struct
 * @arg_list: List of arguments
 * @flags: Flag modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: A buffer_t strct containing an array of char
 *
 * Return: Number of bytes stored to the buffer
 */

unsigned int _convert_unsigned_c(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length)
{
	char c;
	unsigned int rem = 0;

	(void)precision;
	(void)length;

	c = va_arg(arg_list, int);

	rem += _print_width(output, rem, flags, width);
	rem += _memory_copy(output, &c, 1);
	rem += _print_negative_width(output, rem, flags, width);

	return (rem);
}

/**
 * _convert_percent - Stores a percent sign to a buffer
 * contained in a struct
 * @arg_list: List of arguments
 * @flags: Flag modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: A buffer_t struct containing an arry of char
 *
 * Return: The number of bytes stored to the buffer
 */

unsigned int _convert_percent(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length)
{
	char percent = '%';
	unsigned int rem;

	rem = 0;

	(void)arg_list;
	(void)precision;
	(void)length;

	rem += _print_width(output, rem, flags, width);
	rem += _memory_copy(output, &percent, 1);
	rem += _print_negative_width(output, rem, flags, width);

	return (rem);
}

/**
 * _convert_addr_hex - Converts the address of an argument to hex
 * and stores it to a buffer contained in a struct
 * @arg_list: List of arguments
 * @flags: Flag Modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: A buffer_t struct containing an array of char
 *
 * Return: Number of bytes stored to the buffer
 */

unsigned int _convert_addr_hex(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length)
{
	char *null = "(nil)";
	unsigned long int addr;
	unsigned int rem = 0;

	(void)length;

	addr = va_arg(arg_list, unsigned long int);
	if (addr == '\0')
		return (_memory_copy(output, null, 5));

	flags |= 32;
	rem += convert_unsigned_base(output, addr, "0123456789abcdef",
			flags, width, precision);
	rem += _print_negative_width(output, rem, flags, width);

	return (rem);
}
