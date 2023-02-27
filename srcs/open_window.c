#include "miniRT.h"

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	open_window(t_program prog)
{
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		ft_error();

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	int i = -1;
	int j;
	printf("%d, %d\n", WIDTH, HEIGHT);
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			if (prog.camera->vp->arr[i][j].color)
				printf("%d, %d, %d\n", j, i, prog.camera->vp->arr[i][j].color);
			mlx_put_pixel(img, j, i, prog.camera->vp->arr[i][j].color);
		}
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}