#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/** Flag Modifier Macros **/
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define MINUS 16
#define F_PLUS (flags & 1)
#define F_SPACE ((flags >> 1) & 1)
#define F_HASH ((flags >> 2) & 1)
#define F_ZERO ((flags >> 3) & 1)
#define F_MINUS ((flags >> 4) & 1)

/** Length Modifier Macros **/
#define SHORT 1
#define LONG 2

/**
 * struct buffer_s - A new type defining a buffer struct
 * @buffer: A pointer to an array of char
 * @start: A pointer to the start of buffer
 * @length: Length of the string stored in buffer
 */

typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int length;
} buffer_t;

/**
 * struct converter_x - A new type defining a converter struct
 * @specifier: A char representing a conversion specifier
 * @function: A pointer to a conversion funtion corresponding
 * to specifier
 */

typedef struct converter_x
{
	unsigned char specifier;
	unsigned int (*function)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);
} converter_s;

/**
 * struct flag_s - A new type defining a flag struct
 * @flag: A char representing a flag
 * @val: The integer value of the flag
 */

typedef struct flag_s
{
	unsigned char flag;
	unsigned char val;
} flag_f;

int _printf(const char *format, ...);

/** Conversion specifier function prototyes **/
unsigned int _convert_unsigned_c(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char len);
unsigned int _convert_signed_int(va_list arg_list, butter_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length);
unsigned int convert_lower_string(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length);
unsigned int _convert_percent(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length);
unsigned int _convert_octal(va_list arg_list, butter_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length);
unsigned int _convert_decimal(va_list arg_list, butter_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length);
unsigned int _convert_binary(va_list arg_list, butter_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length);
unsigned int convert_lower_hex(va_list arg_list,
		buffer_t *output, unsigned char flags,
		int width, int precision, unsigned char length);
unsigned int convert_upper_hex(va_list arg_list,
		buffer_t *output, unsigned char flags,
		int width, int precision, unsigned char length);
unsigned int convert_reverse_string(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length);
unsigned int _convert_addr_hex(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision,
		unsigned char length);
unsigned int convert_rot13_string(va_list arg_list, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char length);

/** Finders prototypes**/
unsigned char find_length(const char *modifier, char *index);
unsigned char find_flags(const char *flag, char *index);
int find_precision(va_list arg_list, const char *modifier, char *index);
int find_width(va_list arg_list, const char *modifier, char *index);
unsigned int (*find_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/** Modifier function prototypes **/
unsigned int _print_string_width(buffer_t *output, unsigned char flags,
		int width, int precision, int size);
unsigned int _print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int width);
unsigned int _print_negative_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int width);

/** Memory and base helper function prototypes **/
unsigned int _free_buffer(buffer_t *output);
unsigned int _memory_copy(buffer_t *output, const char *src, unsigned int m);
buffer_t *initialize_buffer(void);
unsigned int convert_signed_base(buffer_t *output, long int num, char *base,
		unsigned char flags, int width, int precision);
unisigned int convert_unsigned_base(buffer_t *output,
		unsigned long int num, char *base,
		unsigned char flags, int width, int precision);

#endif
