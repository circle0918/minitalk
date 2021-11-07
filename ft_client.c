/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:54:59 by yyuan             #+#    #+#             */
/*   Updated: 2021/11/07 20:01:16 by yyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
/*pid_t send_id(pid_t pid)
{
	static s_pid = pid;
	return s_pid;
}
void  client_action(int sig, siginfo_t *siginfo, void *text)
{
	kill(s_pid, SIGUSER1);
}*/
void *ft_kill(int pid, char *arg2)
{
	static char c;
//	kill(pid,SIGUSR1);
	int i = 0;
	c= arg2[0];
	while(i<8)
	{
		int check = c >> i& 1;
//		printf ("check : %d\n", check);
		if(check)   //拿到最低位 c向右移i位与1并。是否是1
		{
		 	kill(pid,SIGUSR1);
//			printf("sent 1\n");
		}
		else
		{kill(pid,SIGUSR2);
//			printf("sent 0\n");
		}	
		i++;
		sleep(1);
	}
}

int main(int ac, char **av)
{
	struct sigaction c_action;
	if(ac != 3||!av[2])
		return (127);
	write(1,"Sent   : ",9);
//	c_action.sigaction = client_action;
//	c_action.flag = SA_SIGINFO;
//	sigaction(SIGUSR1, &c_action, 0);
//	sigaction(SIGUSR2, &c_action, 0);
	ft_putnbr_fd(ft_strlen(av[2]),1);
	write(1, "\n", 1);
// send_bit	
	ft_kill(ft_atoi(av[1]), av[2]);
	while (1)
		pause();
	return (0);
}