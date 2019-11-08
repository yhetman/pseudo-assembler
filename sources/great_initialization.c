/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   great_initialization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 20:49:16 by yhetman           #+#    #+#             */
/*   Updated: 2019/10/30 21:49:44 by botkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	miss_trash(int *i, char *line)
{
	int		j;

	j = 0;
	while (line[*i] && line[*i] != COMMENT_CHAR
			&& (IS_TABUL(line[*i])))
		(*i)++;
	while (line[*i + j] && line[*i + j] != COMMENT_CHAR
			&& !(IS_TABUL(line[*i + j])))
	{
		if (line[*i + j] == SEPARATOR_CHAR)
		{
			j++;
			while (line[*i + j] && line[*i + j] != COMMENT_CHAR
					&& (IS_TABUL(line[*i + j])))
				j++;
		}
		j++;
	}
	return (j);
}

static bool	init_each_word(char **words, char *line, int i, int nb_words)
{
	int		w_nb;
	int		w_len;
	char	*tmp;

	w_nb = 0;
	while (nb_words > 0 && line && line[i] && (w_len = miss_trash(&i, line)))
	{
		while (line[i + w_len] && line[i] == COMMENT_CHAR)
			w_len++;
		if (w_len > 0)
		{
			tmp = ft_strsub(line + i, 0, w_len);
			if (!(words[w_nb] = del_space(tmp)))
			{
				free(tmp);
				return (false);
			}
			--nb_words;
			w_nb++;
			free(tmp);
		}
		i += w_len;
	}
	words[w_nb] = NULL;
	return (true);
}

static bool	init_details(char ***grid, char **lines)
{
	int		words;
	int		i;

	i = -1;
	while (++i < 2)
	{
		if (!(grid[i] = (char**)malloc(sizeof(char*) * 2)))
			return (false);
		if (!(grid[i][0] = ft_strdup(lines[i])))
			return (false);
		grid[i][1] = NULL;
	}
	while (lines[i])
	{
		words = find_words(lines[i]);
		if (!(grid[i] = (char**)malloc(sizeof(char*) * (words + 1))))
			return (false);
		if (!init_each_word(grid[i], lines[i], 0, words))
			return (false);
		i++;
	}
	grid[i] = NULL;
	return (true);
}

static bool	init_command(char **command, int lines, char *file, int i)
{
	int		curr;
	int		str;

	str = -1;
	while (++str < lines && ++i >= 0)
	{
		curr = 0;
		while (file[curr + i] && file[curr + i] != '\n')
			curr++;
		if (!(command[str] = ft_strnew(curr + 1)))
		{
			command[str] = NULL;
			return (false);
		}
		curr = 0;
		while (file[i] && file[i] != '\n')
		{
			command[str][curr] = file[i];
			curr++;
			i++;
		}
		command[str][curr] = '\0';
	}
	command[str] = NULL;
	return (true);
}

int			great_initialization(t_assembler *ass, int lines, char *file)
{
	if (!(ass->command = (char **)malloc(sizeof(char*) * (lines + 1))))
		return (0);
	if (!(init_command(ass->command, lines, file, -1)))
		return (great_freeing(ass, file));
	if (!(ass->stored = (char ***)malloc(sizeof(char**) * (lines + 1))))
		return (0);
	if (!(init_details(ass->stored, ass->command)))
		return (great_freeing(ass, file));
	return (1);
}
