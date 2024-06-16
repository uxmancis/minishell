/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_1_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:22:45 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/24 18:24:20 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_strcpy(char *str_src, char **str_dst)
{
	int	len;
	int	i;

	len = ft_strlen(str_src);
	i = 0;
	while (len > 0)
	{
		(*str_dst)[i] = str_src[i];
		i++;
		len--;
	}
}

void	generate_substr(t_prompt *prompt, int substr_id, t_box **box)
{
	int	len;

	len = (int)ft_strlen(prompt->total_substr_input[substr_id - 1]);
	(*box)->input_substr = malloc(sizeof(char) * (len + 1));
	(*box)->input_substr[len] = '\0';
	ft_strcpy(prompt->total_substr_input[substr_id - 1], &(*box)->input_substr);
}

/*get_dict_quotes
*
*   Returns:
*       -1: Error: syntax error: unclosed quotes
*       0: Success
*
*	Explanatory comments:
*		//+1 for NULL value is not needed
*		box->dict_quotes = malloc(sizeof(int)*len); 
*		//About ft_quotes: 1. Make sure 100% main quotes are closed;
*						   2. generates dict_quotes (box), '&' is sent
*		if (ft_quotes (box->input_substr, &box->dict_quotes)== -1)
*/
int	get_dict_quotes(t_box **box)
{
	int	len;
	int	i;

	len = ft_strlen((*box)->input_substr);
	(*box)->dict_quotes = malloc(sizeof(int)*len);
	if (ft_quotes ((*box)->input_substr, &(*box)->dict_quotes) == -1)
	{
		ft_puterror("syntax error: unclosed quotes\n");
		return (-1);
	}
	i = 0;
	while (len > 0)
	{
		printf("               dict_substr[%d] = %d\n", i, (*box)->dict_quotes[i]);
		len--;
		i++;
	}
	return (0);
}

void	get_single_str(t_prompt *prompt, t_box **box)
{
	int	len_substr;

	len_substr = (int)ft_strlen(prompt->input);
	(*box)->input_substr = malloc(sizeof(char) * (len_substr + 1));
	(*box)->input_substr[ft_strlen(prompt->input)] = '\0';
	ft_strcpy(prompt->input, &(*box)->input_substr);
}

void	ft_free_char(char **words, int nb_of_words)
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
