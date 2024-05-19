/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:39:46 by dbonilla          #+#    #+#             */
/*   Updated: 2024/05/17 00:11:16 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int handle_sigint(int sig) 
// {
//     // Liberar la memoria aquí
//     // free_memory();

//     // Manejar SIGINT (Ctrl-C)
//     write(1, "\nCaught signal Ctrl-C\n", 22);
//     exit(0);

//     return (0);
// }

// int handle_eof(int sig) 
// {
//     // Liberar la memoria aquí
//     // free_memory();

//     // Manejar EOF (Ctrl-D)
//     write(1, "\nCaught EOF signal Ctrl-D\n", 26);
//     exit(0);

//     return (0);
// }

// int handle_sigquit(int sig) 
// {
//     // Liberar la memoria aquí
//     // free_memory();

//     // Manejar SIGQUIT (Ctrl-\)
//     write(1, "\nCaught signal Ctrl-\\\n", 22);
//     exit(0);

//     return (0);
// }

// void	ft_signal_handler(void (*handler)(int signum, siginfo_t *info, void *context))
// {
// 	struct sigaction	sa;

// 	memset(&sa, 0, sizeof(sa));
// 	sa.sa_flags = SA_SIGINFO;
// 	sa.sa_sigaction = handler;
// 	if (sigaction(SIGINT, &sa, NULL) == -1)
// 		write(1, "Error\n", 6);
// 	if (handler == ft_parent_signals)
// 	{
// 		if (sigaction(SIGQUIT, &sa, NULL) == -1)
// 			write(1, "Error\n", 6);
// 	}
// }