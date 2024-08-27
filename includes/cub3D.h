/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   cub3D.h	:+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: ppitzini <marvin@42.fr>	+#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2024/07/01 16:24:58 by ppitzini	  #+#	#+#	 */
/*   Updated: 2024/08/26 15:54:37 by ppitzini	 ###   ########.fr	   */
/*	*/
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../MacroLibX/includes/mlx.h"

// COLORS
# define R   "\x1B[31m"
# define G   "\x1B[32m"
# define Y   "\x1B[33m"
# define B_R   "\x1B[1;31m"
# define B_G   "\x1B[1;32m"
# define B_Y   "\x1B[1;33m"
# define BOLD "\x1B[1m"
# define RESET "\x1B[0m"

// ERRORS MESSAGES
# define ERROR_RGB "\n   |Error : Invalid RGB data. \u274c \n"
# define ERROR_DATA "\n   |Error : Invalid data \u274c \n"
# define ERROR_EXTENSION "   |Error : wrong file extension \u274c \n"
# define ERROR_ARGUMENTS "   |Error : Wrong number of arguments \u274c \n"
# define ERROR_EMPTY_MAP "\n   |Error : empty map \u274c \n"
# define ERROR_SYNTAX "\n   |Error : syntax error \u274c \n"
# define ERROR_OPEN_FILE "\n   |Error : Can't open file \u274c \n"
# define ERROR_INVALID_MAP "\n   |Error : Invalid map \u274c \n"
# define ERROR_NOT_CLOSED "\n   |ERROR : Map is not closed at [%d, %d]\n"
# define END_LINE "\n\n -----------------------------------------------\n"
# define ERROR_PLAYER "\n   |Error : No player found \u274c \n"
// MATH
# define FOV 60
# define TILE 15
# define SCREEN_HEIGHT 720
# define SCREEN_LENGHT 1280
# define RAYS 720
# define SPEED 4

// STRUCTURES
typedef struct s_math
{
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;
	int		map_x;
	int		map_y;
}	t_math;

typedef struct s_rotation
{
	double	p_angle;
	int		p_x;
	int		p_x_2d;
	int		p_y;
	int		p_y_2d;
	float	fov_rd;
	double	ray_step;
	int		hor_or_ver;
	float	hor_pos_wall_x;
	float	hor_pos_wall_y;
	float	ver_pos_wall_x;
	float	ver_pos_wall_y;
	float	distance;
	int		pos_player_x;
	int		pos_player_y;
	int		colone;
}	t_rotation;

typedef struct s_map
{
	int		fd;
	int		lenght_line;
	int		height_line;
	int		i;
	char	*map_path;
	char	**map;
	int		n_o;
	int		s_o;
	int		w_e;
	int		e_a;
	int		c_number;
	int		f_number;
	int		player_here;
	int		r;
	int		g;
	int		b;
	int		len_prev_line;
	int		len_this_line;
}				t_map;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*color_f;
	char	*color_c;
	int		rgb_f;
	int		rgb_c;
}				t_texture;

typedef struct map_core
{
	void		*img_n;
	void		*img_e;
	void		*img_s;
	void		*img_w;
	void		*mlx;
	void		*win;
	int			data_ok;
	int			what;
	char		*line;
	t_map		*map;
	t_texture	*texture;
	t_rotation	*rota;
}			t_core;

//Input_verifs
int		file_exists(char *filename, t_core *c);
int		first_checks_hub(int ac, char **av, t_core *core);
void	get_map_path(char *path, t_core *c);

//Parsing
int		read_hub(t_core *c);
void	take_map_data(t_core *c);
void	convert_rgb_c(t_core *c);
void	convert_rgb_f(t_core *c);
void	bit_shift_rgb(int r, int g, int b, t_core *c);
void	color_process(char *line, t_core *c);
void	check_color(t_core *c, char *line, char what);
void	read_map(t_core *c);
int		extension(char *str, char *ext);
int		test_it(char *line, t_core *c, int what);
void	check_surrounding_cells(t_core *c, int i, int j);

//Init
t_core	*init_core(t_core *core);

//print
void	print_map(char **map);
void	print_texture(t_core *c);

//utils
char	**splitt(char *s, char c);
int		str_len_modif(char *s);
int		its_top_bot(char *line);
char	*ft_strdup_end(const char *src);
char	*strdup_and_pad(char *src, int len);
int		is_digit(char *str);
char	**realloc_map(char **map, int size);
int		ct_line(char *s);
void	count_map_height(t_core *c);
void	verify_last_line(t_core *c);
void	count_map_lenght(t_core *c);
int		str_len_modif(char *s);
int		is_valid_data_extend(char *line, t_core *c);
int		is_good_data(char cell);

//free
void	free_map(t_map *map);
void	free_parsing(t_core *c);
void	free_tab(char **tab);
void	ft_exit(t_core *c);

//error exit
void	error_rgb(t_core *c, char **tab);
void	error_data(t_core *c);
void	textures_error_alloc(t_core *c);
void	error_map(t_core *c);
void	error_open_file(t_core *c);
void	error_extension(t_core *c);
void	error_argument(t_core *c);
void	error_wall(t_core *c, int i, int j);
void	error_player(t_core *c);
int		window_hook(int event, void *param);

//go_render
void	go_render(t_core *c);
int		hit_wall(double x, double y, double ray, t_core *c);
void	render_wall(t_core *c,
			double start_pixel, double end_pixel, void *img);
void	render_floor_sky(t_core *c,
			double start_pixel, double end_pixel);
int		key_hook(int key, void *tempo);
void	choose_wall(t_core *c, double start_pixel, double end_pixel, double current_ray);

//go_render_utils
double	normalize_angle(double ray);
double	get_angle_player(t_core *c);
int		get_pos_player_y(t_core *c, int check);
int		get_pos_player_x(t_core *c, int check);
int		check_coli(t_core *c, double pos_x, double pos_y);

//go_render_init
void	init_rota(t_rotation *rota, t_core *c);
void	init_mlx(t_core *c);

//ray_casting_3D
double	check_horizontal_3d(t_core *c, t_rotation *rota, double ray);
double	check_vertical_3d(t_core *c, t_rotation *rota, double ray);
void	send_ray_3d(t_core *c, t_rotation *rota, float current_ray);
void	render_ray_3d(t_core *c, t_rotation *rota,
			double current_ray);
void	cast_ray_3d(t_core *c);

// Texturiize
void	put_image(t_core *c);
#endif
