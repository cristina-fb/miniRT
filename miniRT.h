/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2022/09/21 17:21:13 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "libft.h"
# include <stdio.h>

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
}t_program;

#endif