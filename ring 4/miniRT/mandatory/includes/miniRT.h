/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:11:13 by cprot             #+#    #+#             */
/*   Updated: 2025/11/24 14:35:38 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
# define QUALITY 20
# define M_PI 3.14159265358979323846

// ------------------------------------------------------
// STRUCTURES PRINCIPALES
// ------------------------------------------------------

typedef struct s_vec3
{
	double				x;
	double				y;
	double				z;
}						t_vec3;

typedef struct s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef struct s_ambient
{
	double				ratio;
	t_color				color;
}						t_ambient;

typedef struct s_camera
{
	t_vec3				position;
	t_vec3				orientation;
	int					fov;
	int					samples_per_pixel;
}						t_camera;

typedef struct s_light
{
	t_vec3				position;
	double				brightness;
	t_color				color;
}						t_light;

typedef struct s_sphere
{
	t_vec3				center;
	double				diameter;
	t_color				color;
	struct s_sphere		*next;
}						t_sphere;

typedef struct s_plane
{
	t_vec3				point;
	t_vec3				normal;
	t_color				color;
	struct s_plane		*next;
}						t_plane;

typedef struct s_cylinder
{
	t_vec3				center;
	t_vec3				axis;
	double				diameter;
	double				height;
	t_color				color;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct s_environment
{
	struct s_ambient	*ambient;
	struct s_camera		*camera;
	struct s_light		*light;
}						t_environment;

typedef struct s_object
{
	struct s_sphere		*spheres;
	struct s_plane		*planes;
	struct s_cylinder	*cylinders;
}						t_object;

// ------------------------------------------------------
// STRUCTURES EXEC
// ------------------------------------------------------

typedef enum e_object_type
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}						t_object_type;

typedef struct s_minirt
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					sample_index;
	t_environment		*env;
	t_object			*obj;
}						t_minirt;

typedef struct s_ray
{
	t_vec3				origin;
	t_vec3				direction;
}						t_ray;

typedef struct s_camera_basis
{
	t_vec3				forward;
	t_vec3				right;
	t_vec3				up;
	double				viewport_width;
	double				viewport_height;
}						t_camera_basis;

typedef struct s_hit_record
{
	t_vec3				point;
	t_vec3				normal;
	double				t;
	int					front_face;
	t_object_type		type;
	void				*object;
}						t_hit_record;

typedef struct s_cylinder_calc
{
	t_vec3				oc_perp;
	t_vec3				dir_perp;
	double				a;
	double				b;
	double				c;
}						t_cylinder_calc;

// ------------------------------------------------------
// FONCTIONS PARSING
// ------------------------------------------------------

void					parsing_master(char *filename, t_environment **env,
							t_object **obj);
void					environment_parsing(char **line, t_environment **env,
							t_object **obj);
void					objects_parsing(char **line, t_environment **env,
							t_object **obj);

void					parse_ambient(char **line, t_environment **env);
void					parse_camera(char **line, t_environment **env,
							t_object **obj);
void					parse_light(char **line, t_environment **env);
void					parse_sphere(char **line, t_environment **env,
							t_object **obj);
void					parse_plane(char **line, t_environment **env,
							t_object **obj);
void					parse_cylinder(char **line, t_environment **env,
							t_object **obj);

double					parse_double(char *str, double min, double max,
							t_environment **env);
t_color					parse_color(char *str, t_environment **env);
t_vec3					parse_vector(char *str, t_environment **env);
t_vec3					parse_vector_range(char *str, double min, double max,
							t_environment **env);

bool					is_valid_number(const char *str);
bool					is_valid_float(const char *str);
bool					verify_rgb(char **split_rgb);
bool					verify_coordinates(char **split_coord);
bool					verify_ambient(const char **line);
bool					verify_light(const char **line);
bool					verify_camera_(const char **line);
bool					verify_plane(const char **line);
bool					verify_cylinder(const char **line);
bool					verify_sphere(const char **line);

// ------------------------------------------------------
// FONCTIONS UTILITAIRES / RENDU
// ------------------------------------------------------

// void	process_rendering(t_environment *env, t_object *obj);
void					free_environment(t_environment *env);
void					free_objects(t_object *obj);
void					free_tab(char **tab);
void					exit_with_error(const char *message,
							t_environment **env, t_object **obj);

// ------------------------------------------------------
// FONCTIONS EXEC
// ------------------------------------------------------

void					init_minirt(t_environment *env, t_object *obj);
void					apply_hooks(t_minirt *rt);
int						close_window(t_minirt *rt);
void					my_mlx_pixel_put(t_minirt *rt, int x, int y, int color);
void					render_pixels(t_minirt *rt, t_camera_basis *basis);

// setup
void					setup_camera(t_minirt *rt, t_camera_basis *cam);
t_ray					create_ray(t_vec3 origin, t_vec3 direction);
t_ray					generate_ray(t_minirt *rt, t_camera_basis *cam, int x,
							int y);

// obj
int						intersect_sphere(t_ray ray, t_sphere *sphere,
							double *t);
int						intersect_plane(t_ray ray, t_plane *plane, double *t);
int						intersect_cylinder_body(t_ray ray, t_cylinder *cyl,
							double *t);
int						intersect_cylinder_cap(t_ray ray, t_cylinder *cyl,
							double *t, int is_top);
int						hit_plane(t_ray ray, t_plane *plane, t_hit_record *rec);
int						hit_sphere(t_ray ray, t_sphere *sphere,
							t_hit_record *rec);
int						hit_cylinder(t_ray ray, t_cylinder *cylinder,
							t_hit_record *rec);
int						hit_world(t_ray ray, t_object *obj, t_hit_record *rec);

// colors
t_vec3					ray_color(t_ray ray, t_object *obj, t_environment *env);
int						vec3_to_int(t_vec3 v);
t_vec3					calculate_lighting(t_hit_record *rec,
							t_environment *env, t_object *obj);
t_vec3					get_object_color(t_hit_record *rec);
t_vec3					color_to_vec3(int r, int g, int b);

// Vecteurs
t_vec3					vec_add(t_vec3 a, t_vec3 b);
t_vec3					vec_sub(t_vec3 a, t_vec3 b);
t_vec3					vec_scale(t_vec3 v, double s);
double					vec_dot(t_vec3 a, t_vec3 b);
double					vec_length(t_vec3 v);
t_vec3					vec_normalize(t_vec3 v);
t_vec3					vec_cross(t_vec3 a, t_vec3 b);
t_vec3					vec_mult(t_vec3 a, t_vec3 b);
t_vec3					vec_perp_to_axis(t_vec3 v, t_vec3 axis);

#endif
