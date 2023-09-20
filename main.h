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
} converter_t;

/**
 * struct flag_s - A new type defining a flag struct
 * @flag: A char representing a flag
 * @val: The integer value of the flag
 */

typedef struct flag_s
{
	unsigned char flag;
	unsigned char val;
} flag_t;

int _printf(const char *format, ...);


#endif
