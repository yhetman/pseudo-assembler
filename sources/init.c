/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blukasho <bodik1w@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 08:29:20 by blukasho          #+#    #+#             */
/*   Updated: 2019/10/30 18:40:29 by botkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int				octet(long long numb)
{
	int i;

	i = 1;
	while (numb / 256 && i++)
		numb /= 256;
	return (i);
}

t_header		*init_t_header(void)
{
	t_header	*new;

	new = (t_header *)malloc(sizeof(t_header));
	ft_bzero(new, sizeof(t_header));
	return (new);
}

t_assembler		*init_t_assembler(void)
{
	t_assembler	*new;

	new = (t_assembler *)malloc(sizeof(t_assembler));
	ft_bzero(new, sizeof(t_assembler));
	return (new);
}

t_reader		*init_t_reader(void)
{
	t_reader	*new;

	new = (t_reader *)malloc(sizeof(t_reader));
	ft_bzero(new, sizeof(t_reader));
	return (new);
}
