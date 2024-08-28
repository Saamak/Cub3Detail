/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:47:11 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/28 18:24:48 by pirulenc         ###   ########.fr       */
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

int	key_hook(int key, void *tempo)
{
	t_core	*c;

	c = (t_core *)tempo;
	if (key == 79 || key == 80)
		key_view(c, key);
	else if (key == 26)
		key_deplacement_up(c, key);
	else if (key == 22)
		key_deplacement_down(c, key);
	else if (key == 4)
		key_deplacement_left(c, key);
	else if (key == 7)
		key_deplacement_right(c, key);
	else if (key == 41)
		key_escape(c);
	return (0);
}
