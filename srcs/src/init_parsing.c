/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:09:19 by ppitzini          #+#    #+#             */
/*   Updated: 2024/09/01 14:22:24 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_core	*init_texture(t_core *c)
{
	c->texture->no = NULL;
	c->texture->so = NULL;
	c->texture->we = NULL;
	c->texture->ea = NULL;
	c->texture->color_f = NULL;
	c->texture->color_c = NULL;
	return (c);
}

t_core	*init_core_second(t_core *c)
{
	c->mlx = 0;
	c->win = 0;
	c->line = NULL;
	c->what = 0;
	c->data_ok = 0;
	c->rota = NULL;
	c->texture = malloc(sizeof(t_texture));
	if (!c->texture)
		textures_error_alloc(c);
	return (init_texture(c));
}

t_core	*init_map(t_core *c)
{
	c->map->n_o = 0;
	c->map->s_o = 0;
	c->map->w_e = 0;
	c->map->e_a = 0;
	c->map->c_number = 0;
	c->map->f_number = 0;
	c->map->lenght_line = 0;
	c->map->height_line = 0;
	c->map->i = 0;
	c->map->r = 0;
	c->map->g = 0;
	c->map->b = 0;
	c->map->fd = 0;
	c->map->len_prev_line = 0;
	c->map->len_this_line = 0;
	c->map->map = NULL;
	c->map->map_path = NULL;
	c->map->player_here = 0;
	return (init_core_second(c));
}

t_core	*init_core(t_core *c)
{
	c = malloc(sizeof(t_core));
	if (!c)
	{
		perror("Error allocating memory for core\n");
		exit(EXIT_FAILURE);
	}
	c->map = malloc(sizeof(t_map));
	if (!c->map)
	{
		free(c);
		perror("Error allocating memory for map\n");
		exit(EXIT_FAILURE);
	}
	return (init_map(c));
}
