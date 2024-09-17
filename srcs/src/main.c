/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:12:49 by ppitzini          #+#    #+#             */
/*   Updated: 2024/09/17 11:18:10 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_core	*c;

	c = NULL;
	c = init_core(c);
	printf(BOLD END_LINE RESET);
	printf(B_Y"----| Cub3D input verifications...\n\n"RESET);
	first_checks_hub(argc, argv, c);
	read_hub(c);
	printf(BOLD END_LINE RESET);
	go_render(c);
	printf(B_Y"----| Cub3D exit...\n\n"RESET);
	free_parsing(c);
	return (0);
}
