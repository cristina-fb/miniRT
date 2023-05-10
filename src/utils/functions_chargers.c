/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_chargers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:08:32 by jalvarad          #+#    #+#             */
/*   Updated: 2023/05/05 18:30:43 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parsers_charge(t_action function[N_TYPES])
{
	function[AMBIENT_LIGTH] = parse_ambient_ligth;
	function[CAMERA] = parse_camera;
	function[LIGHT] = parse_light;
	function[CYLINDER] = parse_cylinder;
	function[PLANE] = parse_plane;
	function[SPHERE] = parse_sphere;
	function[TORUS] = parse_torus;
}

void	cleaners_charge(t_cleaner cleaners[N_TYPES - 3])
{
	cleaners[CYLINDER - 3] = cylinder_cleaner;
	cleaners[PLANE - 3] = plane_cleaner;
	cleaners[SPHERE - 3] = sphere_cleaner;
	cleaners[TORUS - 3] = torus_cleaner;
}
