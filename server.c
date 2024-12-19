/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbicer <vbicer@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 02:09:28 by vbicer            #+#    #+#             */
/*   Updated: 2024/12/19 08:27:19 by vbicer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	ft_putnbr(int n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

void	server(int signal)
{
	static char	c;
	static int	i;

	if (signal == SIGUSR1)
		c = c << 1 | 1;
	else
		c = c << 1;
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	write(1, "Server PID:", 11);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, server);
	signal(SIGUSR2, server);
	while (1)
		pause();
	return (0);
}
