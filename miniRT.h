/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2022/09/20 17:27:53 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "libft.h"
# include <stdio.h>

typedef struct s_camara
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	float	fov;
}t_camara;

typedef struct s_light
{
	float	x;
	float	y;
	float	z;
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
	float	x;
	float	y;
	float	z;
	float	diameter;
	int		r;
	int		g;
	int		b;
}t_sphere;

typedef struct s_plane
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	int		r;
	int		g;
	int		b;
}t_plane;

typedef struct s_cylinder
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	float	diameter;
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
}t_program;

#endif