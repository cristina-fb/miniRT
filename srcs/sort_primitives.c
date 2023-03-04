/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_primitives.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:55:35 by jalvarad          #+#    #+#             */
/*   Updated: 2023/03/04 18:13:55 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
void sort_primitives(t_llist *primitives, int n_primitives, int axis)
{
    if (n_primitives < 2)
        return;

    // Se calcula el centro de la caja de límites de todas las primitivas
    t_coord center = get_center_bounding_box(*(primitives->bbox));

    // Se divide el array de primitivas en dos sub-arrays, según su posición en el eje de división
    t_llist *left_primitives = primitives;
    t_llist *right_primitives = primitives + n_primitives / 2;

    int left_count = 0;
    int right_count = n_primitives - n_primitives / 2;

    for (int i = 0; i < n_primitives; i++)
    {
        t_coord primitive_center = get_center_bounding_box(*(primitives[i].bbox));

        if (axis == 0)
        {
            if (primitive_center.x < center.x)
            {
                if (i != left_count)
                    swap_primitives(&left_primitives[left_count], &primitives[i]);
                left_count++;
            }
            else
            {
                if (i != left_count + right_count - 1)
                    swap_primitives(&right_primitives[right_count - 1], &primitives[i]);
                right_count--;
            }
        }
        else if (axis == 1)
        {
            if (primitive_center.y < center.y)
            {
                if (i != left_count)
                    swap_primitives(&left_primitives[left_count], &primitives[i]);
                left_count++;
            }
            else
            {
                if (i != left_count + right_count - 1)
                    swap_primitives(&right_primitives[right_count - 1], &primitives[i]);
                right_count--;
            }
        }
        else if (axis == 2)
        {
            if (primitive_center.z < center.z)
            {
                if (i != left_count)
                    swap_primitives(&left_primitives[left_count], &primitives[i]);
                left_count++;
            }
            else
            {
                if (i != left_count + right_count - 1)
                    swap_primitives(&right_primitives[right_count - 1], &primitives[i]);
                right_count--;
            }
        }
    }

    // Se ordenan recursivamente los dos sub-arrays
    sort_primitives(left_primitives, left_count, (axis + 1) % 3);
    sort_primitives(right_primitives, right_count, (axis + 1) % 3);
}
