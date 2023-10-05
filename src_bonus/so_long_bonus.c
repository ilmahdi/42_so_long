/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 11:23:45 by eabdelha          #+#    #+#             */
/*   Updated: 2021/12/27 11:23:48 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	close_win(t_par *par)
{
	free_map(par->map);
	exit(0);
	return (0);
}

int	move_enemy(t_par *par)
{
	t_enm			enm;
	static t_stp	stp;
	char			enemy[14];
	static int		refresh;
	static int		i;

	enm = (t_enm){};
	ft_strlcpy(enemy, "../img/e1.xpm\0", 14);
	if (par->map[par->py][par->px] == 'E'
		|| (par->px == stp.x && par->py == stp.y))
		return (clear_win(par), refresh = -1, stp.rep = 0, 0);
	enemy_rand_pos(par, &stp.x, &stp.y, refresh);
	if (refresh++ != 7000 && par->map[stp.y][stp.x] != '1')
	{
		if (refresh % 1500 != 0)
			return (0);
		if (++i == 6)
			i = 1;
		return (enemy[8] = i + '0', put_img(par, enemy, stp.x, stp.y), 0);
	}
	refresh = 0;
	increment_move(&enm, &stp, par);
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
	par.win = mlx_new_window(par.mlx, par.px * FACTOR, par.py * FACTOR, W_NAME);
	display(&par);
	mlx_hook(par.win, 17, 0L, close_win, &par);
	mlx_hook(par.win, 2, 0L, move, &par);
	mlx_loop_hook(par.mlx, move_enemy, &par);
	mlx_loop(par.mlx);
	return (0);
}
