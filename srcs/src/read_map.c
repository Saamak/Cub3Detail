/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:37:35 by ppitzini          #+#    #+#             */
/*   Updated: 2024/09/10 15:57:25 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

int	get_map_height(int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		i++;
	}
	free(line);
	close(fd);
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
	if (c->map->player_here == 0)
		error_player(c);
}

void	read_map(t_core *c)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
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
	c->map->tmp_fd = open(c->map->map_path, O_RDONLY);
	size = get_map_height(c->map->tmp_fd);
	store_map(c, size - i);
	verify_map_integrity(c);
	count_map_height(c);
	count_map_lenght(c);
	verify_last_line(c);
}
