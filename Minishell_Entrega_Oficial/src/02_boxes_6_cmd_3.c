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

	(*box)->index_beginning_words_rest = malloc(sizeof(int) * (*box)->nb_of_words_rest);
	len = ft_strlen((*box)->input_substr);
	keep_len = len;
	i = 0;
	x = 0;
	while (len > 0)
	{
		if ((*box)->what_to_take[i] == 'Y')
		{
			if (possible_cases(box, i))
			{
				(*box)->index_beginning_words_rest[x] = i;
				printf("                      index_beginning_words_rest[%d] = %d\n", x, (*box)->index_beginning_words_rest[x]);
				x++;
			}
			while (possible_cases(box, i) && i < keep_len)
				i++;
		}
		if (i == keep_len - 1 || i == keep_len)
			break ;
		len--;
		i++;
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

/*Returns:
*   1: Success, it's a redirección
*   0: Failure, it's not a redirección
*/
int	is_red(t_box **box, int index)
{
	if (((*box)->input_substr[index] == '<'
			|| (*box)->input_substr[index] == '>')
		&& (*box)->dict_quotes[index] == 0)
		return (1);
	return (0);
}

/*cpy_1_word
*
*   Variables:
*       nb_of_word: zenbagarren rest-eko hitza dan 
				(posición en index_beginning_words_rest)
*       start: index of beginning of word.
*			Already precise. No need to go spaces++
*/
void	cpy_1_word(t_box **box, int nb_of_word)
{
	int	len;
	int	start;
	int	keep_start;
	int	x;

	start = (*box)->index_beginning_words_rest[nb_of_word]; //hasiera de dónde empieza la palabra word
	keep_start = start;
	len = 0;
	while (possible_cases(box, start)
		&& (start < (int)ft_strlen((*box)->input_substr))
		&& !is_red(box, start))
	{
		start++;
		len++;
	}
	(*box)->rest_info_potential_cmd[nb_of_word] = malloc(sizeof(char) * (len + 1));
	(*box)->rest_info_potential_cmd[nb_of_word][len] = '\0';
	x = 0;
	while (len > 0)
	{
		(*box)->rest_info_potential_cmd[nb_of_word][x] = (*box)->input_substr[keep_start];
		len--;
		x++;
		keep_start++;
	}
	printf("                      rest_info_potential_cmd[%d] = ["MAGENTA"%s"RESET_COLOR"]\n", nb_of_word, (*box)->rest_info_potential_cmd[nb_of_word]);
}