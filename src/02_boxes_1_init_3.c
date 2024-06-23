/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_1_init_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:26:26 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 15:45:52 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*get_rest
*
*   Returns:
*       -1: Error
*       0: Success
*
*/
int	get_rest(t_box **box, t_prompt **prompt)
{
	if (ft_heredocs(box, HEREDOC) == -1 || ft_infiles(box, INFILE) == -1
		|| ft_outfile_append(box, OUTFILE_APPEND) == -1
		|| ft_outfile_strong(box, OUTFILE_STRONG) == -1)
		return (-1);
	if (ft_cmd_args(box, prompt) == -1)
		return (-1);
	return (0);
}

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
	t_box	**arr_boxes;
	int		tmp_nb_boxes;
	int		keep_nb_boxes;
	int		substr_id;
	int		i;

	i = 0;
	tmp_nb_boxes = prompt->nb_of_substr;
	keep_nb_boxes = prompt->nb_of_substr;
	if (DEBUG_MODE != 0)
	{
		printf("     02_boxes.c - ft_gen_boxes| nb_boxes = ");
		printf("%d\n", prompt->nb_of_substr);
	}
	substr_id = 1;
	arr_boxes = malloc(sizeof(t_box) * tmp_nb_boxes);
	while (tmp_nb_boxes > 0)
	{
		if (ft_box_init(&arr_boxes[i], prompt, substr_id) == -1)
			return (-1);
		//init_cmd(&arr_boxes[i], prompt, substr_id);
		tmp_nb_boxes--;
		substr_id++;
		i++;
	}
	//David ejecuta
	// dup2(prompt->tmp_in, 0);
	// dup2(prompt->tmp_out, 1);
	// close(prompt->tmp_out);
	// close(prompt->tmp_in);
	// int status;
	// status = 0;
	// waitpid(prompt->pid, &status, 0);
    // if (WIFEXITED(status))
	// 	status = WEXITSTATUS(status);
	// if (WIFSIGNALED(status))
	// {
	// 	if (WTERMSIG(status) == 2)
	// 		status = 130;
	// 	else if ((WTERMSIG(status) == 3))
	// 		status = 131;
	// }
    // prompt->pipefd[0] = 0;
    // prompt->pipefd[1] = 1;
	
	//Liberamos
	i = 0;
	while (arr_boxes[i] && keep_nb_boxes > 0)
	{
		ft_free_box(arr_boxes[i]);
		free(arr_boxes[i]);
		arr_boxes[i] = NULL;
		i++;
		keep_nb_boxes--;
	}
	free(arr_boxes);
	return (0);
}
