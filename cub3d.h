/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:51:48 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/10/21 14:53:06 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# define HEIGHT 800
# define WIDTH 1200
# define FOV 70
# define RAY_NBR 1200
# define TURN 2
# define STEP 0.05

# define MINICOLOR 858993663
# define MINIBACK 2155905279
# define LINECOL 94702
# define MOUSE_SENSITIVITY 0.005

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# include "MLX42/include/MLX42/MLX42.h"
# include "MLibft/libft.h"
# include "2DPlane/Plane.h"
# include "2DPlane/Fixed.h"

/** Our player Struct
* @param P The point at which the player is located
* @param angle The angle that the player is facing
* @param view An array of all the angles in the player's FOV
*/
typedef struct s_player
{
	t_point		p;
	t_fixed		angle;
	t_ray		view[RAY_NBR];
}				t_player;

/** A struct for objects to be displayed
 * @param NORTH The texture of the object's north side
 * @param SOUTH The texture of the object's south side
 * @param EAST The texture of the object's east side
 * @param WEST The texture of the object's west side
 * @param FLOOR The texture of the object's bottom side
 * @param CEILING The texture of the object's top side
 */
typedef struct s_object
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	char			*floor;
	char			*ceiling;
	mlx_t			*mlxpointer;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*gun_texture;
	mlx_image_t		*gun_image;
}				t_object;
/** Our Cub3D Struct
 * @param WIN A pointer to the window
 * @param IMG An array of pointers to images
 * @param MAP A pointer to a plane object
 * @param P A pointer to the player
 * @param WALL A pointer to the object representing our walls
 */
typedef struct s_cub
{
	mlx_t		*win;
	mlx_image_t	*img[3];
	t_plane		*map;
	t_player	*p;
	t_object	*wall;
}				t_cub;

/** A useful struct to store information about collisions
 * @param OBJ The object you have collided with
 * @param P The point of collision
 * @param DISTANCE How far away is the object from origin
 * @param DIR A char, indicating from which direction the collision occured
 */
typedef struct crash_s
{
	void		*obj;
	t_point		p;
	t_fixed		distance;
	char		dir;
}				t_crash;

// Map functions
int		obj_init(t_object *obj, t_cub *cub, char *path);
int		extract_grid(t_cub *map, int fd);
int		extract_grid2(t_cub *map, char **str);
int		ft_strcmp(char *s1, char *s2);
int		load_textures(t_object *object);
void	free_chars(char **chars);
void	destroy_obj(t_object obj);
void	draw_mini(t_cub	*cub);
void	draw_walls(t_crash crash, t_cub cub, int i, t_fixed angle);
int		load_gun(t_object *object, t_cub *cub);
void	draw_gun(t_object *object, t_cub *cub);
void	free_gun(t_object obj, t_cub cub);
t_fixed	relative_x(u_int32_t x, t_cub *cub);

// Raycaster
t_crash	cast_ray(t_ray ray);
t_fixed	normalize(t_fixed angle);

// Player Functions
void	init_player(t_cub *cub, int x, int y, char d);
void	key_hook(void *cub);
int		player_access(t_fixed x, t_fixed y, t_plane *plane);
int		frame_function(void);
void	cur_hook(double xpos, double ypos, void *tcub);

void	pcopy(t_point *dst, t_point src);
int		is_spc(int c);
int		line_fill(char *line, t_object *obj);
int		validate_textures(t_object *obj);
int		player_check(char **map);
int		copy_map(char **map, int x, int y);
int		flood_fill2(char **map, int x, int y);
void	minimap(t_cub	*cub);
void	static_map(t_cub	*cub);
void	draw_background(t_cub *cub, uint32_t cei, uint32_t flo);
void	err(char *str);
void	cur_hook(double xpos, double ypos, void *param);

#endif