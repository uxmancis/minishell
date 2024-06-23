/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_6_cmd_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:41:36 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:14 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*rest_numof_words
*
*   In char    **rest_info_potential_cmd variable (box) we will
*   store rest of info, where we will aim to find commands and arguments.
*
*   rest_numof_words will return the number of words we will find
*   along rest 'Y' marked info (in what_to_take).
*/
int	rest_numof_words(t_box **box)
{
	int	counter;
	int	len;
	int	i;
	int	keep_len;

	len = ft_strlen((*box)->input_substr);
	keep_len = len;
	i = 0;
	counter = 0;
	while (len > 0)
	{
		if ((*box)->what_to_take[i] == 'Y')
		{
			if (possible_cases(box, i))
				counter++;
			while (possible_cases(box, i) && i < keep_len)
				i++;
		}
		if (i == keep_len - 1 || i == keep_len)
			break ;
		len--;
		i++;
	}
	return (counter);
}

void	update_variables_2(int *i, int *len)
{
	*len = *len - 1;
	*i = *i + 1;
}

void	rest_get_ind_beginning_words_2(t_box **box, int *x, int i)
{
	(*box)->index_beginning_words_rest[*x] = i;
	put_parsing_box_index_words(box, *x);
	*x = *x + 1;
}

/*rest_get_ind_beginning_words
*
*   It's almost the same function as rest_numof_words.
*
*   Difference: instead of using it to return number of words
*   (int     nb_of_words_rest in words), we'll use it to inform
*   following variable: int    *index_beginning_words_rest (box),
*   containing index of beginning of each of rest of words to be
*   afterwards copied in char    **rest_info_potential_cmd (box).
*
*/
void	rest_get_ind_beginning_words(t_box **box)
{
	int	len;
	int	i;
	int	keep_len;
	int	x;

	(*box)->index_beginning_words_rest = malloc(sizeof(int)
			* (*box)->nb_of_words_rest);
	len = ft_strlen((*box)->input_substr);
	keep_len = len;
	i = 0;
	x = 0;
	while (len > 0)
	{
		if ((*box)->what_to_take[i] == 'Y')
		{
			if (possible_cases(box, i))
				rest_get_ind_beginning_words_2(box, &x, i);
			while (possible_cases(box, i) && i < keep_len)
				i++;
		}
		if (i == keep_len - 1 || i == keep_len)
			break ;
		update_variables_2(&i, &len);
	}
}

/*
*   Cases to take into account in order to consider when counting
*   total number of words to be copied in rest_info_potential_cmd.
*
*   Explanation:
*       - Anything that is not '\'', '\"' or !ft_isspace --> will
*		automatically count as new word. Doesn't matter if inside
*		of outside of quotes.
*       - Quotes (either both simple '\'' and double '\"') --> will
*		count only when inside of other type of quotes. Simples must
*		be inside of doubles and viceversa.
*       - ft_isspace will count if inside of quotes (either both single or doble)
*/
int	possible_cases(t_box **box, int index)
{
	if ((*box)->input_substr[index] == '\''
		&& (*box)->dict_quotes[index] == 2)
		return (1);
	else if ((*box)->input_substr[index] == '\"'
		&& (*box)->dict_quotes[index] == 1)
		return (1);
	else if (ft_isspace((*box)->input_substr[index])
		&& (*box)->dict_quotes[index] != 0)
		return (1);
	else if ((*box)->input_substr[index] != '\''
		&& (*box)->input_substr[index] != '\"'
		&& !ft_isspace((*box)->input_substr[index]))
		return (1);
	return (0);
}
