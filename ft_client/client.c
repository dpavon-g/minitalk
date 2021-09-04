/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:10:07 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/08/31 21:03:39 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk.h"

void	take_bits(char character, char **str)
{
	int	ascii;
	int	counter;

	counter = 0;
	ascii = character;
	while (ascii)
	{
		if ((ascii % 2) == 1)
			str[0][counter] = '1';
		else if ((ascii % 2) == 0)
			str[0][counter] = '0';
		ascii /= 2;
		counter++;
	}
	while (counter < 8)
	{
		str[0][counter] = '0';
		counter++;
	}
}

void	send_bits(char	*str, int pid)
{
	char	*byte;
	int		i;
	int		k;

	k = 0;
	i = 7;
	while (str[k])
	{
		byte = malloc(sizeof(char) * 9);
		byte[8] = '\0';
		take_bits(str[k], &byte);
		while (i >= 0)
		{
			if (byte[i] == '0')
				kill(pid, SIGUSR2);
			else if (byte[i] == '1')
				kill(pid, SIGUSR1);
			i--;
			usleep(150);
		}
		i = 7;
		k++;
		free(byte);
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	int		i;

	i = 7;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		send_bits(argv[2], pid);
		i = 0;
		while (i < 8)
		{
			kill(pid, SIGUSR2);
			usleep(150);
			i++;
		}
	}
	return (0);
}
