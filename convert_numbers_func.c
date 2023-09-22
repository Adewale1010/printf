#include "main.h"

unsigned int _convert_decimal(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length);
unsigned int _convert_signed_int(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length);
unsigned int _convert_binary(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length);
unsigned int _convert_octal(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length);

/**
 * _convert_decimal - Converts an unsigned int arguments to decimal
 * @arg_list: List of arguments
 * @flags: Flag modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: Output modifier
 *
 * Return: Number of bytes stored to the buffer
 */

unsigned int _convert_decimal(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length)
{
	unsigned int rem;
	unsigned long int num;

	rem = 0;

	if (length == LONG)
	{
		num = va_arg(arg_list, unsigned long int);
	}
	else
	{
		num = va_arg(arg_list, unsigned int);
	}
	if (length == SHORT)
	{
		num = (unsigned short)num;
	}

	if (!(num == 0 && precision == 0))
	{
		rem += convert_unsigned_base(output, num, "0123456789",
				flags, width, precision);
	}

	rem += _print_negative_width(output, rem, flags, width);

	return (rem);
}

/**
 * _convert_signed_int - Converts an argument to a signed int
 * @arg_list: List of arguments
 * @flags: Flag modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: buffer_t struct containing an array of char
 *
 * Return: Number of bytes stored to a buffer
 */

unsigned int _convert_signed_int(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length)
{
	unsigned int rem, count;
	long int s, dup;
	char padding, space = ' ', plus = '+', minus = '-';

	rem = 0;
	count = 0;

	if (length == LONG)
	{
		s = va_arg(arg_list, long int);
	}
	else
	{
		s = va_arg(arg_list, int);
	}
	if (length == SHORT)
	{
		s = (short)s;
	}

	if (F_SPACE == 1 && s >= 0)
	{
		rem += _memory_copy(output, &space, 1);
	}

	if (precision <= 0 && F_MINUS == 0)
	{
		if (s == LONG_MIN)
		{
			count += 19;
		}
		else
		{
			for (dup = (s < 0) ? -s : s; dup > 0; dup /= 10)
				count++;
		}
		count += (s == 0) ? 1 : 0;
		count += (s < 0) ? 1 : 0;
		count += (F_PLUS == 1 && s >= 0) ? 1 : 0;
		count += (F_MINUS == 1 && s >= 0) ? 1 : 0;

		if (F_ZERO == 1 && F_PLUS == 1 && s >= 0)
		{
			rem += _memory_copy(output, &plus, 1);
		}
		if (F_ZERO == 1 && s < 0)
		{
			rem += _memory_copy(output, &minus, 1);
		}

		padding = (F_ZERO == 1) ? '0' : ' ';
		for (width -= count; width > 0; width--)
		{
			rem += _memory_copy(output, &padding, 1);
		}
	}

	if (F_ZERO == 0 && s < 0)
	{
		rem += _memory_copy(output, &minus, 1);
	}
	if (F_ZERO == 0 && (F_PLUS == 1 && s >= 0))
	{
		rem += convert_signed_base(output, s, "0123456789",
				flags, 0, precision);
	}

	rem += _print_negative_width(output, rem, flags, width);

	return (rem);
}

/**
 * _convert_binary - Converts an unsigned int argument to binary
 * @arg_list: List of arguments
 * @flags: Flag modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: A buffer_t struct containing an array of char
 *
 * Return: Number of byte stored to the buffer
 */

unsigned int _convert_binary(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length)
{
	unsigned int x;

	x = va_arg(arg_list, unsigned int);

	(void)length;

	return (convert_unsigned_base(output, x, "01", flags, width, precision));
}

/**
 * _convert_octal - Converts an unsigned int to octal
 * @arg_list: List of arguments
 * @flags: Flag modifier
 * @width: Width modifier
 * @precision: Precision modifier
 * @length: Length modifier
 * @output: buffer_t struct containing an array of char
 *
 * Return: Number pf bytes stores to the buffer
 */

unsigned int _convert_octal(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length)
{
	unsigned int rem;
	unsigned long int num;
	char zero = '0';

	rem = 0;

	if (length == LONG)
	{
		num = va_arg(arg_list, unsigned long int);
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
		rem += _memory_copy(output, &zero, 1);
	}

	if (!(num == 0 && precision == 0))
	{
		rem += convert_unsigned_base(output, num, "01234567",
				flags, width, precision);

		}
	rem += _print_negative_width(output, rem, flags, width);

	return (rem);
}
