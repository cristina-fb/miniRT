/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2022/09/27 16:26:59 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
<<<<<<< HEAD
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
=======
# define MINIRT_H
# include <stdio.h>
# include <math.h>

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
}t_coord;

typedef struct s_pixel
{
	t_coord	*ray;
	int		color; //Es un int??
}t_pixel;

typedef struct s_camara
{
	t_coord	*center;
	t_coord	*orientation;
	float	fov;
}t_camara;

typedef struct s_light
{
	t_coord	*point;
	float	ratio;
}t_light;

typedef struct s_ambient
{
	float	r;
	float	g;
	float	b;
	float	ratio;
}t_ambient;

typedef struct s_sphere
{
	t_coord	*center;
	float	diameter;
	float	radius;
	int		r;
	int		g;
	int		b;
}t_sphere;

typedef struct s_plane
{
	t_coord	*point;
	t_coord	*normal;
	int		r;
	int		g;
	int		b;
}t_plane;

typedef struct s_cylinder
{
	t_coord	*center;
	t_coord	*vector;
	float	diameter;
	float	radius;
	float	height;
	int		r;
	int		g;
	int		b;
}t_cylinder;

typedef struct s_program
{
	t_camara	*camara;
	t_light		*light;
	t_ambient	*ambient;
	t_sphere	*sphere_lst;
	t_plane		*plane_lst;
	t_cylinder	*cylinder_lst;
	int			screen_width;
	int			screen_height;
}t_program;

//DISTANCE
float	distance_sphere(t_coord *point, t_sphere *sphere);
float	distance_plane(t_coord *point, t_plane *plane);

//VECTOR_OPERATIONS
t_coord	vector_add(t_coord *a, t_coord *b);
t_coord	vector_sub(t_coord *a, t_coord *b);
t_coord	vector_mul(t_coord *a, float b);
t_coord	vector_div(t_coord *a, float b);

//VECTOR_OPERATIONS1
float	vector_module(t_coord *a);
float	dot_product(t_coord *a, t_coord *b);

//SCREEN
float   distance_screen(t_camara *camara, int width);
t_coord center_point_screen(t_camara *camara, int width);
#endif
>>>>>>> master
