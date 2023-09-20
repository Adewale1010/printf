#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int length;
} buffer_t;

int _printf(const char *format, ...);

#endif
