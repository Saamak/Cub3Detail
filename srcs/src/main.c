#include "../../includes/cub3D.h"

int	main (int argc, char **argv)
{
	t_core	*c;

	c = NULL;
	c = init_core(c);

	printf(BOLD END_LINE RESET);
	printf(B_Y"----| Cub3D input verifications...\n\n"RESET);
	first_checks_hub(argc, argv, c);
	read_hub(c);
	print_texture(c);
	printf(BOLD END_LINE RESET);
	// go_render(c);
	return (0);
}
