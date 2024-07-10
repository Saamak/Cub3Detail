/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:58 by ppitzini          #+#    #+#             */
/*   Updated: 2024/07/10 19:46:53 by pirulenc         ###   ########.fr       */
/*                                                                            */
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
# define PI "3,14159265"
# define FOV 60
# define TILE 15
# define SCREEN_HEIGHT 720
# define SCREEN_LENGHT 1280

// STRUCTURES

typedef struct s_rotation
{
	double	angle_c;
	double	angle_l;
	double	angle_r;
	int	p_x;
	int	p_y;
	int	pix_x;
	int	pix_y;
	float	fov_rd;
}t_rotation;

typedef struct s_map
{
	int		fd;
	int		lenght_line;
	int		height_line;
	int		i;
	char	*map_path;
	char	**map;
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		C;
	int		F;
	int		player_here;
	int		r;
	int		g;
	int		b;
}				t_map;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*F;
	char	*C;
	int		rgb_f;
	int		rgb_c;
}				t_texture;

typedef struct map_core
{
	void		*mlx;
	void		*win;
	int			data_ok;
	int			what;
	char		*line;
	t_map		*map;
	t_texture	*texture;
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
int	extension(char *str, char *ext);

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
int		is_digit(char *str);
char	**realloc_map(char **map, int size);
int		ct_line (char *s);
void	count_map_height(t_core *c);
void	verify_last_line(t_core *c);
void	count_map_lenght(t_core *c);

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

//go_render
void	go_render(t_core *c);

//matrice_rotation
t_rotation  *start_rotation(t_core *c);

#endif
