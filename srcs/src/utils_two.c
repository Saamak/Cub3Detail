/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:33:04 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/26 16:27:56 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	verify_last_line(t_core *c)
{
	int	x;

	x = 0;
	while (c->map->map[c->map->height_line - 1][x] != '\0')
	{
		if (c->map->map[c->map->height_line - 1][x] != '1'
			&& c->map->map[c->map->height_line - 1][x] != ' '
			&& c->map->map[c->map->height_line - 1][x] != '\n')
			error_wall(c, c->map->height_line - 1, x);
		x++;
	}
}

int	its_top_bot(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '1')
		return (0);
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '1')
			return (0);
		i++;
	}
	printf(B_G"   | Map found \xE2\x9C\x93 \n"RESET);
	return (1);
}

int	count_word(char *s, char c)
{
	int	c_w;
	int	tmp;

	tmp = 0;
	c_w = 0;
	while (*s != '\0')
	{
		if (tmp == 1 && *s == c)
			tmp = 0;
		if (tmp == 0 && *s != c)
		{
			tmp = 1;
			c_w++;
		}
		s++;
	}
	return (c_w);
}

char	**splitt(char *s, char c)
{
	char	**dest;
	int		i;
	int		x;

	x = 0;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!dest)
		return (NULL);
	while (*s)
	{
		if (s[0] == c)
			s++;
		else
		{
			i = 0;
			while (s[i] != '\0' && s[i] != c)
				i++;
			dest[x++] = ft_substr(s, 0, i);
			s = s + i;
		}
	}
	dest[x] = NULL;
	return (dest);
}

int	ct_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}
