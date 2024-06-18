/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_6_cmd_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:37:06 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:12 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*  init_what_to_take
*
*   Initializes char *what_to_take variable (box) with
*   'Y' value.
*
*   Y = YES to take as comand/argument.
*/
void	init_what_to_take(t_box **box)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen((*box)->input_substr);
	while (len > 0)
	{
		(*box)->what_to_take[i] = 'Y';
		len--;
		i++;
	}
}

/*mark_redir
*
*	tmp_nb_of_redir = len dict_red_index_type
*
*	· HEREDOC (<<) and OUTFILE_APPEND (>>): 2 'R'-s are assigned.
*	· INFILE (<) and OUTFILE_STRONG (>): 1 single 'R' is assigned.
*/
void	mark_redir(t_box **box)
{
	int	tmp_nb_of_redir;
	int	i;
	int	current_ind_in_substr;

	i = 0;
	tmp_nb_of_redir = (*box)->nb_of_redir;
	while (tmp_nb_of_redir > 0)
	{
		if ((*box)->dict_red_index_type[i][1] == HEREDOC
			|| (*box)->dict_red_index_type[i][1] == OUTFILE_APPEND)
		{
			current_ind_in_substr = (*box)->dict_red_index_type[i][0];
			(*box)->what_to_take[current_ind_in_substr] = 'R';
			(*box)->what_to_take[current_ind_in_substr + 1] = 'R';
		}
		else if ((*box)->dict_red_index_type[i][1] == INFILE
			|| (*box)->dict_red_index_type[i][1] == OUTFILE_STRONG)
		{
			current_ind_in_substr = (*box)->dict_red_index_type[i][0];
			(*box)->what_to_take[current_ind_in_substr] = 'R';
		}
		i++;
		tmp_nb_of_redir--;
	}
}

void	mark_word_2(int start, int end, t_box **box)
{
	int	len_word;

	len_word = 0;
	while (!possible_cases(box, start) && start <= end)
		start++;
	while (possible_cases(box, start) && start <= end)
	{
		(*box)->what_to_take[start] = 'W';
		start++;
		len_word++;
	}
}

/*mark_word
*
*	· HEREDOC (<<) and OUTFILE_APPEND (>>): start: + 2
*	· INFILE (<) and OUTFILE_STRONG (>): start: + 1
*
*	if (is_last_redir_2) //end: ft_strlen (start: según el caso + 1 o + 2)
*	else //end: index next redirección (start: según el caso + 1 o + 2)
*
*	Additional explanatory comments:
*		if last redir: start: posición de redirección (+1 o +2), end: ft_strlen
*		else (still more redirs): start: posición de redirección (+1 o +2), end: posición next redirección
*		{
*			if (red_type == HEREDOC || red_type ?? OUTFILE_APPEND): start + 2
*			if (red_type == INFILE || red_type ?? OUTFILE_STRONG): start + 2
*		}
*		
*/
void	mark_word(t_box **box)
{
	int	tmp_nb_of_redir;
	int	i;

	tmp_nb_of_redir = (*box)->nb_of_redir;
	i = 0;
	while (tmp_nb_of_redir > 0)
	{
		if (is_last_redir_2(box, i))
		{
			if ((*box)->dict_red_index_type[i][1] == HEREDOC
				|| (*box)->dict_red_index_type[i][1] == OUTFILE_APPEND)
				mark_word_2((*box)->dict_red_index_type[i][0] + 2,
					ft_strlen((*box)->input_substr) - 1, box);
			else if (((*box)->dict_red_index_type[i][1] == INFILE
				|| (*box)->dict_red_index_type[i][1] == OUTFILE_STRONG))
				mark_word_2((*box)->dict_red_index_type[i][0] + 1,
					ft_strlen((*box)->input_substr) - 1, box);
			break ;
		}
		else
		{
			if ((*box)->dict_red_index_type[i][1] == HEREDOC
				|| (*box)->dict_red_index_type[i][1] == OUTFILE_APPEND)
				mark_word_2((*box)->dict_red_index_type[i][0] + 2,
					(*box)->dict_red_index_type[i + 1][0] - 1, box);
			else if (((*box)->dict_red_index_type[i][1] == INFILE
				|| (*box)->dict_red_index_type[i][1] == OUTFILE_STRONG))
				mark_word_2((*box)->dict_red_index_type[i][0] + 1,
					(*box)->dict_red_index_type[i + 1][0] - 1, box);   
		}
		tmp_nb_of_redir--;
		i++;
	}
}

/*is_last_redir_2
*
*   Compares nb_of_redirs with nb_redir_x.
*
*   Returns:
*       1: YES is last redirección
*       0: NO still more redirecciones in input_substr
*/
int	is_last_redir_2(t_box **box, int nb_redir_x)
{
	if (nb_redir_x + 1 == (*box)->nb_of_redir)
		return (1);
	return (0);
}
