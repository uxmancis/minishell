/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_setup_redirects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:29:16 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 20:10:45 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	process_infile(t_box **box, int index_red)
{
	if (handle_input_infile(box, index_red) == -1)
		return (-1);
	free(*(*box)->words_infile);
	*(*box)->words_infile = NULL;
	(*box)->words_infile++;
	return (0);
}

int	process_outfile_strong(t_box **box, int index_red)
{
	if (handle_output_strong(box, index_red) == -1)
		return (-1);
	free(*(*box)->words_outfile_strong);
	*(*box)->words_outfile_strong = NULL;
	(*box)->words_outfile_strong++;
	return (0);
}

int	process_heredoc(t_box **box)
{
	if (handle_heredoc(box) == -1)
		return (-1);
	free(*(*box)->words_hrdc);
	*(*box)->words_hrdc = NULL;
	(*box)->words_hrdc++;
	return (0);
}

int	process_outfile_append(t_box **box, int index_red)
{
	if (handle_output_append(box, index_red) == -1)
		return (-1);
	free(*(*box)->words_outfile_append);
	*(*box)->words_outfile_append = NULL;
	(*box)->words_outfile_append++;
	return (0);
}

void	restore_original_pointers(t_box **box)
{
	(*box)->words_outfile_append = (*box)->words_outfile_append_tmp;
	(*box)->words_infile = (*box)->words_infile_tmp;
	(*box)->words_hrdc = (*box)->words_hrdc_tmp;
	(*box)->words_outfile_strong = (*box)->words_outfile_strong_tmp;
}

int process_redirect(t_box **box, int index_red)
{
	int redir_type = (*box)->dict_red_index_type[index_red][1];

	if (redir_type == INFILE)
	{
		return process_infile(box, index_red);
	}
	else if (redir_type == OUTFILE_STRONG)
	{
		return process_outfile_strong(box, index_red);
	}
	else if (redir_type == HEREDOC)
	{
		int result = process_heredoc(box);
		if (result == 0 && (*box)->nb_of_heredocs > 1)
		{
			return (*box)->nb_of_heredocs - 1;
		}
		return result;
	}
	else if (redir_type == OUTFILE_APPEND)
	{
		return process_outfile_append(box, index_red);
	}
	return 0;
}


int handle_redirects(t_box **box)
{
	int tmp_nb_of_red_type = (*box)->nb_of_redir;
	int index_red = 0;

	while (tmp_nb_of_red_type > 0)
	{
		if (process_redirect(box, index_red) == -1)
			return (-1);

		index_red++;
		tmp_nb_of_red_type--;
	}

	restore_original_pointers(box);

	return (0);
}

