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
		if ((*box)->dictred_i_t[i][1] == HEREDOC
			|| (*box)->dictred_i_t[i][1] == OUTFILE_APPEND)
		{
			current_ind_in_substr = (*box)->dictred_i_t[i][0];
			(*box)->what_to_take[current_ind_in_substr] = 'R';
			(*box)->what_to_take[current_ind_in_substr + 1] = 'R';
		}
		else if ((*box)->dictred_i_t[i][1] == INFILE
			|| (*box)->dictred_i_t[i][1] == OUTFILE_STRONG)
		{
			current_ind_in_substr = (*box)->dictred_i_t[i][0];
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

void	mark_word_3(t_box **box, int i)
{
	if ((*box)->dictred_i_t[i][1] == HEREDOC
		|| (*box)->dictred_i_t[i][1] == OUTFILE_APPEND)
		mark_word_2((*box)->dictred_i_t[i][0] + 2,
			ft_strlen((*box)->input_substr) - 1, box);
	else if (((*box)->dictred_i_t[i][1] == INFILE
		|| (*box)->dictred_i_t[i][1] == OUTFILE_STRONG))
		mark_word_2((*box)->dictred_i_t[i][0] + 1,
			ft_strlen((*box)->input_substr) - 1, box);
}

void	mark_word_4(t_box **box, int i)
{
	if ((*box)->dictred_i_t[i][1] == HEREDOC
				|| (*box)->dictred_i_t[i][1] == OUTFILE_APPEND)
		mark_word_2((*box)->dictred_i_t[i][0] + 2,
			(*box)->dictred_i_t[i + 1][0] - 1, box);
	else if (((*box)->dictred_i_t[i][1] == INFILE
		|| (*box)->dictred_i_t[i][1] == OUTFILE_STRONG))
		mark_word_2((*box)->dictred_i_t[i][0] + 1,
			(*box)->dictred_i_t[i + 1][0] - 1, box);
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
*		else (still more redirs): start: posición de redirección (+1 o +2),
*		end: posición next redirección
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
			mark_word_3(box, i);
			break ;
		}
		else
			mark_word_4(box, i);
		tmp_nb_of_redir--;
		i++;
	}
}
