/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:17:24 by eabdelha          #+#    #+#             */
/*   Updated: 2021/12/28 11:53:18 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "mlx.h"

# define GROUND_IMG "../img/sol.xpm"
# define R_PLAYER_IMG "../img/birdr.xpm"
# define L_PLAYER_IMG "../img/birdl.xpm"
# define WALL_IMG "../img/w.xpm"
# define COLLECT_IMG "../img/xw.xpm"
# define EXIT_IMG "../img/exit2.xpm"

# define WON "YOU WON !! Press SPACE key to restart."
# define COLR 0x0000EF

# define INVALID_CHAR 1
# define MISSED_CHAR 2
# define MISSED_WALL 3
# define INVALID_EXTENSION 4
# define EMPTY_MAP 5
# define INVALID_N_ARGS 6
# define INVALID_SHAPE 7

# define LEFT_STEP -1
# define RIGHT_STEP 1
# define UP_STEP -1
# define DOWN_STEP 1
# define ZERO_MOVE 0

# define LEFT_KEY 0
# define RIGHT_KEY 2
# define UP_KEY 13
# define DOWN_KEY 1
# define ESC_KEY 53

# define FACTOR 42
# define NAME_W "so_long"

typedef struct s_par
{
	char	**map;
	char	*arg;
	int		px;
	int		py;
	void	*win;
	void	*mlx;
	int		col;
	int		n_move;
	int		msg_px;
	int		msg_py;
}	t_par;

int		close_win(t_par *par);
char	*get_next_line(int fd);
void	free_map(char **map);
void	map_invalid(int iden, t_par *par);
char	*ft_strjoin2(char *s1, char *s2);
int		read_map(t_par *par, char *f_map);
void	display(t_par *par);
void	count_col(t_par *par);
void	put_img(t_par *par, char *img, int x, int y);
int		move(int keycode, t_par *par);
void	move_plyr(t_par *par, int V, int H);
void	move_down(t_par *par);
void	move_r(t_par *par);
void	move_l(t_par *par);

#endif
