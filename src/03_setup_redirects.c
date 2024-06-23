/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_setup_redirects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:29:16 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 20:38:48 by dbonilla         ###   ########.fr       */
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
