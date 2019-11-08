/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_direct_indirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:32:38 by yhetman           #+#    #+#             */
/*   Updated: 2019/10/30 18:38:38 by botkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	find_correct_token(t_assembler *ass, char *name)
{
	int		index;

	index = -1;
	while (++index < ass->count)
		if (!ft_strcmp(ass->tokens[index].name, name))
			return (index);
	return (index);
}

static bool	count_bytes(t_assembler *ass, t_writer *writer,
		char *line, long long *hex)
{
	int		i;
	char	*token;

	i = 0;
	while (line[i] && line[i] != SEPARATOR_CHAR)
		i++;
	if (!(token = ft_strsub(line, 1, i - 1)))
		return (false);
	if ((i = find_correct_token(ass, token)) < 0)
		return (false);
	*hex = ass->tokens[i].byte.first - writer->curr_command;
	free(token);
	return (true);
}

static void	write_direct(t_assembler *ass, t_writer *writer,
					int *cur, char *line)
{
	int				i;
	long long		numb;
	long long		hex;

	i = -1;
	if (line[1] != LABEL_CHAR)
		hex = ass->options[writer->command_index].command_size ?
		ft_atoi(line + 1) % 65536 : ft_atoi(line + 1) % 4294967296;
	else if (!count_bytes(ass, writer, line + 1, &hex))
		return ;
	if (hex < 0)
		hex = ass->options[writer->command_index].command_size ? hex + 65536
			: hex + 4294967296;
	numb = octet(hex);
	if (ass->options[writer->command_index].command_size)
		while (++i < (2 - numb))
			ft_putchar_fd(0, writer->fd);
	else
		while (++i < (4 - numb))
			ft_putchar_fd(0, writer->fd);
	ft_puthex_fd(hex, writer->fd);
	*cur = ass->options[writer->command_index].command_size ?
		(*cur) + 2 : (*cur) + 4;
}

static void	write_indirect(t_assembler *ass, t_writer *writer,
		int *cur, char *line)
{
	long long	hex;

	if (line[0] == LABEL_CHAR && !count_bytes(ass, writer, line, &hex))
		return ;
	else
		hex = ft_atoi(line) % 65536;
	hex = hex < 0 ? hex + 65536 : hex;
	ft_putchar_fd(hex / 256, writer->fd);
	ft_putchar_fd(hex % 256, writer->fd);
	(*cur) += 2;
}

void		write_direct_indirect(t_assembler *ass, t_writer *writer,
		char **buffer, int i)
{
	int		*cur;
	char	*line;

	cur = &(writer->cursor);
	line = buffer[writer->token + 1] + i;
	if (buffer[writer->token + 1][i] == '%')
		write_direct(ass, writer, cur, line);
	else
		write_indirect(ass, writer, cur, line);
}
