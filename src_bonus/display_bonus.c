/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 11:23:10 by eabdelha          #+#    #+#             */
/*   Updated: 2021/12/27 11:23:14 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	game_end(int keycode, t_par *par)
{
	if (keycode == 49)
	{
		free_map(par->map);
		read_map(par, par->arg);
		display(par);
		par->n_move = 0;
		mlx_hook(par->win, 2, 0L, move, par);
	}
	else if (keycode == ESC_KEY)
	{
		free_map(par->map);
		exit(0);
	}
	return (0);
}

void	put_img(t_par *par, char *img, int x, int y)
{
	void	*imgp;
	int		img_w;
	int		img_h;
	int		len;

	len = ft_strlen(R_PLAYER_IMG);
	imgp = mlx_xpm_file_to_image(par->mlx, img, &img_w, &img_h);
	mlx_put_image_to_window(par->mlx, par->win, imgp, x * FACTOR, y * FACTOR);
	if (!ft_strncmp(R_PLAYER_IMG, img, len)
		|| !ft_strncmp(L_PLAYER_IMG, img, len))
	{
		par->px = x;
		par->py = y;
	}
}

void	move_plyr(t_par *par, int V, int H)
{
	char	*movs;

	if (par->map[(par->py) + V][(par->px) + H] == 'E' && par->col != 0)
		return ;
	else if (par->map[(par->py) + V][(par->px) + H] == 'E' && par->col == 0)
		return (clear_win(par), par->px += H, par->py += V, (void)0);
	if (par->map[(par->py) + V][(par->px) + H] == 'C')
	{
		par->map[(par->py) + V][(par->px) + H] = '0';
		(par->col)--;
	}
	if (par->map[(par->py) + V][(par->px) + H] != '1')
	{
		put_img(par, GROUND_IMG, par->px, par->py);
		if (H >= 0)
			put_img(par, R_PLAYER_IMG, par->px + H, par->py + V);
		else
			put_img(par, L_PLAYER_IMG, par->px + H, par->py + V);
		movs = ft_itoa(++(par->n_move));
		put_img(par, WALL_IMG, 0, 0);
		mlx_string_put(par->mlx, par->win, 0, 0, COLR, movs);
		free(movs);
	}
}

void	display(t_par *par)
{
	int	x;
	int	y;

	y = -1;
	par->msg_px = ((par->px - 7) / 2) * FACTOR;
	par->msg_py = ((par->py) / 2) * FACTOR;
	while (*par->map && par->map[++y])
	{
		x = 0;
		while (**par->map && par->map[y][x])
		{
			if (par->map[y][x] == 'C' || par->map[y][x] == '0')
				put_img(par, GROUND_IMG, x, y);
			else if (par->map[y][x] == 'P')
				put_img(par, R_PLAYER_IMG, x, y);
			else if (par->map[y][x] == '1')
				put_img(par, WALL_IMG, x, y);
			else if (par->map[y][x] == 'E')
				put_img(par, EXIT_IMG, x, y);
			if (par->map[y][x] == 'C')
				put_img(par, COLLECT_IMG, x, y);
			x++;
		}
	}
}

void	clear_win(t_par *par)
{
	mlx_clear_window(par->mlx, par->win);
	if (par->map[par->py][par->px] == 'E')
		mlx_string_put(par->mlx, par->win, par->msg_px, par->msg_py, COLR, WON);
	else
		mlx_string_put(par->mlx, par->win, par->msg_px,
			par->msg_py, COLR, LOSS);
	mlx_hook(par->win, 2, 0L, game_end, par);
}
