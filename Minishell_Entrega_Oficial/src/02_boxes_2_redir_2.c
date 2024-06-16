/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_2_redir_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:48:41 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/16 17:02:55 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int ft_check_if_redir redir(t_box *box, char *input)
/* ft_get_numof_redir
 *
 *   Returns:
 *       -1: Error (E.g.: 3rd redirección was found)
 *		0: Success
 *
 *	Explanatory comments:
 *		//1st redirección found
 *			if (i < keep_len && (box->input_substr[i] == '<' 
 *			|| box->input_substr[i] == '>' ))
 *		//2nd redirección found
 *			else if (box->dict_quotes[i] == 0)
 *
 */
int	ft_get_numof_redir(t_box **box)
{
	int	i;
	int	counter;
	int	len;
	int	keep_len;

	i = 0;
	counter = 0;
	printf(RED "               input_substr = %s, len = %d\n" RESET_COLOR, (*box)->input_substr, (int)ft_strlen((*box)->input_substr));
	len = (int)ft_strlen((*box)->input_substr);
	keep_len = len;
	while (i < keep_len)
	{
		if (i < keep_len && ((*box)->input_substr[i] == '<'
				|| (*box)->input_substr[i] == '>') && (*box)->dict_quotes[i] == 0)
		{
			if ((((*box)->input_substr[i + 1] == '<'
						|| (*box)->input_substr[i + 1] == '>'))
				&& (*box)->dict_quotes[i + 1] == 0)
			{
				if (check_if_three_redirs(box, i) == -1)
					return (-1);
				else if ((*box)->dict_quotes[i] == 0)
				{
					counter++;
					i = i + 2;
				}
			}
			else if ((*box)->dict_quotes[i] == 0)
			{
				counter++;
				i++;
			}
		}
		i++;
		len--;
	}
	printf("     02_boxes_redir.c - ft_get_numof_redir| Counted!✅" BLUE " nb_of_red = %d\n" RESET_COLOR, counter);
	return (counter);
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
				(*box)->dict_red_index_type[index_of_arr][0] = (*i);
				(*box)->dict_red_index_type[index_of_arr][1] = HEREDOC;
				(*i) = (*i) + 1;
				return (0);
			}
			else
				return (-1);
		}
		else if ((*box)->input_substr[(*i) + 1] == '>'
			&& (*box)->dict_quotes[(*i) + 1] == 0)
		{
			ft_puterror("syntax error near unexpected token `newline'\n");
			return (-1);
		}
		else
		{
			if ((*box)->dict_quotes[(*i)] == 0)
			{
				(*box)->dict_red_index_type[index_of_arr][0] = (*i);
				(*box)->dict_red_index_type[index_of_arr][1] = INFILE;
				return (0);
			}
			else
				return (-1);
		}
	}
	return (0);
}

/*  set_red_greater_than
 *       Returns:
 *           0: Success - Redirection was assigned
 *           -1: Redirection was finally NOT assigned (inside quotes)
 */
int	set_red_greater_than(t_box **box, int *i, int index_of_arr)
{
	if ((*box)->input_substr[(*i)] != '>'
		&& (*box)->dict_quotes[(*i)] == 0)
		return (EXIT_FAILURE);
	else if ((*box)->input_substr[(*i)] == '>'
		&& (*box)->dict_quotes[(*i)] == 0)
	{
		if ((*box)->input_substr[(*i) + 1] == '>' && (*box)->dict_quotes[(*i) + 1] == 0)
		{
			if (((*box)->input_substr[(*i) + 2] == '<'
					&& (*box)->dict_quotes[(*i) + 2] == 0)
				|| ((*box)->input_substr[(*i) + 2] == '>'
					&& (*box)->dict_quotes[(*i) + 2] == 0))
			{
				ft_puterror("syntax error near unexpected token `newline'\n");
				return (-1);
			}
			if ((*box)->dict_quotes[(*i)] == 0) // si está fuera de comillas
			{
				(*box)->dict_red_index_type[index_of_arr][0] = (*i);
				(*box)->dict_red_index_type[index_of_arr][1] = OUTFILE_APPEND;
				(*i) = (*i) + 1;
				return (0);
			}
			else
				return (-1);
		}
		else if ((*box)->input_substr[(*i) + 1] == '<'
			&& (*box)->dict_quotes[(*i) + 1] == 0)
		{
			ft_puterror("syntax error near unexpected token `newline'\n");
			return (-1);
		}
		else
		{
			if ((*box)->dict_quotes[(*i)] == 0)
			{
				(*box)->dict_red_index_type[index_of_arr][0] = (*i);
				(*box)->dict_red_index_type[index_of_arr][1] = OUTFILE_STRONG;
				return (0);
			}
			else
				return (-1);
		}
	}
	return (0);
}

int	set_red_index_type(t_box **box)
{
	int	i;
	int	index_of_arr;
	int	len;

	i = 0;
	index_of_arr = 0;
	len = (int)ft_strlen((*box)->input_substr);
	printf("     02_boxes_redir.c - " BLUE "set_red_index_type" RESET_COLOR "| Info about redirecciones is stored here:\n");
	while (i < len)
	{
		if ((*box)->input_substr[i] == '<' && (*box)->dict_quotes[i] == 0)
		{
			if (set_red_less_than(box, &i, index_of_arr) == 0)
			{
				printf(GREEN "               redirection %d assigned:     [0]_INDEX: %d  [1]_TYPE: %s\n" RESET_COLOR, (index_of_arr + 1), (*box)->dict_red_index_type[index_of_arr][0], ft_enum_to_str((*box)->dict_red_index_type[index_of_arr][1]));
				index_of_arr++;
			}
			else
				return (-1);
		}
		else if ((*box)->input_substr[i] == '>' && (*box)->dict_quotes[i] == 0)
		{
			if (set_red_greater_than(box, &i, index_of_arr) == 0) //> and >> are assigned. Includes error management. We send &i in case it must be updated (+2, when double redirection is found)
			{
				printf(GREEN "               redirection %d assigned:     [0]_INDEX: %d  [1]_TYPE: %s\n" RESET_COLOR, (index_of_arr + 1), (*box)->dict_red_index_type[index_of_arr][0], ft_enum_to_str((*box)->dict_red_index_type[index_of_arr][1]));
				index_of_arr++;
			}
			else
				return (-1);
		}
		i++;
	}
	return (0);
}
