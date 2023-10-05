/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 11:23:34 by eabdelha          #+#    #+#             */
/*   Updated: 2021/12/27 11:23:37 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	map_invalid(int iden, t_par *par)
{
	int	i;

	i = -1;
	ft_putendl_fd("Erorr", 2);
	if (iden == INVALID_CHAR)
		ft_putendl_fd("Invalid character in the map!", 2);
	else if (iden == MISSED_CHAR)
		ft_putendl_fd("Missed character in the map!", 2);
	else if (iden == MISSED_WALL)
		ft_putendl_fd("Map not surrounded by walls!", 2);
	else if (iden == INVALID_EXTENSION)
		ft_putendl_fd("Invalid map extension (.ber)!", 2);
	else if (iden == EMPTY_MAP)
		ft_putendl_fd("empty_map!", 2);
	else if (iden == INVALID_N_ARGS)
		ft_putendl_fd("Invalid number of arguments!", 2);
	else if (iden == INVALID_SHAPE)
		ft_putendl_fd("Map not rectangular!", 2);
	else if (iden == ALLOC_ERROR)
		ft_putendl_fd("Memory error has been detected!", 2);
	if (par->map != NULL)
		free_map(par->map);
	exit(0);
}

int	check_char(char one_par[0][4], char c)
{
	int		i;
	char	set[6];

	i = 0;
	ft_strlcpy(set, "10ECP\0", 6);
	while (set[i])
	{
		if (set[i] == c)
		{
			if (c == 'P')
				one_par[0][0] = one_par[0][0] + 1;
			else if (c == 'E')
				one_par[0][1] = 1;
			else if (c == 'C')
				one_par[0][2] = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	count_col(t_par *par)
{	
	int		i;
	int		j;
	char	one_par[4];

	ft_bzero(one_par, 4);
	i = 0;
	par->col = 0;
	while (*par->map && par->map[i])
	{
		j = 0;
		while (**par->map && par->map[i][j])
		{		
			if (!check_char(&one_par, par->map[i][j]))
				map_invalid(INVALID_CHAR, par);
			if (par->map[i][j] == 'C')
				(par->col)++;
			j++;
		}
		i++;
	}
	if ((one_par[1] < 1 || one_par[2] < 1 || one_par[0] != 1))
		map_invalid(MISSED_CHAR, par);
}

void	check_map(t_par *par)
{
	int	y;

	y = 0;
	while (par->map[y] && par->map[y][0])
	{
		if (par->map[y][(par->px) - 1] != '1' || par->map[y][0] != '1')
			map_invalid(MISSED_WALL, par);
		y++;
	}
	y = 0;
	while (par->map[0][y])
	{
		if (par->map[0][y] != '1' || par->map[(par->py) - 1][y] != '1')
			map_invalid(MISSED_WALL, par);
		y++;
	}
	y = 0;
	while (par->map[y])
	{
		if (par->map[y][(par->px)] != '\0')
			map_invalid(INVALID_SHAPE, par);
		y++;
	}
}

int	read_map(t_par *par, char *f_map)
{
	char	*hget;
	char	*hol;
	int		fd;

	if (ft_strncmp(".ber", &f_map[ft_strlen(f_map) - 4], 5))
		map_invalid(INVALID_EXTENSION, par);
	fd = open(f_map, O_RDONLY);
	hol = NULL;
	while (1)
	{
		hget = get_next_line(fd);
		if (!hget)
			break ;
		hol = ft_strjoin2(hol, hget);
	}
	close(fd);
	if (!hol)
		map_invalid(EMPTY_MAP, par);
	par->map = ft_split(hol, '\n');
	while (*par->map && par->map[par->py])
		(par->py)++;
	while (*par->map && **par->map && par->map[0][par->px])
		(par->px)++;
	return (free(hol), check_map(par), count_col(par), 0);
}
