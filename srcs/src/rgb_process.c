/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:11:19 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/26 16:11:21 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	bit_shift_rgb(int r, int g, int b, t_core *c)
{
	if (c->what == 'C')
	{
		c->texture->rgb_c = 0;
		c->texture->rgb_c += r << 16;
		c->texture->rgb_c += g << 8;
		c->texture->rgb_c += b;
	}
	else
	{
		c->texture->rgb_f = 0;
		c->texture->rgb_f += r << 16;
		c->texture->rgb_f += g << 8;
		c->texture->rgb_f += b;
	}
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != '\n' && str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) || str[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

void	convert_rgb_f(t_core *c)
{
	char	**tab;

	if (c == NULL || c->texture->F == NULL)
		error_rgb(c, NULL);
	tab = splitt(c->texture->F, ',');
	if ((tab[0] != NULL) || (tab[1] != NULL) || (tab[2] != NULL))
	{
		if (!is_digit(tab[0]) || !is_digit(tab[1]) || !is_digit(tab[2]))
			error_rgb(c, tab);
		c->map->r = atoi(tab[0]);
		c->map->g = atoi(tab[1]);
		c->map->b = atoi(tab[2]);
	}
	else
		error_rgb(c, tab);
	if (c->map->r < 0 || c->map->r > 255
		|| c->map->g < 0 || c->map->g > 255 || c->map->b < 0 || c->map->b > 255)
		error_rgb(c, tab);
	c->what = 'F';
	bit_shift_rgb(c->map->r, c->map->g, c->map->b, c);
	c->map->F = 1;
	free_tab(tab);
}

void	convert_rgb_c(t_core *c)
{
	char	**tab;

	if (c == NULL || c->texture->C == NULL)
		error_rgb(c, NULL);
	tab = splitt(c->texture->C, ',');
	if ((tab[0] != NULL) && (tab[1] != NULL) && (tab[2] != NULL))
	{
		if (!is_digit(tab[0]) || !is_digit(tab[1]) || !is_digit(tab[2]))
			error_rgb(c, tab);
		c->map->r = atoi(tab[0]);
		c->map->g = atoi(tab[1]);
		c->map->b = atoi(tab[2]);
	}
	else
		error_rgb(c, tab);
	if (c->map->r < 0 || c->map->r > 255
		|| c->map->g < 0 || c->map->g > 255 || c->map->b < 0 || c->map->b > 255)
		error_rgb(c, NULL);
	c->what = 'C';
	bit_shift_rgb(c->map->r, c->map->g, c->map->b, c);
	c->map->C = 1;
	free_tab(tab);
}
