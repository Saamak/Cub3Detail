/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:47:11 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/27 02:30:46 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end(param);
	return (0);
	// Fonctionne mais ce message d'erreur est affiché :
		//[MacroLibX] Error : Graphics allocator : some user-dependant allocations were not freed before destroying the display
		//(1 active allocations).
	 	//You may have not destroyed all the MLX resources you've created
}

int	key_hook(int key, void *tempo)
{
	t_core	*c;

	c = (t_core *)tempo;
	if (key == 79)// fleche droite
	{
		c->rota->p_angle = normalize_angle(c->rota->p_angle + (0.01 * SPEED));
		cast_ray_3d(c);
	}
	else if (key == 80)// fleche gauche
	{
		c->rota->p_angle = normalize_angle(c->rota->p_angle - (0.01 * SPEED));
		cast_ray_3d(c);
	}
	else if (key == 26)// W move up
	{
		if (check_collision(c, c->rota->p_x + (sin(c->rota->p_angle) * (SPEED * 2)), c->rota->p_y + (cos(c->rota->p_angle) * (SPEED * 2))) == 1)
		{
			c->rota->p_x = c->rota->p_x + (sin(c->rota->p_angle) * SPEED);
			c->rota->p_y = c->rota->p_y + (cos(c->rota->p_angle) * SPEED);
			cast_ray_3d(c);
		}
	}
	else if (key == 22)// S move down
	{
		if (check_collision(c, c->rota->p_x + (-sin(c->rota->p_angle) * (SPEED * 2)), c->rota->p_y + (-cos(c->rota->p_angle) * (SPEED * 2))) == 1)
		{
			c->rota->p_x = c->rota->p_x + (-sin(c->rota->p_angle) * SPEED);
			c->rota->p_y = c->rota->p_y + (-cos(c->rota->p_angle) * SPEED);
			cast_ray_3d(c);
		}
	}
	else if (key == 4)// D move right
	{
		if (check_collision(c, c->rota->p_x + (-cos(c->rota->p_angle) * (SPEED * 2)), c->rota->p_y + (sin(c->rota->p_angle) * (SPEED * 2))) == 1)
		{
			c->rota->p_x = c->rota->p_x + (-cos(c->rota->p_angle) * SPEED);
			c->rota->p_y = c->rota->p_y + (sin(c->rota->p_angle) * SPEED);
			cast_ray_3d(c);
		}
	}
	else if (key == 7)// A move left
	{
		if (check_collision(c, c->rota->p_x + (cos(c->rota->p_angle) * (SPEED * 2)), c->rota->p_y + (-sin(c->rota->p_angle) * (SPEED * 2))) == 1)
		{
			c->rota->p_x = c->rota->p_x + (cos(c->rota->p_angle) * SPEED);
			c->rota->p_y = c->rota->p_y + (-sin(c->rota->p_angle) * SPEED);
			cast_ray_3d(c);
		}
	}
	return (0);
}
