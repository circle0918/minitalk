/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:54:59 by yyuan             #+#    #+#             */
/*   Updated: 2021/11/07 23:30:32 by yyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
void ft_kill(int pid, unsigned char c);

void  client_action(int sig, siginfo_t *siginfo, void *text)
{
	static int count = 0;

	if(sig == SIGUSR1)
		count++;
	else if(sig == SIGUSR2)
	{
		write(1,"Received ",9);
		ft_putnbr_fd(count,1);
		write(1,"\n",1);
		count = 0;
		exit(0);
	}

}

void ft_while(int pid, char *str)
{
	unsigned char c;
	int j = 0;
//	int len;

//	len = ft_strlen(str[j])+1;
	
	while (str[j])
	{
		c= str[j];
		ft_kill(pid, c);
		j++;
	}
	ft_kill(pid, '\0');
}

void ft_kill(int pid, unsigned char c)
{
	int i;
//printf("c:   %c\n",c);
  	i = 0;
  	while(i<8)
  	{
  		int check = c >> i& 1;
//printf ("check : %d\n", check);
  		if(check)   //拿到最低位 c向右移i位与1并。是否是1
  		{
   			kill(pid,SIGUSR1);
//		printf("sent 1\n");
  		}
  		else
  		{
  			kill(pid,SIGUSR2);
//	printf("sent 0\n");
  		}	
  		i++;
  		usleep(100);
  	}
}

int main(int ac, char **av)
{
	struct sigaction c_action;
	if(ac != 3||!av[2])
		return (127);
	write(1,"Sent   : ",9);
	c_action.sa_sigaction = client_action;
	c_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &c_action, 0);
	sigaction(SIGUSR2, &c_action, 0);
	ft_putnbr_fd(ft_strlen(av[2]),1);
	write(1, "\n", 1);
	ft_while(ft_atoi(av[1]), av[2]);
	while (1)
		pause();
	return (0);
}
