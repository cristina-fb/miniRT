/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:57:31 by jalvarad          #+#    #+#             */
/*   Updated: 2023/03/04 17:36:11 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"

t_coord get_center_bounding_box(t_bounding_box bbox)
{
    t_coord center;
    center.x = (bbox.min->x + bbox.max->x) / 2.0;
    center.y = (bbox.min->y + bbox.max->y) / 2.0;
    center.z = (bbox.min->z + bbox.max->z) / 2.0;
    return center;
}

// Función para obtener la caja de límites de una esfera
t_bounding_box get_bounding_box_sphere(t_sphere *sphere)
{
    t_bounding_box bbox;

    bbox.min = (t_coord*)ft_calloc(1, sizeof(t_coord));
    bbox.max = (t_coord*)ft_calloc(1, sizeof(t_coord));
    // El mínimo y el máximo son iguales al centro de la esfera en ambas direcciones
    *(bbox.min) = v_sub(*(sphere->center), (t_coord){sphere->radius, sphere->radius, sphere->radius});
    *(bbox.max) = v_add(*(sphere->center), (t_coord){sphere->radius, sphere->radius, sphere->radius});
    return (bbox);
}

// Función para obtener la caja de límites de un cilindro
t_bounding_box get_bounding_box_cylinder(t_cylinder *cylinder)
{
    t_bounding_box bbox;

    bbox.min = (t_coord*)ft_calloc(1, sizeof(t_coord));
    bbox.max = (t_coord*)ft_calloc(1, sizeof(t_coord));
    // Obtenemos el vector que va desde la base del cilindro hasta la tapa
    t_coord axis = v_sub(*(cylinder->bb), *(cylinder->ba));
    // Calculamos el radio del cilindro en el eje perpendicular al eje del cilindro
    float radius = cylinder->radius * sqrt(pow(axis.x, 2.0) + pow(axis.z, 2.0));
    // Calculamos el vector que apunta hacia abajo desde la tapa del cilindro
    t_coord top = (t_coord){cylinder->bb->x, cylinder->bb->y + cylinder->height, cylinder->bb->z};
    t_coord down = v_sub(top, *(cylinder->bb));
    // Calculamos la altura del cilindro
    float height = v_module(down);
    // Obtenemos un vector perpendicular al eje del cilindro y a down
    t_coord a;
    if (fabs(down.x) < fabs(down.y))
        a = (t_coord){1, 0, 0};
    else
        a = (t_coord){0, 1, 0};
    t_coord b = v_unit(cross_product(down, a));
    // Obtenemos el máximo y el mínimo del cilindro
    *(bbox.min) = v_sub(*(cylinder->ba), v_mul(b, radius));
    bbox.min->y = cylinder->ba->y;
    *(bbox.max) = v_add(*(cylinder->ba), v_mul(b, radius));
    bbox.max->y = cylinder->ba->y + height;
    return (bbox);
}

// Función para obtener la caja de límites de un plano
t_bounding_box get_bounding_box_plane(t_plane *plane)
{
    t_bounding_box bbox;

    bbox.min = (t_coord*)ft_calloc(1, sizeof(t_coord));
    bbox.max = (t_coord*)ft_calloc(1, sizeof(t_coord));
    // El mínimo y el máximo son iguales a la posición del plano en ambas direcciones
    *(bbox.min) = *(plane->point);
    *(bbox.max) = *(plane->point);
    return (bbox);
}