/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/05/02 17:16:06 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord rotate_euler(t_coord p, t_coord euler_angles)
{
    double cos_x = cos(euler_angles.x);
    double sin_x = sin(euler_angles.x);
    double cos_y = cos(euler_angles.y);
    double sin_y = sin(euler_angles.y);
    double cos_z = cos(euler_angles.z);
    double sin_z = sin(euler_angles.z);

    t_coord q;

    // Rotación en torno al eje X
    q.y = p.y * cos_x - p.z * sin_x;
    q.z = p.y * sin_x + p.z * cos_x;

    // Rotación en torno al eje Y
    q.x = p.x * cos_y + q.z * sin_y;
    q.z = -p.x * sin_y + q.z * cos_y;

    // Rotación en torno al eje Z
    p.x = q.x * cos_z - q.y * sin_z;
    p.y = q.x * sin_z + q.y * cos_z;
    p.z = q.z;

    return p;
}

double sdTorus(t_coord p, t_torus *torus)
{
    // Traslada el punto al espacio del objeto (centrado en el origen)
    p = v_sub(p, *torus->center);

    // Aplica la rotación de orientación
    p = rotate_euler(p, *torus->orientation);

    double q_x;
    double q_y;
    double q_length;
    q_x = sqrt((p.x * p.x) + (p.z * p.z)) - torus->t_x;
    q_y = p.y;
    q_length = sqrt((q_x * q_x) + (p.y * q_y));
    return (q_length - torus->t_y);
}

/*double sdTorus( t_coord p, t_torus *torus)
{
	double q_x;
	double q_y;
	double q_length;
	q_x = sqrt( (p.x*p.x) + (p.z*p.z)) - torus->t_x;
	q_y = p.y;
	q_length = sqrt( (q_x*q_x) + (p.y*q_y));
  return (q_length - torus->t_y);
}*/
double	distance_sphere(t_coord p, t_sphere *sphere)
{
	double	dist;

	dist = pow(p.x - sphere->center->x, 2.0);
	dist += pow(p.y - sphere->center->y, 2.0);
	dist += pow(p.z - sphere->center->z, 2.0);
	return (sqrt(dist) - sphere->radius);
}

double	distance_plane(t_coord p, t_plane *plane)
{
	double	dist;

	dist = (plane->point->x - p.x) * plane->normal->x;
	dist += (plane->point->y - p.y) * plane->normal->y;
	dist += (plane->point->z - p.z) * plane->normal->z;
	return (fabs(dist));
}

double	distance_cylinder(t_coord p, t_cylinder *cy)
{
	t_coord	pa;
	double	paba;
	double	x;
	double	y;

	pa.x = p.x - cy->base->x;
	pa.y = p.y - cy->base->y;
	pa.z = p.z - cy->base->z;
	paba = (pa.x * cy->ba->x) + (pa.y * cy->ba->y) + (pa.z * cy->ba->z);
	x = sqrt((pow((pa.x * cy->baba) - (cy->ba->x * paba), 2.0) + \
	pow((pa.y * cy->baba) - (cy->ba->y * paba), 2.0) + pow((pa.z * cy->baba) - \
	(cy->ba->z * paba), 2.0))) - cy->radius * cy->baba;
	y = fabs(paba - (cy->baba * 0.5)) - (cy->baba * 0.5);
	if ((x < 0.0) && (y < 0.0))
	{
		if ((x * x) > (y * y * cy->baba))
			return (-1 * sqrt(fabs(-y * y * cy->baba)) / cy->baba);
		else
			return (-1 * sqrt(fabs(-x * x)) / cy->baba);
	}
	if ((x > 0.0) && (y > 0.0))
		return (sqrt(fabs(x * x + y * y * cy->baba)) / cy->baba);
	if (x > 0.0)
		return (sqrt(fabs(x * x)) / cy->baba);
	return (sqrt(fabs(y * y * cy->baba)) / cy->baba);
}
