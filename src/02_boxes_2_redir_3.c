/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_2_redir_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:16:44 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 21:45:48 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_red_less_than_2(t_box **box, int *i, int index_of_arr)
{
	if (((*box)->input_substr[(*i) + 2] == '<'
			&& (*box)->dict_quotes[(*i) + 2] == 0)
		|| ((*box)->input_substr[(*i) + 2] == '>'
			&& (*box)->dict_quotes[(*i) + 2] == 0))
	{
		ft_puterror("syntax error near unexpected token `newline'\n");
		return (-1);
	}
	if ((*box)->dict_quotes[(*i)] == 0)
	{
		(*box)->dictred_i_t[index_of_arr][0] = (*i);
		(*box)->dictred_i_t[index_of_arr][1] = HEREDOC;
		(*i) = (*i) + 1;
		return (0);
	}
	else
		return (-1);
}

int	set_red_less_than_3(t_box **box, int *i, int index_of_arr)
{
	if ((*box)->dict_quotes[(*i)] == 0)
	{
		(*box)->dictred_i_t[index_of_arr][0] = (*i);
		(*box)->dictred_i_t[index_of_arr][1] = INFILE;
		return (0);
	}
	else
		return (-1);
}

/*  set_red_less_than
 *       Returns:
 *           0: Success - Redirection was assigned
 *           -1: Redirection was finally NOT assigned (inside quotes)
 *
 * 	Additional explanatory comments:
 *		// INDEX of heredoc
 * 		(*box)->dict_red_index_type[index_of_arr][0] = (*i);
 * 
 * 		//TYPE of redir
 * 		(*box)->dict_red_index_type[index_of_arr][1] = HEREDOC;
 * 
 * 		//When double redir was assigned
 * 		(*i) = (*i) + 1;
 */
int	set_red_less_than(t_box **box, int *i, int index_of_arr)
{
	if ((*box)->input_substr[(*i)] != '<' && (*box)->dict_quotes[(*i)] == 0)
		return (EXIT_FAILURE);
	else if ((*box)->input_substr[(*i)] == '<'
		&& (*box)->dict_quotes[(*i)] == 0)
	{
		if ((*box)->input_substr[(*i) + 1] == '<'
			&& (*box)->dict_quotes[(*i) + 1] == 0)
			set_red_less_than_2(box, i, index_of_arr);
		else if ((*box)->input_substr[(*i) + 1] == '>'
			&& (*box)->dict_quotes[(*i) + 1] == 0)
		{
			ft_puterror("syntax error near unexpected token `newline'\n");
			return (-1);
		}
		else
			set_red_less_than_3(box, i, index_of_arr);
	}
	put_parsing_box_numof_redir_4(box, index_of_arr);
	return (0);
}

int	set_red_greater_than_2(t_box **box, int *i, int index_of_arr)
{
	if (((*box)->input_substr[(*i) + 2] == '<'
			&& (*box)->dict_quotes[(*i) + 2] == 0)
		|| ((*box)->input_substr[(*i) + 2] == '>'
			&& (*box)->dict_quotes[(*i) + 2] == 0))
	{
		ft_puterror("syntax error near unexpected token `newline'\n");
		return (-1);
	}
	if ((*box)->dict_quotes[(*i)] == 0)
	{
		(*box)->dictred_i_t[index_of_arr][0] = (*i);
		(*box)->dictred_i_t[index_of_arr][1] = OUTFILE_APPEND;
		(*i) = (*i) + 1;
		return (0);
	}
	else
		return (-1);
}

int	set_red_greater_than_3(t_box **box, int *i, int index_of_arr)
{
	if ((*box)->dict_quotes[(*i)] == 0)
	{
		(*box)->dictred_i_t[index_of_arr][0] = (*i);
		(*box)->dictred_i_t[index_of_arr][1] = OUTFILE_STRONG;
		return (0);
	}
	else
		return (-1);
}
