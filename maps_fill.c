/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:13:14 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/10/21 12:25:52 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_chars(char **chars)
{
	int	i;

	i = -1;
	if (!chars)
		return ;
	while (chars[++i])
		free_t(chars[i]);
	free_t(chars);
}

char	**add_str(char **old, char *new)
{
	char	**ret;
	int		size;
	int		i;

	i = 0;
	if (!old)
		size = 0;
	else
	{
		while (old[i])
			i++;
		size = i;
	}
	i = 0;
	ret = (char **)malloc_t(sizeof(char *) * (size + 2));
	if (!ret)
		return (free_chars(old), free_t(new), NULL);
	while (old && old[i])
	{
		ret[i] = old[i];
		i++;
	}
	ret[i] = new;
	ret[++i] = NULL;
	return (free_t(old), ret);
}

char	**extract_chars(int fd)
{
	char	*line;
	char	**ret;

	ret = NULL;
	line = get_next_line(fd);
	while (line && !ft_strcmp(line, "\n"))
	{
		free_t(line);
		line = get_next_line(fd);
	}
	if (!line)
		return (NULL);
	while (line && ft_strcmp(line, "\n"))
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		ret = add_str(ret, line);
		if (!ret)
			return (NULL);
		line = get_next_line(fd);
	}
	if (line)
		free_t(line);
	return (ret);
}

int	extract_grid(t_cub *map, int fd)
{
	char	**str;

	str = extract_chars(fd);
	if (!str || player_check(str) < 0)
	{
		err("Wrong Player count or map.\n");
		exit(-1);
	}
	map->map = build_plane(str, 0, 0);
	if (!map->map)
		return (free_chars(str), -1);
	if (extract_grid2(map, str) < 0)
	{
		free_chars(str);
		return (-1);
	}
	return (0);
}

int	extract_grid2(t_cub *map, char **str)
{
	int	x;
	int	y;

	x = -1;
	while (++x < map->map->heigth)
	{
		y = -1;
		while (++y < map->map->width && y < (int)ft_strlen(str[x]))
		{
			if (str[x][y] == '1')
				map->map->grid[y][x] = map->wall;
			else if (str[x][y] == 'N' || str[x][y] == 'E'
					|| str[x][y] == 'S' || str[x][y] == 'W')
			{
				init_player(map, x, y, str[x][y]);
				if (copy_map(str, x, y) < 1)
					exit(-1);
			}
		}
	}
	return (0);
}
