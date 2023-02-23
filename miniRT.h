/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/02/23 14:06:28 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "minirt_errors.h"
# include "minirt_structs.h"
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
/* ---------------------- MACROS --------------------------*/
/*                    Index for save                       */
# define AMBIENT_LIGTH 0
# define CAMERA 1
# define LIGHT 2
# define CYLINDER 3
# define PLANE 4
# define SPHERE 5
# define N_TYPES 6

/*                     Resolution                         */
# define WIDTH 1080
# define HEIGHT 720

/*               Number of data for element                */
# define N_DATA_A 3
# define N_DATA_CA 4
# define N_DATA_L 4
# define N_DATA_SP 4
# define N_DATA_P 4
# define N_DATA_CY 6

# define MAX_STEPS 1000
# define MAX_DIST 10000.
# define MIN_DIST 0.001

/* ------------------- FUNCTIONS -------------------------- */
/*                      READER                              */
char		**open_read(char *file_name, char **err_message);
/*                       RGB                                */
short int	*get_rgb(char *attr_buf, bool *err);
short int	*object_rgb(t_llist *obj);
int         get_int_color(short int *rgb);

/*                  GEOMETRIES PARSER                       */
bool		parse_sphere(t_program *program);
bool		parse_plane(t_program *program);
bool		parse_cylinder(t_program *program);

/*                 SCENE ELEMENTS PARSER					*/
bool		parse_ambient_ligth(t_program *program);
bool		parse_camera(t_program *program);
bool		parse_light(t_program *program);

t_coord		*orientation_vector(char *str_cords);
t_coord		*get_coords(char *str_coords);

/*		                 PARSER UTILS                       */
bool		filename_format(char *file_name);
void		print_error(char *message);
double		ft_mod_atof(const char *str, bool *out_of_range);
bool		str_is_float(const char *str);
bool		str_is_int(const char *str);
bool		are_basic_attr(t_program program);
t_program	get_attributes(char **all_file, bool *error);
bool		is_not_fov(float fov);
bool		not_in_ambient_ratio(float ratio);

t_llist		*lst_to_array(t_list *lst, size_t size);
void		print_program_data(t_program program);

/*                      CLEANERS                            */
void		free_program_data(t_program *program, bool clean_content);
void		ft_modlstclear(t_list *lst, bool clean_content);
void		array_geometries_clear(t_llist *shapes, size_t len);

void		cylinder_cleaner(t_cylinder *cylinder);
void		sphere_cleaner(t_sphere *sphere);
void		plane_cleaner(t_plane *plane);

void		light_cleaner(t_light *light);
void		camera_cleaner(t_camera *camera);
void		ambient_light_cleaner(t_ambient *ambient);
void		viewpane_cleaner(t_viewpane *viewpane);

/*                       DISTANCE					        */
double		distance_sphere(t_coord point, t_sphere *sphere);
double		distance_plane(t_coord point, t_plane *plane);
t_llist		*min_distance(t_coord p, t_program *program, double *min);

/*                   VECTOR OPERATIONS					    */
t_coord		v_add(t_coord a, t_coord b);
t_coord		v_sub(t_coord a, t_coord b);
t_coord		v_mul(t_coord a, float b);
t_coord		v_div(t_coord a, float b);

/*                  VECTOR OPERATIONS 1	       			    */
float		v_module(t_coord a);
float		dot_product(t_coord a, t_coord b);
t_coord		cross_product(t_coord a, t_coord b);
t_coord		v_unit(t_coord v);

/*                        SCREEN					        */
bool		init_vp(t_camera *cam);
bool		pixels_array(t_camera *cam);
int			horizontal_resolution(void);
float		distance_screen(t_camera *camara, int width); //NO EXISTE (?)
t_coord		center_point_screen(t_camera *camara, int width); //NO EXISTE (?)

/*                        SHADING					        */
double      pcolor(t_program *p, t_llist *obj, t_coord *point, t_coord *ray);
t_coord	    get_normal(t_llist *obj, t_coord *point);
#endif
