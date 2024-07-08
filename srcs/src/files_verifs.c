/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_verifs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:21:56 by ppitzini          #+#    #+#             */
/*   Updated: 2024/07/08 17:57:45 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	file_exists(char *filename, t_core *c)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	printf("filename : %s\n", filename);
	if (fd == -1)
	{
		printf(B_R"   |Error : File %s does not exist"
			"\u274c \n"RESET, filename);
		free_parsing(c);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf(B_G"   |File %s exists \xE2\x9C\x93 \n\n"RESET, filename);
		close(fd);
		return (1);
	}
}
