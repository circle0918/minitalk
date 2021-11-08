/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:54:59 by yyuan             #+#    #+#             */
/*   Updated: 2021/11/08 01:31:43 by yyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_kill(int pid, char c);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);

int	ft_strlen(char *str)
{
	int	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}

void	ft_while(int pid, char *str)
{
	char	c;
	int		j;

	j = 0;
	while (str[j] != '\0')
	{
		c = str[j];
		ft_kill(pid, c);
		j++;
	}
}

void	ft_kill(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(50);
	}
}

int	main(int ac, char **av)
{
	if (ac != 3 || !av[2])
		return (127);
	write(1, "Sent   : ", 9);
	ft_putnbr_fd(ft_strlen(av[2]), 1);
	write(1, "\n", 1);
	ft_while(ft_atoi(av[1]), av[2]);
	return (0);
}
