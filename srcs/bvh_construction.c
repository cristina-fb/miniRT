/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_construction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:21:29 by jalvarad          #+#    #+#             */
/*   Updated: 2023/04/06 18:09:52 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bvh_node *build_bvh(t_llist **objects, size_t start, size_t end) {
    t_bvh_node *node = malloc(sizeof(t_bvh_node));
    node->left = NULL;
    node->right = NULL;
    node->geometry = NULL;

    size_t object_span = end - start;
    if (object_span == 1) {
        node->geometry = objects[start];
        object_aabb(objects[start], &node->min, &node->max);
        return node;
    }

    // Calculate the total bounding box for all objects in this span
    t_coord total_min, total_max;
    object_aabb(objects[start], &total_min, &total_max);
    for (size_t i = start + 1; i < end; i++) {
        t_coord temp_min, temp_max;
        object_aabb(objects[i], &temp_min, &temp_max);
        merge_aabb(&total_min, &total_max, &temp_min, &temp_max);
    }

    // Determine the best axis to split the objects
    int split_axis = longest_axis(&total_min, &total_max);
    if (object_span == 2) {
        node->left = build_bvh(objects, start, start + 1);
        node->right = build_bvh(objects, start + 1, end);
    } else {
        // Sort the objects based on the split axis
        qsort(objects + start, object_span, sizeof(t_llist *), axis_compare[split_axis]);

        // Recursively build the BVH tree for the left and right children
        size_t mid = start + object_span / 2;
        node->left = build_bvh(objects, start, mid);
        node->right = build_bvh(objects, mid, end);
    }

    node->min = total_min;
    node->max = total_max;
    return node;
}

