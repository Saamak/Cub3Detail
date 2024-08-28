/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_deplacement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:21:46 by pirulenc          #+#    #+#             */
/*   Updated: 2024/08/28 18:27:14 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	key_deplacement_up(t_core *c)
{
	if (check_coli(c, c->rota->p_x + (sin(c->rota->p_angle) * (SPEED * 3)),
			c->rota->p_y + (cos(c->rota->p_angle) * (SPEED * 3))) == 1
			&& check_coli(c, c->rota->p_x + (sin(c->rota->p_angle) * (SPEED * 3)),
			c->rota->p_y) == 1
			&& check_coli(c, c->rota->p_x,
			c->rota->p_y + (cos(c->rota->p_angle) * (SPEED * 3))) == 1)
	{
		c->rota->p_x = c->rota->p_x + (sin(c->rota->p_angle) * SPEED);
		c->rota->p_y = c->rota->p_y + (cos(c->rota->p_angle) * SPEED);
		cast_ray_3d(c);
	}
}

void	key_deplacement_down(t_core *c)
{
	if (check_coli(c, c->rota->p_x + (-sin(c->rota->p_angle) * (SPEED * 3)),
			c->rota->p_y + (-cos(c->rota->p_angle) * (SPEED * 3))) == 1
			&& check_coli(c, c->rota->p_x,
			c->rota->p_y + (-cos(c->rota->p_angle) * (SPEED * 3))) == 1
			&& check_coli(c, c->rota->p_x + (-sin(c->rota->p_angle) * (SPEED * 3)),
			c->rota->p_y) == 1)
	{
		c->rota->p_x = c->rota->p_x + (-sin(c->rota->p_angle) * SPEED);
		c->rota->p_y = c->rota->p_y + (-cos(c->rota->p_angle) * SPEED);
		cast_ray_3d(c);
	}
}

void	key_deplacement_left(t_core *c)
{
	if (check_coli(c, c->rota->p_x + (-cos(c->rota->p_angle) * (SPEED * 3)),
			c->rota->p_y + (sin(c->rota->p_angle) * (SPEED * 3))) == 1
			&& check_coli(c, c->rota->p_x,
			c->rota->p_y + (sin(c->rota->p_angle) * (SPEED * 3))) == 1
			&& check_coli(c, c->rota->p_x + (-cos(c->rota->p_angle) * (SPEED * 3)),
			c->rota->p_y) == 1)
	{
		c->rota->p_x = c->rota->p_x + (-cos(c->rota->p_angle) * SPEED);
		c->rota->p_y = c->rota->p_y + (sin(c->rota->p_angle) * SPEED);
		cast_ray_3d(c);
	}
}

void	key_deplacement_right(t_core *c)
{
	if (check_coli(c, c->rota->p_x + (cos(c->rota->p_angle) * (SPEED * 3)),
			c->rota->p_y + (-sin(c->rota->p_angle) * (SPEED * 3))) == 1
			&& check_coli(c, c->rota->p_x,
			c->rota->p_y + (-sin(c->rota->p_angle) * (SPEED * 3))) == 1
			&& check_coli(c, c->rota->p_x + (cos(c->rota->p_angle) * (SPEED * 3)),
			c->rota->p_y) == 1)
	{
		c->rota->p_x = c->rota->p_x + (cos(c->rota->p_angle) * SPEED);
		c->rota->p_y = c->rota->p_y + (-sin(c->rota->p_angle) * SPEED);
		cast_ray_3d(c);
	}
}