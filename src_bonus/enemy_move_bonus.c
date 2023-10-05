/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 11:23:21 by eabdelha          #+#    #+#             */
/*   Updated: 2021/12/27 11:23:24 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_val_path(t_par *par, int y, int x)
{
	char	set[4];
	int		i;

	ft_strlcpy(set, "0PC\0", 4);
	i = 0;
	while (set[i])
	{
		if (par->map[y][x] == set[i])
			return (1);
		i++;
	}
	return (0);
}

void	enemy_rand_pos(t_par *par, int*x, int *y, int pass)
{
	static int	pos_e;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (++pos_e == 1 || pass == -1)
	{
		while (*par->map && par->map[i])
			i++;
		while (*par->map && **par->map && par->map[0][j])
			j++;
		(*y) = rand() % i;
		(*x) = rand() % j;
		while ((par->map[(*y)][(*x)] != '0' && par->map[(*y)][(*x)] != 'C')
			|| par->map[(*y)][(*x)] == 'P')
		{
			(*y) = rand() % i;
			(*x) = rand() % j;
		}
	}
}

void	count_prob(t_par *par, t_enm *enm, t_stp *stp)
{
	while (check_val_path(par, stp->sty, stp->x) && stp->sty-- >= 0)
		enm->yu++;
	stp->sty = stp->y;
	while (check_val_path(par, stp->sty, stp->x) && stp->sty++ >= 0)
		enm->yd++;
	while (check_val_path(par, stp->y, stp->stx) && stp->stx-- >= 0)
		enm->xl++;
	stp->stx = stp->x;
	while (check_val_path(par, stp->y, stp->stx) && stp->stx++ >= 0)
		enm->xr++;
	enm->arr = alloc_verify(par, (enm->xl + enm->xr + enm->yu + enm->yd));
	while (enm->l < enm->xl)
		enm->arr[enm->l++] = enm->xl;
	while (enm->l < enm->xr + enm->xl)
		enm->arr[enm->l++] = enm->xr;
	while (enm->l < enm->yu + enm->xl + enm->xr)
		enm->arr[enm->l++] = enm->yu;
	while (enm->l < enm->yd + enm->xl + enm->xr + enm->yu)
		enm->arr[enm->l++] = enm->yd;
	while (stp->rep <= 0 && (enm->xl + enm->xr + enm->yu + enm->yd) != 4)
	{
		enm->pos = rand() % (enm->xl + enm->xr + enm->yu + enm->yd);
		stp->rep = rand() % ((enm->arr[enm->pos]));
	}
	free(enm->arr);
}

void	get_steps(t_enm *enm, t_stp *stp)
{
	stp->stx = 0;
	stp->sty = 0;
	if (enm->arr[enm->pos] == enm->xl)
		stp->stx = -1;
	else if (enm->arr[enm->pos] == enm->yu)
		stp->sty = -1;
	else if (enm->arr[enm->pos] == enm->yd && enm->yd != enm->yu)
		stp->sty = 1;
	else if (enm->arr[enm->pos] == enm->xr && enm->xr != enm->xl)
		stp->stx = 1;
}

void	increment_move(t_enm *enm, t_stp *stp, t_par *par)
{
	put_img(par, GROUND_IMG, stp->x, stp->y);
	if (par->map[stp->y][stp->x] == 'C')
		put_img(par, COLLECT_IMG, stp->x, stp->y);
	if (stp->rep <= 0)
	{
		stp->stx = stp->x;
		stp->sty = stp->y;
		count_prob(par, enm, stp);
		get_steps(enm, stp);
	}
	stp->rep--;
	if (stp->rep >= 0)
	{
		stp->x += stp->stx;
		stp->y += stp->sty;
	}
	put_img(par, ENMEY_IMG, stp->x, stp->y);
}
