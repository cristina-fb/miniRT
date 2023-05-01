/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:22:40 by jalvarad          #+#    #+#             */
/*   Updated: 2023/05/01 12:50:52 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_ERRORS_H
# define MINIRT_ERRORS_H
# define ERR_A "Wrong number of arguments"
# define ERR_B "Wrong file name format"
# define ERR_C "Can't open this file, check access permissions."
# define ERR_D "Empty File"

// common
# define RGB_MSG "[R,G,B colors in range -> [0-255]]"
# define ORIENTATION "3d normalized orientation vector."
# define OR_RG "In range [-1,1] for each x,y,z axis"

// Ambient
# define AMB_IDX "[identifier -> A]"
# define AMB_RATIO "[ambient lighting ratio in range -> [0.0,1.0]]"

//Camera
# define CM_IDX "[identifier -> C]"
# define CM_VP "x,y,z coordinates of the view point"
# define FOV "FOV : Horizontal field of view in degrees in range [0,180]"

// Light
# define L_IDX "[identifier -> L]"
# define L_LP "x,y,z coordinates of the light point"
# define L_BRIGHT "the light brightness ratio in range [0.0,1.0]"

// Sphere
# define SP_IDX "[identifier -> sp]"
# define SP_CENTER "x,y,z coordinates of the sphere center"
# define SP_DIAMETER "the sphere diameter"

// Plane
# define PL_IDX "[identifier -> pl]"

// Cylinder
# define CY_IDX "[identifier -> cy]"
# define CY_COORDS "x,y,z coordinates"
# define CY_DIAMETER "the cylinder diameter"
# define CY_HEIGHT "the cylinder height"
#endif
