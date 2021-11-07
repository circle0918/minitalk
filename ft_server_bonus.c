/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:40:42 by yyuan             #+#    #+#             */
/*   Updated: 2021/11/07 23:31:07 by yyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <signal.h>
void  server_action(int sig, siginfo_t *siginfo, void *text)
{
//	if(sig == SIGUSR1);
//		write(1,"hello\n",6);
	static unsigned char c = 0;
	static int i = 0;
	static pid_t client_pid = 0;

//	printf("sig : %d\n",sig);
//	printf("i : %d\n",i);
	if (i!= 8)
	{
		if(sig == SIGUSR1)
		{
			 c |= 1<<i;
//			printf("1 in : %d\n",c);
		}
		else if (sig == SIGUSR2)
		{
		//	c |= 0<<i;
//			printf("0 in : %d\n",c);
		}
		i++;
	}
	if(i == 8)
	{	
		i = 0;
		
		client_pid = siginfo->si_pid;
//		printf("client in server : %d\n", client_pid);
		if (c == '\0')
   		{
			kill(client_pid, SIGUSR2);
			//printf("to client sig2\n");
			client_pid = 0;
			return ;
		} //only take care of last '\0', no need to print

		write(1,&c,1);
		c = 0;
   		kill(client_pid, SIGUSR1);
//		printf("to client sig1\n");
	}	
}
int main(void)
{
	struct sigaction	s_action;
//sigaction
	write(1,"Server PID: ",12);
	ft_putnbr_fd(getpid(),1);
	write(1,"\n",1);
	s_action.sa_sigaction = server_action;	
	s_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_action, 0);
	sigaction(SIGUSR2, &s_action, 0);
	while (1)
		pause();
	return (0);
}
