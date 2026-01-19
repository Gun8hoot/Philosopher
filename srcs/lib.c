/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:16:32 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/07 01:30:53 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (!nptr || !nptr[0])
		return (0);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res);
}

int	ft_atol(char *number)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	while (number[i] == '+' || number[i] == '-')
		i++;
	while (number[i])
	{
		nb = nb * 10 + (number[i] - '0');
		i++;
	}
	return (nb);
}
