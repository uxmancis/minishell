/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:39:46 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/23 21:35:35 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_signals(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		printf("\nSeñal desconocida recibida\n");
	}
}

void	ft_suppress_output(int quit)
{
	struct termios	config;

	ft_bzero(&config, sizeof(config));
	tcgetattr(STDIN_FILENO, &config);
	if (quit == 0)
		config.c_lflag &= ~ECHOCTL;
	else
		config.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &config);
}

void	ft_signal_handler(void)
{
	ft_suppress_output(0);
	signal(SIGINT, ft_signals);
	signal(SIGQUIT, ft_signals);
	signal(SIGTERM, ft_signals);
}

void	handle_eof(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
}
