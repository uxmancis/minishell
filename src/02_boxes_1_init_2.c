/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_1_init_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:24:59 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 15:34:49 by dbonilla         ###   ########.fr       */
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
	ft_free_char(box->words_hrdc, box->nb_of_heredocs);
	ft_free_char(box->words_infile, box->nb_of_infile);
	ft_free_char(box->words_outfile_append, box->nb_of_outfile_append);
	ft_free_char(box->words_outfile_strong, box->nb_of_outfile_strong);
	if (box->what_to_take)
		free(box->what_to_take);
	if (box->index_beginning_words_rest)
		free(box->index_beginning_words_rest);
	ft_free_char(box->rest_info_potential_cmd, box->nb_of_words_rest);
	if (box->tmp_pid_str)
		free(box->tmp_pid_str);
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
	// COMANDS
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
	int	len;
	int	i;

	*box = (t_box *)malloc(sizeof(t_box));
	printf(BLUE"\n\n\n======ִֶָ𓂃 ࣪˖ ִֶָ🐇་༘࿐====ᯓ★_⋆˚࿔ 📦BOX NB: %d 𝜗𝜚˚⋆========𓇼🐚☾☼🦪========;༊;༊__\n"RESET_COLOR, substr_id);
	printf("     02_boxes.c - "BLUE"ft_boxes_init"RESET_COLOR": Boxes are generated here. Nb_of_substr to be created = "BLUE"%d"RESET_COLOR". Let's start!\n", prompt->nb_of_substr);
	ft_boxes_initialize(box);
	if (prompt->nb_of_substr == 1)
		get_single_str(prompt, box);
	else
		generate_substr(prompt, substr_id, box);
	len = ft_strlen((*box)->input_substr);
	i = 0;
	while (len > 0)
	{
		printf("               input_substr[%d] = %c\n", i, (*box)->input_substr[i]);
		i++;
		len--;
	}
	printf("     02_boxes.c - ft_boxes_init| Copied!✅"BLUE" input_substr"RESET_COLOR" generated:"GREEN" %s"RESET_COLOR", len = %d\n", (*box)->input_substr, (int)ft_strlen((*box)->input_substr));
	if (get_dict_quotes(box) == -1)
		return (-1);
	printf("     02_boxes.c - ft_boxes_init|"BLUE" dict_quotes"RESET_COLOR" generated✅\n");
	if (get_redirections(box) == -1)
		return (-1);
	if (get_rest(box, &prompt) == -1)
		return (-1);
	printf("\n\n//pdte.: recopilar info de comandos, argumentos\n");
	printf(BLUE"BOX GENERATION COMPLETED✅, box number = %d\n"RESET_COLOR, substr_id);
	printf(BLUE"==============================================================================\n\n\n"RESET_COLOR);
	return (0);
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
