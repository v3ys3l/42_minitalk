/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbicer <vbicer@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 01:35:19 by vbicer            #+#    #+#             */
/*   Updated: 2024/12/19 12:38:59 by vbicer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int	a;
	int	i;
	int	result;

	i = 0;
	a = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			a *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * a);
}

void	ft_error(char *s)
{
	ft_putstr(s);
	exit(1);
}

void	ft_transfer(char c, int pid)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (i < 8)
	{
		if (c << i & 128)
			check = kill(pid, SIGUSR1);
		else
			check = kill(pid, SIGUSR2);
		i++;
		usleep(2000);
	}
	if (check == -1)
		ft_error("ERROR\n");
}

int	main(int ac, char **av)
{
	int	i;
	int	check;

	i = 0;
	if (ac == 3)
	{
		check = ft_atoi(av[1]);
		if (check == -1)
			ft_error("Invalid PID\n");
		while (av[2][i])
			ft_transfer(av[2][i++], ft_atoi(av[1]));
	}
	else
		ft_error("Error:\nInvalid arguments\n");
	return (0);
}
