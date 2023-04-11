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
void cylinder_aabb(t_cylinder *cylinder, t_coord *min, t_coord *max)
{
    t_coord a = *(cylinder->ba);
    t_coord b = *(cylinder->bb);
    double r = cylinder->radius;

    // Encontrar los límites del cilindro en cada dimensión
    min->x = fmin(a.x, b.x) - r;
    min->y = fmin(a.y, b.y) - r;
    min->z = fmin(a.z, b.z) - r;
    max->x = fmax(a.x, b.x) + r;
    max->y = fmax(a.y, b.y) + r;
    max->z = fmax(a.z, b.z) + r;
}

void sphere_aabb(t_sphere *sphere, t_coord *min, t_coord *max) {
    t_coord c = *(sphere->center);
    double r = sphere->radius;

    // Encontrar los límites de la esfera en cada dimensión
    min->x = c.x - r;
    min->y = c.y - r;
    min->z = c.z - r;
    max->x = c.x + r;
    max->y = c.y + r;
    max->z = c.z + r;
}

void object_aabb(t_llist *obj, t_coord *min, t_coord *max)
{
    if (obj->type == 3)
    {   
        t_cylinder *cylinder = (t_cylinder *)obj->content;
        cylinder_aabb(cylinder, min, max);
    }
    
    else if (obj->type == 4)
    {
        min->x = min->y = min->z = -INFINITY;
        max->x = max->y = max->z = INFINITY;
    }
    else
    {
        t_sphere *sphere = (t_sphere *)obj->content;
        sphere_aabb(sphere, min, max);
    }
}
int compare_x(const void *a, const void *b) {
    t_llist *obj_a = (t_llist *)a;
    t_llist *obj_b = (t_llist *)b;
    t_coord min_a, max_a, min_b, max_b;
    object_aabb(obj_a, &min_a, &max_a);
    object_aabb(obj_b, &min_b, &max_b);
    return (min_a.x < min_b.x) ? -1 : 1;
}

int compare_y(const void *a, const void *b) {
    t_llist *obj_a = (t_llist *)a;
    t_llist *obj_b = (t_llist *)b;
    t_coord min_a, max_a, min_b, max_b;
    object_aabb(obj_a, &min_a, &max_a);
    object_aabb(obj_b, &min_b, &max_b);
    return (min_a.y < min_b.y) ? -1 : 1;
}

int compare_z(const void *a, const void *b) {
    t_llist *obj_a = (t_llist *)a;
    t_llist *obj_b = (t_llist *)b;
    t_coord min_a, max_a, min_b, max_b;
    object_aabb(obj_a, &min_a, &max_a);
    printf("paso %d\n", obj_b->type);
    object_aabb(obj_b, &min_b, &max_b);
    return (min_a.z < min_b.z) ? -1 : 1;
}

int (*axis_compare[])(const void *, const void *) = {compare_x, compare_y, compare_z};

int longest_axis(const t_coord *min, const t_coord *max) {
    // Calcular las longitudes de los lados del AABB a lo largo de cada eje
    double dx = max->x - min->x;
    double dy = max->y - min->y;
    double dz = max->z - min->z;

    // Encuentra el eje más largo y devuelve su índice
    if (dx >= dy && dx >= dz) {
        return 0; // Eje x
    } else if (dy >= dx && dy >= dz) {
        return 1; // Eje y
    } else {
        return 2; // Eje z
    }
}
void merge_aabb(const t_coord *min_a, const t_coord *max_a, const t_coord *min_b, const t_coord *max_b, t_coord *min_out, t_coord *max_out)
{
    // Encuentra los límites mínimos y máximos combinados de los dos AABB
    min_out->x = fmin(min_a->x, min_b->x);
    min_out->y = fmin(min_a->y, min_b->y);
    min_out->z = fmin(min_a->z, min_b->z);

    max_out->x = fmax(max_a->x, max_b->x);
    max_out->y = fmax(max_a->y, max_b->y);
    max_out->z = fmax(max_a->z, max_b->z);
}

t_bvh_node *build_bvh(t_llist *objects, size_t start, size_t end)
{
    t_bvh_node *node = malloc(sizeof(t_bvh_node));
    node->left = NULL;
    node->right = NULL;
    node->geometry = NULL;

    size_t object_span = end - start;
    if (object_span == 1) {
        node->geometry = &objects[start];
        object_aabb(&objects[start], &node->min, &node->max);
        return node;
    }

    // Calculate the total bounding box for all objects in this span
    t_coord total_min, total_max;
    object_aabb(&objects[start], &total_min, &total_max);
    for (size_t i = start + 1; i < end; i++) {
        t_coord temp_min, temp_max;
        object_aabb(&objects[i], &temp_min, &temp_max);
        merge_aabb(&total_min, &total_max, &temp_min, &temp_max, &total_min, &total_max);
    }

    // Determine the best axis to split the objects
    int split_axis = longest_axis(&total_min, &total_max);
    if (object_span == 2)
    {
        node->left = build_bvh(objects, start, start + 1);
        node->right = build_bvh(objects, start + 1, end);
    }
    else
    {
        // Sort the objects based on the split axis
        printf("sort\n");
        qsort(objects + start, object_span, sizeof(t_llist), axis_compare[split_axis]);

        // Recursively build the BVH tree for the left and right children
        size_t mid = start + object_span / 2;
        node->left = build_bvh(objects, start, mid);
        node->right = build_bvh(objects, mid, end);
    }

    node->min = total_min;
    node->max = total_max;
    return node;
}

bool aabb_contains_point(t_coord *min, t_coord *max, t_coord point)
{
    return point.x >= min->x && point.x <= max->x &&
           point.y >= min->y && point.y <= max->y &&
           point.z >= min->z && point.z <= max->z;
}

double distance_to_geometry(t_coord p, t_llist *geometry)
{
    if (geometry->type == SPHERE)
        return distance_sphere(p, (t_sphere *)geometry->content);
    else if (geometry->type == PLANE)
        return distance_plane(p, (t_plane *)geometry->content);
    else if (geometry->type == CYLINDER)
        return distance_cylinder(p, (t_cylinder *)geometry->content);
    return 0;
}

t_llist *distance_to_bvh(t_coord point, t_bvh_node *node, double *min_distance)
{
    t_llist *closest_geometry = NULL;

    if (!node || !aabb_contains_point(&node->min, &node->max, point))
    {
        *min_distance = INFINITY;
        return NULL;
    }

    if (node->geometry)
    {
        *min_distance = distance_to_geometry(point, node->geometry);
        return node->geometry;
    }

    double left_distance, right_distance;
    t_llist *left_geometry = distance_to_bvh(point, node->left, &left_distance);
    t_llist *right_geometry = distance_to_bvh(point, node->right, &right_distance);

    if (left_distance < right_distance)
    {
        *min_distance = left_distance;
        closest_geometry = left_geometry;
    }
    else
    {
        *min_distance = right_distance;
        closest_geometry = right_geometry;
    }
    return closest_geometry;
}
