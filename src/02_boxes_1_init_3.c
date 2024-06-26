/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_1_init_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:26:26 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 20:54:46 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_exec(t_prompt *prompt)
{
	int	status;

	dup2(prompt->tmp_in, 0);
	dup2(prompt->tmp_out, 1);
	close(prompt->tmp_out);
	close(prompt->tmp_in);
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
	prompt->arr_boxes = NULL;
}

void	ft_gen_boxes_2(t_prompt *prompt)
{
	prompt->tmp_in = dup(STDIN_FILENO);
	prompt->tmp_out = dup(STDOUT_FILENO);
	prompt->pid = 0;
	prompt->pipefd[0] = 0;
	prompt->pipefd[1] = 1;
	prompt->arr_boxes = ft_calloc(prompt->nb_of_substr + 1, sizeof(t_box *));
	prompt->arr_boxes[prompt->nb_of_substr] = NULL;
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
	int		tmp_nb_boxes;
	int		i;

	i = 0;
	tmp_nb_boxes = prompt->nb_of_substr;
	if (DEBUG_MODE != 0)
	{
		printf("     02_boxes.c - ft_gen_boxes| nb_boxes = ");
		printf("%d\n", prompt->nb_of_substr);
	}
	ft_gen_boxes_2(prompt);
	while (i < tmp_nb_boxes)
	{
		if (ft_box_init(&prompt->arr_boxes[i], prompt, i + 1) == -1)
			return (-1);
		init_cmd(&prompt->arr_boxes[i], prompt, i + 1);
		i++;
	}
	ft_exec(prompt);
	return (0);
}

void	ft_free_char(char **words, int nb_of_words)
{
	int	x;

	if (words != NULL)
	{
		x = 0;
		while (x < nb_of_words)
		{
			free(words[x]);
			x++;
		}
		free (words);
		words = NULL;
	}
}

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
