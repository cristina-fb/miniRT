#include "miniRT.h"
#define WIDTH 1920
#define HEIGHT 1080

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	open_window(t_program prog)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(prog.s_width, prog.s_height, "miniRT", true);
	if (!mlx)
		ft_error();

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, prog.s_width, prog.s_height);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	mlx_put_pixel(img, 100, 100, 0xFF0000FF);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}