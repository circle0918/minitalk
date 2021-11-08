/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:40:42 by yyuan             #+#    #+#             */
/*   Updated: 2021/11/08 01:15:41 by yyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <signal.h>

void	ft_putnbr_fd(int n, int fd);

void	server_action(int sig, siginfo_t *siginfo, void *text)
{
	static unsigned char	c = 0;
	static int				i = 0;
	static pid_t			client_pid = 0;

	(void) (text);
	if (i != 8)
	{
		if (sig == SIGUSR1)
			c |= 1 << i;
		i++;
	}
	if (i == 8)
	{
		i = 0;
		client_pid = siginfo->si_pid;
		if (c == '\0')
		{
			kill(client_pid, SIGUSR2);
			client_pid = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
		kill(client_pid, SIGUSR1);
	}	
}

int	main(void)
{
	struct sigaction	s_action;

	write(1, "Server PID: ", 12);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	s_action.sa_sigaction = server_action;
	s_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_action, 0);
	sigaction(SIGUSR2, &s_action, 0);
	while (1)
		pause();
	return (0);
}
