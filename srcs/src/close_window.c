#include "../../includes/cub3D.h"

int window_hook(int event, void* param)
{
	if(event == 0)
		mlx_loop_end(param);
	return (0);
	// Fonctionne mais ce message d'erreur est affiché :
		//[MacroLibX] Error : Graphics allocator : some user-dependant allocations were not freed before destroying the display
		//(1 active allocations).
	 	//You may have not destroyed all the MLX resources you've created
}
