/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:37:25 by ppitzini          #+#    #+#             */
/*   Updated: 2024/07/08 16:37:27 by ppitzini         ###   ########.fr       */
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
	printf(B_G"   |map height = %d\n"RESET, c->map->height_line);
}

void	count_map_lenght(t_core *c)
{
	int	i = 0;
	int	line_lenght;

	c->map->lenght_line = 0;
	while (i < c->map->height_line)
	{
		line_lenght = ct_line(c->map->map[i]);
		if (line_lenght > c->map->lenght_line)
			c->map->lenght_line = line_lenght;
		i++;
	}
	printf(B_G"   |Longest map lenght = %d\n"RESET, c->map->lenght_line);
}

char	**realloc_map(char **map, int size)
{
	char	**new_map;

	new_map = realloc(map, sizeof(char *) * size);
	if (new_map == NULL)
	{
		fprintf(stderr, "Error: realloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_map[size - 1] = NULL;
	return (new_map);
}

char	*ft_strdup_end(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i] != '\0' && src[i] != '\n')
	{
		i++;
	}
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
	{
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
