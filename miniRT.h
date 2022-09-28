#ifndef MINIRT_H
#define MINIRT_H
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
bool file_format(char *file_name);

/*		UTILS */
double ft_mod_atof(const char *str, bool *out_of_range);
bool	str_is_float(const char * str);
bool	str_is_int(const char *str);
char** read_file(unsigned short int fd);
#endif