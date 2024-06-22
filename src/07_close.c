/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:22:55 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/22 21:17:20 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int close_fdin_fdout(t_box *box)
// {
// 	printf(RED "Closing... fd_in: [%d]\n" RESET_COLOR, box->fd_in);
// 	if (box->fd_in != -1)
// 	{
// 		close(box->fd_in);
// 		// box->fd_in = -1;
// 	}
// 	printf(RED "Closing... fd_out: [%d]\n" RESET_COLOR, box->fd_out);
// 	if (box->fd_out != -1)
// 	{
// 		close(box->fd_out);
// 		// box->fd_out = -1;
// 	}
// 	close_pipefd(box);
// 	return 0;
// }

// int close_pipefd(t_box *box)
// {
// 	int i = 0;
// 	// int nb_cmds = cmd_data->nb_cmds ;

// 	while (i < box->nb_pipes)
// 	{

// 		printf(RED "\n            Closing pipefd [%d] WRITE[1]: [%d] READ[0]: [%d]\n" RESET_COLOR, i, box->pipefd[i][1], box->pipefd[i][0]);
// 		close(box->pipefd[i][0]);
// 		close(box->pipefd[i][1]);
// 		free(box->pipefd[i]);

// 		i++;
// 	}
// 	return (0);
// }
