#include "main.h"

unsigned char find_length(const char *modifier, char *index);
unsigned char find_flags(const char *flag, char *index);
int find_precision(va_list arg_list, const char *modifier, char *index);
int find_width(va_list arg_list, const char *modifier, char *index);
unsigned int (*find_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/**
 * find_length - Assigns length modifiers to thier corresponding
 * values
 * @modifier: Pointer to a potential length modifier
 * @index: Index counter for the original format string
 *
 * Return: If matched, the corresponding value.
 * Otherwise 0.
 */

unsigned char find_length(const char *modifier, char *index)
{
	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * find_flags - Assigns flags to corresponding value
 * @flag: Pointer to a potential string of flags
 * @index: Index counter for the original format string
 *
 * Return: If matched, corresponding value.
 * Otherwise 0.
 */

unsigned char find_flags(const char *flag, char *index)
{
	int ind, k;
	unsigned int rem = 0;
	flag_f flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', MINUS},
		{0, 0}
	};

	for (ind = 0; flag[ind]; ind++)
	{
		for (k = 0; flags[k].flag != 0; k++)
		{
			if (flag[ind] == flags[k].flag)
			{
				(*index)++;
				if (rem == 0)
					rem = flags[k].val;
				else
					rem |= flags[k].val;
				break;
			}
		}
		if (flags[k].val == 0)
			break;
	}

	return (rem);
}

/**
 * find_precision - Assigns a precision modifier to its corresponding
 * value
 * @arg_list: List of arguments
 * @modifier: Pointer to a potential precision modifier
 * @index: Index counter for the original format string
 *
 * Return: If matched, its value. If empty, 0 or -0.
 * otherwise 1.
 */

int find_precision(va_list arg_list, const char *modifier, char *index)
{
	int value;

	value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
			*modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
			(*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(arg_list, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * find_width - Assigns a width modifier to its corresponding
 * value
 * @arg_list: List of arguments
 * @modifier: Pointer to a potential with modifier
 * @index: Index counter for the original format string
 *
 * Return: If matched, its value.
 * Otherwise 0.
 */

int find_width(va_list arg_list, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') ||
			(*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(arg_list, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * find_specifiers - Assigns a conversion specifier to its
 * corresponding conversion function
 * @specifier: Pointer to a potential conversion specifier
 *
 * Return: If matched, a pointer to the function.
 * Otherwise NULL.
 */

unsigned int (*find_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char)
{
	int indx;
	converter_s converters[] = {
		{'c', _convert_unsigned_c},
		{'d', _convert_signed_int},
		{'i', _convert_signed_int},
		{'s', convert_lower_string},
		{'%', _convert_percent},
		{'o', _convert_octal},
		{'u', _convert_decimal},
		{'b', _convert_binary},
		{'x', convert_lower_hex},
		{'X', convert_upper_hex},
		{'S', convert_upper_string},
		{'r', convert_reverse_string},
		{'p', _convert_addr_hex},
		{'R', convert_rot13_string},
		{0, NULL}
	};

	for (indx = 0; converters[indx].function; indx++)
	{
		if (converters[indx].specifier == *specifier)
			return (converters[indx].function);
	}

	return (NULL);
}
