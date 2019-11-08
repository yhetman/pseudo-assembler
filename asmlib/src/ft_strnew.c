/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:03:59 by yhetman           #+#    #+#             */
/*   Updated: 2019/10/07 04:14:17 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asmlib.h"

char	*ft_strnew(size_t size)
{
	char	*memory;
	size_t	i;

	i = -1;
	if (!(memory = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (++i < size)
		memory[i] = '\0';
	memory[i] = '\0';
	return (memory);
}
