/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2022/11/24 20:48:32 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H
#include "libft.h"
#include <fcntl.h>
# include <math.h>
# define AMBIENT_LIGTH 0
# define CAMERA 1
# define LIGHT 2
# define CYLINDER 3
# define PLANE 4
# define SPHERE 5
# define N_TYPES 6
# define SCREEN_WIDHT
# define SCREEN_HEIGHT
# define N_DATA_A 3
# define N_DATA_CA 4
# define N_DATA_L 3
# define N_DATA_SP 4
# define N_DATA_P 4
# define N_DATA_CY 6

bool file_format(char *file_name);

/*		UTILS */
double ft_mod_atof(const char *str, bool *out_of_range);
bool	str_is_float(const char * str);
bool	str_is_int(const char *str);
char** read_file(unsigned short int fd);
void	ft_modlstclear(t_list *lst);

/*		STRUCTS */
typedef struct s_llist
{
	void		*content;
	short int	type;
}t_llist;
/// ligth list
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

typedef struct s_camera
{
	t_coord	*center;
	t_coord	*orientation;
	float	fov;
}t_camera;

typedef struct s_light
{
	t_coord	*point;
	float	ratio;
}t_light;

typedef struct s_ambient
{
	short int *rgb;
	float	ratio;
}t_ambient;

typedef struct s_sphere
{
	t_coord	*center;
	float	diameter;
	float	radius;
	short int *rgb;
}t_sphere;

typedef struct s_plane
{
	t_coord	*point;
	t_coord	*normal;
	short int *rgb;
}t_plane;

typedef struct s_cylinder
{
	t_coord	*center;
	t_coord	*vector; //// ni idea de que punto en el plano se refiere
	float	diameter;
	float	radius;
	float	height;
	short int *rgb;
}t_cylinder;

typedef struct s_program
{
	t_camera	*camera;
	t_light		*light;
	t_ambient	*ambient;
	t_list		*geometries;
	t_llist		*shapes;
	size_t		n_geometries;
	char		**attr_buf;
	int			screen_width;
	int			screen_height;
}t_program;

//CLEANERS
void cylinder_cleaner(t_cylinder *cylinder);
void sphere_cleaner(t_sphere *sphere);
void plane_cleaner(t_plane *plane);
void	ft_modlstclear(t_list *lst);

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
float   distance_screen(t_camera *camara, int width);
t_coord center_point_screen(t_camera *camara, int width);
#endif
