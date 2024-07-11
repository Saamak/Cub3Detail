/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:37:35 by ppitzini          #+#    #+#             */
/*   Updated: 2024/07/11 15:32:20 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int is_good_data(char cell)
{
	if(cell == '0' || cell == '1' || cell == '2' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
		return 1;
	else
		return 0;
}

void	verify_map_integrity(t_core *c)
{
	int	i = 0, j;

	while (c->map->map[i] != NULL)
	{
		j = 0;
		if (c->map->map[i][j] == '0' || c->map->map[i][j] == 'N'
			|| c->map->map[i][j] == 'S' || c->map->map[i][j] == 'E'
			|| c->map->map[i][j] == 'W')
			error_wall(c, i, j);
		while (c->map->map[i][j] != '\0')
		{
			if (c->map->map[i][j] == '0' || c->map->map[i][j] == 'N'
				|| c->map->map[i][j] == 'S' || c->map->map[i][j] == 'E'
				|| c->map->map[i][j] == 'W')
			{
				if (i > 0 && !is_good_data(c->map->map[i - 1][j]))
					error_wall(c, i - 1, j);
				if (c->map->map[i + 1] != NULL
					&& !is_good_data(c->map->map[i + 1][j]))
					error_wall(c, i + 1, j);
				if (j > 0 && !is_good_data(c->map->map[i][j - 1]))
					error_wall(c, i, j - 1);
				if (c->map->map[i][j + 1] != '\0'
					&& !is_good_data(c->map->map[i][j + 1]))
					error_wall(c, i, j + 1);
			}
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

char	*strdup_and_pad(char *src, int len)
{
	int		src_len;
	char	*dst;
	int		i;

	src_len = ft_strlen(src);
	if (src_len > len)
		len = src_len;
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = ' ';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	store_map(t_core *c)
{
	int	i;

	i = 0;
	c->map->map = malloc(sizeof(char *) * (c->map->i + 1));
	c->map->map[i] = ft_strdup(c->line);
	i++;
	free(c->line);
	while ((c->line = get_next_line(c->map->fd)) != NULL)
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
	}
	c->map->map[i] = NULL;
	if (c->map->player_here == 0)
		error_player(c);
	print_map(c->map->map);
}

void	read_map(t_core *c)
{
	while ((c->line = get_next_line(c->map->fd)) != NULL)
	{
		if (c->line[0] != '\n' && !its_top_bot(c->line))
			error_map(c);
		else if (its_top_bot(c->line))
			break ;
		free(c->line);
	}
	if (!c->line)
		error_map(c);
	store_map(c);
	verify_map_integrity(c);
	count_map_height(c);
	count_map_lenght(c);
	verify_last_line(c);
}
