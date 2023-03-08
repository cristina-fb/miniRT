#include "miniRT.h"

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	open_window(t_program prog, clock_t start)
{
	clock_t end;
    double cpu_time_used;
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
	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("El tiempo de ejecución de la porción de código fue de %f segundos.\n", cpu_time_used);
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			mlx_put_pixel(img, j, i, prog.camera->vp->arr[i][j].color);
		}
	}

	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("El tiempo de ejecución de la porción de código fue de %f segundos.\n", cpu_time_used);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}