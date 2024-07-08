/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:18:03 by ppitzini          #+#    #+#             */
/*   Updated: 2024/07/08 16:14:27 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	error_player(t_core *c)
{
	printf(B_R ERROR_PLAYER RESET);
	printf(BOLD END_LINE RESET);
	free_parsing(c);
	exit(0);
}

void	error_wall(t_core *c, int i, int j)
{
	printf(B_R ERROR_NOT_CLOSED RESET, i, j);
	free_parsing(c);
	exit(0);
}

void	error_argument(t_core *c)
{
	printf(B_R ERROR_ARGUMENTS RESET);
	printf(BOLD END_LINE RESET);
	free_parsing(c);
	exit(0);
}

void	error_extension(t_core *c)
{
	printf(B_R ERROR_EXTENSION RESET);
	printf(BOLD END_LINE RESET);
	free_parsing(c);
	exit(0);
}

void	error_map(t_core *c)
{
	printf(B_R ERROR_INVALID_MAP RESET);
	printf(BOLD END_LINE RESET);
	free_parsing(c);
	exit(0);
}
