/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:09:08 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/27 17:23:25 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->map == NULL)
		return ;
	while (map->map[i])
	{
		free(map->map[i]);
		i++;
	}
}

void	free_texture(t_core *c)
{
	if (c->texture->no)
		free(c->texture->no);
	if (c->texture->so)
		free(c->texture->so);
	if (c->texture->we)
		free(c->texture->we);
	if (c->texture->ea)
		free(c->texture->ea);
	if (c->texture->color_c)
		free(c->texture->color_c);
	if (c->texture->color_f)
		free(c->texture->color_f);
	if (c->texture)
		free(c->texture);
}

void	free_parsing(t_core *c)
{
	if (c)
	{
		if (c->line)
			free(c->line);
		if (c->map)
		{
			close(c->map->fd);
			if (c->map->map)
				free_tab(c->map->map);
			free(c->map);
		}
		if (c->texture)
			free_texture(c);
		free(c);
	}
	exit(1);
}
