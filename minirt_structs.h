/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:57:13 by jalvarad          #+#    #+#             */
/*   Updated: 2023/03/08 18:09:17 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCTS_H
# define MINIRT_STRUCTS_H
# include "libft.h"

/// light list
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

/* STRUCT TO SAVE ON ARRAY */
typedef struct s_llist
{
	void		*content;
	short int	type;
}t_llist;

typedef struct s_viewpane
{
	t_coord	*init;
	t_coord	*up;
	t_coord	*right;
	t_pixel	**arr;
	double pixel_width;
	double pixel_height;
	double	width;
	double	height;
}t_viewpane;

typedef struct s_camera
{
	t_coord		*center;
	t_coord		*dir;
	t_viewpane	*vp;
	double		fov;
}t_camera;

typedef struct s_light
{
	t_coord		*point;
	short int	*rgb;
	double		ratio;
}t_light;

typedef struct s_ambient
{
	short int	*rgb;
	double		ratio;
}t_ambient;

typedef struct s_sphere
{
	t_coord		*center;
	double		diameter;
	double		radius;
	short int	*rgb;
}t_sphere;

typedef struct s_plane
{
	t_coord		*point;
	t_coord		*normal;
	short int	*rgb;
}t_plane;

typedef struct s_cylinder
{
	t_coord		*vector;
	t_coord		*ba;
	t_coord		*bb;
	t_coord		*ba_aux;
	double		diameter;
	double		radius;
	double		height;
	double	baba;
	short int	*rgb;
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
	int			s_width;//screen_width
	int			s_height;//screen_height
}t_program;

#endif
