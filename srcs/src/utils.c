/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:37:25 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/27 18:07:44 by ppitzini         ###   ########.fr       */
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
