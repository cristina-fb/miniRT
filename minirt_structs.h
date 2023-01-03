/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:57:13 by jalvarad          #+#    #+#             */
/*   Updated: 2023/01/03 21:18:40 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCTS_H
#define MINIRT_STRUCTS_H
#include "libft.h"

/* STRUCT TO SAVE ON ARRAY */
typedef struct s_llist
{
	void		*content;
	short int	type;
}t_llist;
/// ligth list
typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
}t_coord;

typedef struct s_pixel
{
	t_coord	*ray;
	int		color;
}t_pixel;

typedef struct s_camera
{
	t_coord	*center;
	t_coord	*orientation;
	t_coord *vp_init;
	t_coord *vp_up;
	t_coord *vp_right;
	double	fov;
	int		vp_widht;
	int		vp_height;
}t_camera;
/*
vp_init npi
vp_up
ancho cristal camara -> vp_width y vp_height
cambiar float a double
*/
typedef struct s_light
{
	t_coord	*point;
	short int *rgb;
	double	ratio;
}t_light;

typedef struct s_ambient
{
	short int *rgb;
	double	ratio;
}t_ambient;

typedef struct s_sphere
{
	t_coord	*center;
	double	diameter;
	double	radius;
	short int *rgb;
}t_sphere;
/* inicializar radio*/
typedef struct s_plane
{
	t_coord	*point;
	t_coord	*normal;
	short int *rgb;
}t_plane;

typedef struct s_cylinder
{
	t_coord	*center;
	t_coord	*vector;
	t_coord *ba;
	t_coord *bb;
	double	diameter;
	double	radius;
	double	height;
	short int *rgb;
}t_cylinder;
/* ba -> base abajo   TODO -> cambiar nombres
	bb ->base arriba
*/

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

#endif