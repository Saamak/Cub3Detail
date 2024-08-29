/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:32:57 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/29 18:41:07 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	color_process(char *line, t_core *c)
{
	while (*line == ' ')
		line++;
	if (*line == 'F' && *(line + 1) == ' ')
	{
		if (c->texture->color_f)
			error_data(c);
		else
			check_color(c, line, 'F');
	}
	else if (*line == 'C' && *(line + 1) == ' ')
	{
		if (c->texture->color_c)
			error_data(c);
		else
			check_color(c, line, 'C');
	}
	else
		error_data(c);
}

void	check_color(t_core *c, char *line, char what)
{
	int	i;

	i = 1;
	line += 1;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n')
	{
		error_map(c);
	}
	if (what == 'F')
	{
		c->texture->color_f = ft_strdup_end(line + i, c);
		convert_rgb_f(c);
	}
	else if (what == 'C')
	{
		c->texture->color_c = ft_strdup_end(line + i, c);
		convert_rgb_c(c);
	}
}
