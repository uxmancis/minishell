/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_7.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:00:12 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/16 14:59:53 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free(void *arr)
{
	free (arr);
	arr = NULL;
}

/*is_dollar
*
*   Returns number of dollars found in each word to be analysed
*   from rest_info_potential_cmd. 
*/
int	get_nb_of_dollars(t_box **box, int ind)
{
	int	len_word;
	int	i;
	int	counter;

	len_word = ft_strlen((*box)->rest_info_potential_cmd[ind]);
	counter = 0;
	i = 0;
	while (len_word > 0)
	{
		if ((*box)->rest_info_potential_cmd[ind][i] == '$')
			counter++;
		i++;
		len_word--;
	}
	return (counter);
}

void	ft_replace(t_box **box, int ind, char *str_after)
{
	int	new_len;
	int	i;

	new_len = ft_strlen(str_after);
	free((*box)->rest_info_potential_cmd[ind]);
	(*box)->rest_info_potential_cmd[ind] = malloc(sizeof(char) * (new_len + 1));
	(*box)->rest_info_potential_cmd[ind][new_len] = '\0';
	i = 0;
	while (new_len > 0)
	{
		(*box)->rest_info_potential_cmd[ind][i] = str_after[i];
		i++;
		new_len--;
	}
}

char	*basic_itoa(int nb)
{
	char	*str;
	int		len;
	int		keep_nb;
	int		i;

	keep_nb = nb;
	len = 0;
	while (nb > 10)
	{
		len++;
		nb = nb / 10;
	}
	if (nb > 0 && nb < 10)
		len++;
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	i = len - 1 ;
	while (len > 0)
	{
		str[i] = (keep_nb % 10) + 48;
		i--;
		keep_nb = keep_nb / 10;
		len--;
	}
	return (str);
}

/*  Assigns values to tmp_dict_quotes_word based on start value.
*   
*   start value is taken from index_beggining_words_rest (box).
*
*/
void	fill_tmp_dict_quotes(t_box **box, int **dict, int len, int start)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		(*dict)[i] = (*box)->dict_quotes[start];
		len--;
		i++;
		start++;
	}
}
