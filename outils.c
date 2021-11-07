/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:13:22 by yyuan             #+#    #+#             */
/*   Updated: 2021/11/07 16:28:11 by yyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
void	ft_putnbr_fd(int n, int fd)
{
	unsigned	int	nb;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb = n * (-1);
	}
	else
		nb = n;
	if (nb > 9)
		ft_putnbr_fd((nb / 10), fd);
	ft_putchar_fd(((nb % 10) + '0'), fd);
}

int ft_strlen(char *str)
{
	int l;

	l = 0;
	while(str[l]!='\0')
		l++;
	return (l);
}

static int	ft_is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' ||
			c == '\v' || c == '\f' || c == '\r');
}

static	int	return_res(const char *s, int neg, long int res)
{
	int count;

	count = 0;
	while (s[count] && s[count] >= '0' && s[count] <= '9')
	{
		count++;
	}
	if (count >= 20 && neg == 1)
		return (-1);
	else if (count >= 20 && neg == -1)
		return (0);
	else
		return (neg * res);
}

int			ft_atoi(const char *str)
{
	long	int		res;
	int				neg;
	const	char	*s;

	neg = 1;
	res = 0;
	while (ft_is_space(*str) == 1)
		str++;
	if (*str == '-')
	{
		neg = -1;
		str++;
		if (*str < '0' || *str > '9')
			return (0);
	}
	if (*str == '+')
		str++;
	s = str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return (int)(return_res(s, neg, res));
}
