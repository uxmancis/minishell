/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 03:19:28 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/23 15:05:31 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit_builtin(t_box *box, t_prompt *prompt, int status)
{
	int	i;

	(void)prompt;
	i = 0;
	// Free dynamically allocated memory in box
	if (box)
	{
		if (box->rest_info_potential_cmd)
			free(box->rest_info_potential_cmd);
		if (box->words_hrdc)
			free(box->words_hrdc);
		if (box->words_infile)
			free(box->words_infile);
		if (box->words_outfile_append)
			free(box->words_outfile_append);
		if (box->words_outfile_strong)
			free(box->words_outfile_strong);
		if (box->pids)
			free(box->pids);
		if (box->cmd_options)
			free(box->cmd_options);
		if (box->cmd_path)
			free(box->cmd_path);
		if (box->envp)
		{
			while (box->envp[i])
			{
				free(box->envp[i]);
				i++;
			}
			free(box->envp);
		}
		free(box);
	}
	exit(status);
}



