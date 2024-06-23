/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_1_init_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:26:26 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 13:31:38 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exitcode;
/*
*   Generates boxes based on nb_of_substr indicated in prompt
*   structure.
*
*	substr_id: Tells us which substr / which box are we referring to.
*
*	I could also..
*	while (arr_boxes[i])
	{
		ft_free_box(arr_boxes[i]);
		i++;
	}

*/
int	ft_gen_boxes(t_prompt *prompt)
{
	int		tmp_nb_boxes;
	int		i;

	i = 0;
	tmp_nb_boxes = prompt->nb_of_substr;
    if (DEBUG_MODE != 0)
    {
        printf("     02_boxes.c - ft_gen_boxes| nb_boxes = ");
        printf("%d\n", prompt->nb_of_substr);
    }
    prompt->tmp_in = dup(STDIN_FILENO);
    prompt->tmp_out = dup(STDOUT_FILENO);
    prompt->pid = 0;
    prompt->pipefd[0] = 0;
    prompt->pipefd[1] = 1;
	prompt->arr_boxes = (t_box**) malloc((tmp_nb_boxes + 1) * sizeof(t_box *));
    prompt->arr_boxes[tmp_nb_boxes] = NULL;
	while (i < tmp_nb_boxes)
	{
		if (ft_box_init(&prompt->arr_boxes[i], prompt, i + 1) == -1)
			return (-1);
		init_cmd(&prompt->arr_boxes[i], prompt, i + 1);
		i++;
	}
	//David ejecuta
	dup2(prompt->tmp_in, 0);
	dup2(prompt->tmp_out, 1);
	close(prompt->tmp_out);
	close(prompt->tmp_in);
	int status;
	status = 0;
	waitpid(prompt->pid, &status, 0);
    if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			status = 130;
		else if ((WTERMSIG(status) == 3))
			status = 131;
	}
    prompt->pipefd[0] = 0;
    prompt->pipefd[1] = 1;
	i = 0;
	while (prompt->arr_boxes[i] != NULL)
	{
		ft_free_box(prompt->arr_boxes[i]);
		free(prompt->arr_boxes[i]);
		prompt->arr_boxes[i] = NULL;
		i++;
	}
	free(prompt->arr_boxes);
    prompt->arr_boxes = NULL;
	return (0);
}
