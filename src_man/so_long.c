/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:22:41 by eabdelha          #+#    #+#             */
/*   Updated: 2021/12/28 17:37:10 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_win(t_par *par)
{
	free_map(par->map);
	exit(0);
	return (0);
}

int	move(int keycode, t_par *par)
{
	if (keycode == UP_KEY)
		move_plyr(par, UP_STEP, ZERO_MOVE);
	else if (keycode == DOWN_KEY)
		move_plyr(par, DOWN_STEP, ZERO_MOVE);
	else if (keycode == RIGHT_KEY)
		move_plyr(par, ZERO_MOVE, RIGHT_STEP);
	else if (keycode == LEFT_KEY)
		move_plyr(par, ZERO_MOVE, LEFT_STEP);
	else if (keycode == ESC_KEY)
	{
		free_map(par->map);
		exit(0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_par	par;

	par = (t_par){};
	if (ac != 2)
		map_invalid(INVALID_N_ARGS, &par);
	par.arg = av[1];
	read_map(&par, av[1]);
	par.mlx = mlx_init();
	par.win = mlx_new_window(par.mlx, par.px * FACTOR, par.py * FACTOR, NAME_W);
	display(&par);
	mlx_hook(par.win, 2, 0L, move, &par);
	mlx_hook(par.win, 17, 0L, close_win, &par);
	mlx_loop(par.mlx);
	return (0);
}
