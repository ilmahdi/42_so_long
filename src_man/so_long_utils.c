/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:58:24 by eabdelha          #+#    #+#             */
/*   Updated: 2021/12/28 10:56:27 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = -1;
	while (map && map[++i])
		free(map[i]);
	free(map);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	hol[2];
	char	hhol[10000];
	int		i;
	int		rt;

	i = 0;
	while (1)
	{
		rt = read(fd, hol, 1);
		if (rt <= 0)
			break ;
		hol[1] = '\0';
		hhol[i] = hol[0];
		i++;
		hhol[i] = '\0';
		if (hol[0] == '\n' || hol[0] == '\0')
			break ;
	}
	if (i == 0 || rt == -1)
		return (NULL);
	line = (char *)ft_calloc((size_t)(i + 1), sizeof(char));
	if (!line)
		return (NULL);
	return (ft_strlcpy(line, hhol, (ft_strlen(hhol)) + 1), line);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	j = 0;
	if (s1 != NULL)
		j = ft_strlen(s1);
	s = (char *)malloc((size_t)(j + ft_strlen(s2) + 1));
	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 != NULL && s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
		s[i++] = s2[j++];
	s[i] = '\0';
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	return (s);
}
