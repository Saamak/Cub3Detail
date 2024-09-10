/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:37:25 by ppitzini          #+#    #+#             */
/*   Updated: 2024/09/10 13:00:51 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	count_map_height(t_core *c)
{
	int	i;

	i = 0;
	while (c->map->map[i] != NULL)
		i++;
	c->map->height_line = i;
}

void	count_map_lenght(t_core *c)
{
	int	i;
	int	line_lenght;

	i = 0;
	c->map->lenght_line = 0;
	while (i < c->map->height_line)
	{
		line_lenght = ct_line(c->map->map[i]);
		if (line_lenght > c->map->lenght_line)
			c->map->lenght_line = line_lenght;
		i++;
	}
}

char	*ft_strdup_end(const char *src, t_core *c)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i] != '\0' && src[i] != '\n')
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
	{
		free_parsing(c);
		return (NULL);
	}
	i = 0;
	while (src[i] != '\0' && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	get_lenght_max(char **map)
{
	int	i;
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
		while (map[i][j] != '\0' && j < lenght_max)
		{
			if (map[i][j] == '\n')
				map[i][j] = ' ';
			j++;
		}
		j = 0;
		i++;
	}
}
