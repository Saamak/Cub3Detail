/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:37:35 by ppitzini          #+#    #+#             */
/*   Updated: 2024/09/09 18:53:34 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_good_data(char cell)
{
	if (cell == '0' || cell == '1' || cell == 'N'
		|| cell == 'S' || cell == 'E' || cell == 'W')
		return (1);
	else
		return (0);
}

void	verify_map_integrity(t_core *c)
{
	int	i;
	int	j;

	i = 0;
	while (c->map->map[i] != NULL)
	{
		j = 0;
		if (c->map->map[i][j] == '0' || c->map->map[i][j] == 'N'
			|| c->map->map[i][j] == 'S' || c->map->map[i][j] == 'E'
			|| c->map->map[i][j] == 'W')
			error_wall(c, i, j);
		while (c->map->map[i][j] != '\0')
		{
			check_surrounding_cells(c, i, j);
			j++;
		}
		i++;
	}
}

void	check_tab(t_core *c)
{
	int	i;

	i = 0;
	while (c->line[i] != '\n' && c->line[i])
	{
		if (c->line[i] != '0' && c->line[i] != '1'
			&& c->line[i] != ' ' && c->line[i] != 'P' && c->line[i] != 'N'
			&& c->line[i] != 'S' && c->line[i] != 'E' && c->line[i] != 'W')
			error_map(c);
		else if (c->line[i] == 'N' || c->line[i] == 'S'
			|| c->line[i] == 'E' || c->line[i] == 'W')
		{
			if (c->map->player_here == 1)
				error_map(c);
			c->map->player_here = 1;
		}
		else if (c->line[i] == '\t')
		{
			printf("Error\n");
			error_map(c);
		}
		i++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

int	get_lenght_max(char **map)
{
	int i;
	int	j;
	int	max;

	max = 0;
	j = 0;
	i = 0;
	while (map[i])
	{
		while (map[i][j] != '\0')
			j++;
		if (j > max)
			max = j;
		j = 0;
		i++;
	}
	return (max);
}

// void	ft_malloc_map(char **new_map, int i, int lenght_max, t_core *c)
// {
// 	int	j;

// 	j = 0;
// 	while (j < i + 2)
// 	{
// 		new_map[j] = ft_calloc(sizeof(char), (lenght_max + 1));
// 		if (!new_map[j])
// 		{
// 			while (j >= 0)
// 			{
// 				free(new_map[j]);
// 				j--;
// 			}
// 			free(new_map);
// 			free_parsing(c);
// 		}
// 		j++;
// 	}
// }
void print_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}

// char	**ft_recreate_map(t_core *c, int i, char *line)
// {
// 	int		lenght_max;
// 	char	**new_map;
// 	int		j;
// 	int		x;

// 	x = 0;
// 	j = 0;
// 	lenght_max = get_lenght_max(c->map->map);
// 	new_map = malloc(sizeof(char *) * (i + 2));
// 	printf("new map char* %lu\n", sizeof(char *) * (i + 2));
// 	if (!new_map)
// 		free_parsing(c);
// 	ft_malloc_map(new_map, i, lenght_max, c);
// 	while (j < i)
// 	{
// 		while (c->map->map[j][x] != '\0')
// 		{
// 			new_map[j][x] = c->map->map[j][x];
// 			x++;
// 		}
// 		x = 0;
// 		j++;
// 	}
// 	while (line[x] != '\0')
// 	{
// 		new_map[i][x] = line[x];
// 		x++;
// 	}
// 	new_map[i + 1] = NULL;
// 	free_tab(c->map->map);
// 	c->map->map = NULL;
// 	printf("new_map address: %p\n", new_map);
// 	return (new_map);
// }

void	ft_replace_with_spaces(char **map)
{
	int	lenght_max;
	int	i;
	int	j;

	i = 0;
	j = 0;
	lenght_max = get_lenght_max(map);
	while (map[i])
	{
		while (map[i][j] != '\0'  && j < lenght_max)
		{
			if (map[i][j] == '\n')
				map[i][j] = ' ';
			j++;
		}
		j = 0;
		i++;
	}
}

int get_map_height(int fd)
{
	char *line;
	int i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		free(line);
		i++;
	}
	free(line);
	return (i);

}



void	store_map(t_core *c, int size)
{
	int	i;

	i = 1;
	c->map->map = ft_calloc(sizeof(char *), size + 2);
	c->map->map[0] = ft_strdup(c->line);
	while (1)
	{
		if (c->line[0] == '\n')
			error_map(c);
		check_tab(c);
		free(c->line);
		c->line = get_next_line(c->map->fd);
		if (!c->line)
			break ;
		c->map->map[i] = ft_strdup(c->line);
		i++;
	}
	c->map->map[i] = NULL;
	ft_replace_with_spaces(c->map->map);
	print_map(c->map->map);
	if (c->map->player_here == 0)
		error_player(c);
}

////////////////////////////////////////////////////////////////////////////////////////////

//void	store_map(t_core *c)
//{
//	int	i;
//
//	i = 0;
//	c->map->map = malloc(sizeof(char *) * (c->map->i + 1));
//	c->map->map[i] = ft_strdup(c->line);
//	i++;
//	free(c->line);
//	c->line = get_next_line(c->map->fd);
//	while (c->line != NULL)
//	{
//		if (c->line[0] == '\n')
//			error_map(c);
//		check_tab(c);
//		c->map->len_prev_line = str_len_modif(c->map->map[i - 1]);
//		c->map->map = realloc_map(c->map->map, sizeof(char *) * (i + 2));
//		c->map->map[i] = strdup_and_pad(c->line, c->map->len_prev_line, c);
//		c->map->map[i + 1] = NULL;
//		i++;
//		free(c->line);
//		c->line = get_next_line(c->map->fd);
//	}
//	c->map->map[i] = NULL;
//	if (c->map->player_here == 0)
//		error_player(c);
//}

void	read_map(t_core *c)
{
	int i = 0;
	c->line = get_next_line(c->map->fd);
	while (c->line != NULL)
	{
		if (c->line[0] != '\n' && !its_top_bot(c->line))
			error_map(c);
		else if (its_top_bot(c->line))
			break ;
		free(c->line);
		c->line = get_next_line(c->map->fd);
		i++;
	}
	if (!c->line)
		error_map(c);

	int fd = open(c->map->map_path, O_RDONLY);
	int size = get_map_height(fd);

	store_map(c, size - i);
	verify_map_integrity(c);
	count_map_height(c);
	count_map_lenght(c);
	verify_last_line(c);
}
