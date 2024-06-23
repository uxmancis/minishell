/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_1_init_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:24:59 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 15:49:36 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_int(int **words, int nb_of_words)
{
	int	x;

	if (words != NULL)
	{
		x = 0;
		while (x < nb_of_words)
		{
			if (words[x])
				free(words[x]);
			x++;
		}
		free (words);
	}
}

void	ft_free_box(t_box *box)
{
	if (box->input_substr)
		free(box->input_substr);
	if (box->dict_quotes)
		free(box->dict_quotes);
	ft_free_int(box->dict_red_index_type, box->nb_of_redir);
	ft_free_char(box->words_infile, box->nb_of_infile);
	ft_free_char(box->words_hrdc, box->nb_of_heredocs);
	ft_free_char(box->words_outfile_append, box->nb_of_outfile_append);
	ft_free_char(box->words_outfile_strong, box->nb_of_outfile_strong);
	// free(box->words_outfile_strong);
	// free(box->words_outfile_append);
	// free(box->words_hrdc);
	// free(box->words_infile);
	if (box->what_to_take)
		free(box->what_to_take);
	if (box->index_beginning_words_rest)
		free(box->index_beginning_words_rest);
	ft_free_char(box->rest_info_potential_cmd, box->nb_of_words_rest);
	if (box->tmp_pid_str)
		free(box->tmp_pid_str);
    ft_free_tab(box->envp);
    free(box->pids);
}

void	ft_boxes_initialize_2(t_box **box)
{
	(*box)->is_outfile_strong = 0;
	(*box)->nb_of_outfile_strong = 0;
	(*box)->words_outfile_strong = NULL;
	(*box)->what_to_take = NULL;
	(*box)->nb_of_words_rest = 0;
	(*box)->index_beginning_words_rest = NULL;
	(*box)->rest_info_potential_cmd = NULL;
	(*box)->tmp_pid = -1;
	(*box)->tmp_pid_str = NULL;
    (*box)->close_out = 0;
    (*box)->close_in = 0;
}

void	ft_boxes_initialize(t_box **box)
{
	(*box)->input_substr = NULL;
	(*box)->dict_quotes = NULL;
	(*box)->nb_of_redir = 0;
	(*box)->dict_red_index_type = NULL;
	(*box)->nb_of_heredocs = 0;
	(*box)->words_hrdc = NULL;
	(*box)->words_hrdc_tmp = NULL;
	(*box)->words_infile = NULL;
	(*box)->words_infile_tmp = NULL;
	(*box)->words_outfile_append = NULL;
	(*box)->words_outfile_append_tmp = NULL;
	(*box)->words_outfile_strong = NULL;
	(*box)->words_outfile_strong_tmp = NULL;
	(*box)->is_infile = 0;
	(*box)->nb_of_infile = 0;
	(*box)->words_infile = NULL;
	(*box)->is_outfile_append = 0;
	(*box)->nb_of_outfile_append = 0;
	(*box)->words_outfile_append = NULL;
	(*box)->heredoc = 0;
	(*box)->fd_in = -1;
	(*box)->fd_out = -1;
	(*box)->nb_pipes = 0;
	(*box)->pids = 0;
	(*box)->child = -1;
	(*box)->cmd_options = NULL;
	(*box)->cmd_path = NULL;
	ft_boxes_initialize_2(box);
}

/*  ft_boxes_init, Initializes following variables in 
*   t_box structure:
*       · input_substr: substr (input divided based on splits)
*
*   Returns: 
*       -1: Error
*       0: Success
*/
int	ft_box_init(t_box **box, t_prompt *prompt, int substr_id)
{
	*box = (t_box *)malloc(sizeof(t_box));
	ft_boxes_initialize(box);
	if (prompt->nb_of_substr == 1)
		get_single_str(prompt, box);
	else
		generate_substr(prompt, substr_id, box);
	put_parsing_box_beginning(substr_id, prompt, box);
	if (get_dict_quotes(box) == -1)
		return (-1);
	if (get_redirections(box) == -1)
		return (-1);
	if (get_rest(box, &prompt) == -1)
		return (-1);
	put_parsing_box_end(substr_id);
	return (0);
}
