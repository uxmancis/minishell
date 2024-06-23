/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:29:16 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 20:05:17 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	close_files(t_box *box)
{
	if (box->close_in > 1 && box->fd_in != -1)
	{
		if (dup2(box->fd_in, STDIN_FILENO) == -1)
		{
			return (-1);
		}
		close(box->fd_in);
	}
	if (box->close_out > 1 && box->fd_out != -1)
	{
		if (dup2(box->fd_out, STDOUT_FILENO) == -1)
		{
			return (-1);
		}
		close(box->fd_out);
	}
	return (0);
}

int	handle_input_infile(t_box **box, int index_red)
{
	int	i;

	i = 0;
	if ((*box)->dict_red_index_type[index_red][0] == OUTFILE_APPEND
		|| (*box)->dict_red_index_type[index_red][0] == OUTFILE_APPEND
		|| (*box)->dict_red_index_type[index_red][0] == NO_REDIRECTION)
		return (-1);
	if ((*box)->words_infile[i] != NULL
		&& (*box)->dict_red_index_type[index_red][1] == INFILE)
	{
		if (ft_strlen((*box)->words_infile[i]) >= MAX_FILENAME_LENGTH)
			return (-1);
		(*box)->fd_in = open((*box)->words_infile[i], O_RDONLY);
		if ((*box)->fd_in == -1)
		{
			close((*box)->fd_in);
			return (-1);
		}
		if (read((*box)->fd_in, NULL, 0) == -1)
		{
			perror(RED "Error al leer el archivo" RESET_COLOR);
			close((*box)->fd_in);
		}
	}
	else
		return (-1);
	(*box)->close_in = 1;
	return (0);
}

int	handle_output_append(t_box **box, int index_red)
{
	int	index_append;

	index_append = 0;
	if ((*box)->dict_red_index_type[index_red][1] != OUTFILE_APPEND)
		return (-1);
	if ((*box)->words_outfile_append[index_append] != NULL)
	{
		if (ft_strlen((*box)->words_outfile_append[index_append]) >= MAX_FILENAME_LENGTH)
			return (-1);
		if ((*box)->fd_out != -1)
			close((*box)->fd_out);
		(*box)->fd_out = open((*box)->words_outfile_append[index_append],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
		if ((*box)->fd_out == -1)
		{
			perror((*box)->words_outfile_append[index_append]);
			return (-1);
		}
	}
	else
		return (-1);
	(*box)->close_out++;
	return (0);
}

int	handle_output_strong(t_box **box, int index_red)
{
	int	index_strong;

	index_strong = 0;
	if ((*box)->dict_red_index_type[index_red][1] != OUTFILE_STRONG)
		return (-1);
	if ((*box)->words_outfile_strong[index_strong] != NULL)
	{
		if (ft_strlen((*box)->words_outfile_strong[index_strong]) >= MAX_FILENAME_LENGTH)
			return (-1);
		if ((*box)->fd_out != -1)
			close((*box)->fd_out);
		(*box)->fd_out = open((*box)->words_outfile_strong[index_strong],
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if ((*box)->fd_out == -1)
		{
			perror((*box)->words_outfile_strong[index_strong]);
			return (-1);
		}
	}
	else
		return (-1);
	(*box)->close_out++;
	return (0);
}
