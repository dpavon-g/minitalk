/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:04:50 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/09/01 10:32:16 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk.h"

int	g_counter = 1;

int	complete_str(char **str, int counter, char letter)
{
	int		i;
	char	*aux;

	aux = ft_strdup(*str);
	free(*str);
	*str = malloc(sizeof(char) * counter + 2);
	i = 0;
	while (aux[i])
	{
		(*str)[i] = aux[i];
		i++;
	}
	free(aux);
	(*str)[i++] = letter;
	(*str)[i] = '\0';
	return (1);
}

int	reserve_string(char letter)
{
	static int	counter = 0;
	static char	*str;

	if (letter == '\0')
	{
		counter = 0;
		ft_printf("%s\n", str);
		free(str);
		str = NULL;
		return (0);
	}
	if (!str)
	{	
		counter = 2;
		str = malloc(sizeof(char) * counter);
		str[0] = letter;
		str[1] = '\0';
	}
	else
		complete_str(&str, ++counter, letter);
	return (0);
}

void	sender_pid(int sig, siginfo_t *info, void *context)
{
	static int	final;
	int			pid;

	pid = info->si_pid;
	(void)context;
	if (g_counter == 1)
		final = 0;
	if (sig == SIGUSR1)
		final += 1 << (8 - g_counter++);
	else if (sig == SIGUSR2)
		final += 0 << (8 - g_counter++);
	if (g_counter == 9)
	{
		reserve_string(final);
		final = 0;
		g_counter = 1;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("The server PID is: %d\n", getpid());
	sa.sa_sigaction = sender_pid;
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
