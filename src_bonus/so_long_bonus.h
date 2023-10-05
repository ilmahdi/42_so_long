/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 11:24:02 by eabdelha          #+#    #+#             */
/*   Updated: 2021/12/27 11:24:06 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

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
# define ENMEY_IMG "../img/e8.xpm"

# define W_NAME "so_long"
# define WON "YOU WON !! Press SPACE key to restart."
# define LOSS "GAME OVER !! Press SPACE key to restart."
# define COLR 0x0000FF

# define INVALID_CHAR 1
# define MISSED_CHAR 2
# define MISSED_WALL 3
# define INVALID_EXTENSION 4
# define EMPTY_MAP 5
# define INVALID_N_ARGS 6
# define INVALID_SHAPE 7
# define ALLOC_ERROR 8

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

typedef struct s_enm
{
	int	xl;
	int	xr;
	int	yu;
	int	yd;
	int	pos;
	int	*arr;
	int	l;
}	t_enm;

typedef struct s_stp
{
	int	stx;
	int	sty;
	int	x;
	int	y;
	int	rep;
}	t_stp;

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
int		*alloc_verify(t_par *par, int size);
void	free_map(char **map);
void	map_invalid(int iden, t_par *par);
char	*ft_strjoin2(char *s1, char *s2);
int		read_map(t_par *par, char *f_map);
void	display(t_par *par);
void	clear_win(t_par *par);
void	count_col(t_par *par);
void	put_img(t_par *par, char *img, int x, int y);
int		game_end(int keycode, t_par *par);
int		move(int keycode, t_par *par);
void	move_plyr(t_par *par, int dirV, int dirH);
void	move_down(t_par *par);
void	move_r(t_par *par);
void	move_l(t_par *par);

void	enemy_rand_pos(t_par *par, int*x, int *y, int pass);
void	count_prob(t_par *par, t_enm *enm, t_stp *stp);
void	get_steps(t_enm *enm, t_stp *stp);
void	increment_move(t_enm *enm, t_stp *stp, t_par *par);

#endif
