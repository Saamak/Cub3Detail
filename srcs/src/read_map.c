/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:37:35 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/27 17:46:07 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_good_data(char cell)
{
	if (cell == '0' || cell == '1' || cell == '2' || cell == 'N'
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
		if (c->line[i] != '0' && c->line[i] != '1' && c->line[i] != '2'
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

void	store_map(t_core *c)
{
	int	i;

	i = 0;
	c->map->map = malloc(sizeof(char *) * (c->map->i + 1));
	c->map->map[i] = ft_strdup(c->line);
	i++;
	free(c->line);
	c->line = get_next_line(c->map->fd);
	while (c->line != NULL)
	{
		if (c->line[0] == '\n')
			error_map(c);
		check_tab(c);
		c->map->len_prev_line = str_len_modif(c->map->map[i - 1]);
		c->map->map = realloc_map(c->map->map, sizeof(char *) * (i + 2));
		c->map->map[i] = strdup_and_pad(c->line, c->map->len_prev_line);
		c->map->map[i + 1] = NULL;
		i++;
		free(c->line);
		c->line = get_next_line(c->map->fd);
	}
	c->map->map[i] = NULL;
	if (c->map->player_here == 0)
		error_player(c);
	// print_map(c->map->map);
}

void	read_map(t_core *c)
{
	c->line = get_next_line(c->map->fd);
	while (c->line != NULL)
	{
		if (c->line[0] != '\n' && !its_top_bot(c->line))
			error_map(c);
		else if (its_top_bot(c->line))
			break ;
		free(c->line);
		c->line = get_next_line(c->map->fd);
	}
	if (!c->line)
		error_map(c);
	store_map(c);
	verify_map_integrity(c);
	count_map_height(c);
	count_map_lenght(c);
	verify_last_line(c);
}
