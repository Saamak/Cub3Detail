/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:25:18 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/27 17:13:38 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	print_texture(t_core *c)
{
	printf(B_Y"\n\n----| Reading Data : \n\n"RESET);
	printf(B_Y"   |NO: %s\n", c->texture->no);
	printf("   |SO: %s\n", c->texture->so);
	printf("   |WE: %s\n", c->texture->we);
	printf("   |EA: %s\n", c->texture->ea);
	printf("   |RGB C: %d\n", c->texture->rgb_c);
	printf("   |RGB F: %d\n"RESET, c->texture->rgb_f);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	printf(B_G"\n\n----|Map read [OK]\n\n"RESET);
	while (map[i])
	{
		if (map[i] != NULL)
			printf("|%s", map[i]);
		else
			printf("(null)");
		i++;
	}
	printf(" -----------END OF MAP---------------\n");
	printf("\n\n");
}
