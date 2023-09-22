#include "main.h"

unsigned int convert_lower_string(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_upper_string(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_rot13_string(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_reverse_string(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length);

/**
 * convert_lower_string - Converts an argument to a string
 * in lowercase
 * @arg_list: List of arguments
 * @flags: Flag modifier
 * @width: Width Modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: buffer_t struct containing an array of char
 *
 * Return: Number of bytes stored to the buffer
 */

unsigned int convert_lower_string(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length)
{
	int size;
	char *str, *null = "(null)";
	unsigned int rem;

	rem = 0;

	(void)flags;
	(void)length;

	str = va_arg(arg_list, char *);
	if (str == NULL)
	{
		return (_memory_copy(output, null, 6));
	}

	for (size = 0; *(str + size);)
	{
		size++;
	}

	rem += _print_string_width(output, flags, width, precision, size);

	precision = (precision == -1) ? size : precision;
	while (*str != '\0' && precision > 0)
	{
		rem += _memory_copy(output, str, 1);
		precision--;
		str++;
	}

	rem += _print_negative_width(output, rem, flags, width);

	return (rem);
}

/**
 * convert_upper_string - Converts an argument to a string
 * in uppercase
 * @arg_list: List of arguments
 * @flags: Flag modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: buffer_t struct containing an array of char
 *
 * Return: Number of bytes stores to the buffer
 *
 * Description: Non-printable chars are stored as \x followed
 * by the ASCII code in hex
 */

unsigned int convert_upper_string(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length)
{
	int size, i;
	unsigned int rem;
	char *str, *null = "(null)", zero = '0', *hex = "\\x";

	rem = 0;

	(void)length;
	str = va_arg(arg_list, char *);
	if (str == NULL)
	{
		return (_memory_copy(output, null, 6));
	}

	for (size = 0; str[size];)
	{
		size++;
	}

	rem += _print_string_width(output, flags, width, precision, size);

	precision = (precision == 1) ? size : precision;
	for (i = 0; *(str + i) != '\0' && i < precision; i++)
	{
		if (*(str + i) < 32 || *(str + i) >= 127)
		{
			rem += _memory_copy(output, hex, 2);
			if (*(str + i) < 16)
			{
				rem += _memory_copy(output, &zero, 1);
			}
			rem += convert_unsigned_base(output, *(str + i),
					"0123456789ABCDEF", flags, 0, 0);
			continue;
		}
		rem += _memory_copy(output, (str + i), 1);
	}

	rem += _print_negative_width(output, rem, flags, width);

	return (rem);
}

/**
 * convert_rot13_string - Converts a string to ROT13
 * @arg_list: List of arguments
 * @flags: Flag modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: buffer_t struct containing an array of char
 *
 * Return: Number of bytes stored to the buffer
 */

unsigned int convert_rot13_string(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length)
{
	int index, k, size;
	unsigned int rem;
	char *str, *null = "(null)";
	char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";

	rem = 0;

	(void)flags;
	(void)length;

	str = va_arg(arg_list, char *);
	if (str == NULL)
	{
		return (_memory_copy(output, null, 6));
	}

	for (size = 0; *(str + size);)
	{
		size++;
	}

	rem += _print_string_width(output, flags, width, precision, size);

	precision = (precision == -1) ? size : precision;
	for (index = 0; *(str + index) != '\0' && index < precision; index++)
	{
		for (k = 0; k < 52; k++)
		{
			if (*(str + index) == *(alphabet + k))
			{
				rem += _memory_copy(output, (rot13 + k), 1);
				break;
			}
		}
		if (k == 52)
		{
			rem += _memory_copy(output, (str + index), 1);
		}
	}

	rem += _print_negative_width(output, rem, flags, width);

	return (rem);
}

/**
 * convert_reverse_string - Reverses a string
 * @arg_list: List of arguments
 * @flags: Flag modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: buffer_t strcut containing an array of char
 *
 * Return: Number of bytes stored to the buffer
 */

unsigned int convert_reverse_string(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length)
{
	int size, last, index;
	char *str, *null = "(null)";
	unsigned int rem;

	rem = 0;

	(void)flags;
	(void)length;

	str = va_arg(arg_list, char *);
	if (str == NULL)
	{
		return (_memory_copy(output, null, 6));
	}

	for (size = 0; *(str + size);)
	{
		size++;
	}

	rem += _print_string_width(output, flags, width, precision, size);

	last = size - 1;
	precision = (precision == -1) ? size : precision;
	for (index = 0; last >= 0 && index < precision; index++)
	{
		rem += _memory_copy(output, (str + last), 1);
		last--;
	}

	rem += _print_negative_width(output, rem, flags, width);

	return (rem);
}
