/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:47:11 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/28 16:55:26 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end(param);
	return (0);
}

void	key_view(t_core *c, int key)
{
	if (key == 79)
	{
		c->rota->p_angle = normalize_angle(c->rota->p_angle + (0.01 * SPEED));
		cast_ray_3d(c);
	}
	else if (key == 80)
	{
		c->rota->p_angle = normalize_angle(c->rota->p_angle - (0.01 * SPEED));
		cast_ray_3d(c);
	}
}

void	key_deplacement_one(t_core *c, int key)
{
	if (key == 26)
	{
		if (check_coli(c, c->rota->p_x + (sin(c->rota->p_angle) * (SPEED * 3)),
				c->rota->p_y + (cos(c->rota->p_angle) * (SPEED * 3))) == 1)
		{
			c->rota->p_x = c->rota->p_x + (sin(c->rota->p_angle) * SPEED);
			c->rota->p_y = c->rota->p_y + (cos(c->rota->p_angle) * SPEED);
			cast_ray_3d(c);
		}
	}
	else if (key == 22)
	{
		if (check_coli(c, c->rota->p_x + (-sin(c->rota->p_angle) * (SPEED * 3)),
				c->rota->p_y + (-cos(c->rota->p_angle) * (SPEED * 3))) == 1)
		{
			c->rota->p_x = c->rota->p_x + (-sin(c->rota->p_angle) * SPEED);
			c->rota->p_y = c->rota->p_y + (-cos(c->rota->p_angle) * SPEED);
			cast_ray_3d(c);
		}
	}
}

void	key_deplacement_two(t_core *c, int key)
{
	if (key == 4)
	{
		if (check_coli(c, c->rota->p_x + (-cos(c->rota->p_angle) * (SPEED * 3)),
				c->rota->p_y + (sin(c->rota->p_angle) * (SPEED * 3))) == 1)
		{
			c->rota->p_x = c->rota->p_x + (-cos(c->rota->p_angle) * SPEED);
			c->rota->p_y = c->rota->p_y + (sin(c->rota->p_angle) * SPEED);
			cast_ray_3d(c);
		}
	}
	else if (key == 7)
	{
		if (check_coli(c, c->rota->p_x + (cos(c->rota->p_angle) * (SPEED * 3)),
				c->rota->p_y + (-sin(c->rota->p_angle) * (SPEED * 3))) == 1)
		{
			c->rota->p_x = c->rota->p_x + (cos(c->rota->p_angle) * SPEED);
			c->rota->p_y = c->rota->p_y + (-sin(c->rota->p_angle) * SPEED);
			cast_ray_3d(c);
		}
	}
}

int	key_hook(int key, void *tempo)
{
	t_core	*c;

	c = (t_core *)tempo;
	if (key == 79 || key == 80)
		key_view(c, key);
	else if (key == 26 || key == 22)
		key_deplacement_one(c, key);
	else if (key == 4 || key == 7)
		key_deplacement_two(c, key);
	else if (key == 41)
		key_escape(c);
	return (0);
}
