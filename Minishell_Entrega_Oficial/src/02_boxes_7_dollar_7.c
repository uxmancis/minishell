/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_7.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:00:12 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/09 14:20:47 by uxmancis         ###   ########.fr       */
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

	//printf("     get_nb_of_dollars\n");
	len_word = ft_strlen((*box)->rest_info_potential_cmd[ind]);
	counter = 0;
	//printf("     len = %d, ind = %d\n", len_word, ind);
	i = 0;
	while (len_word > 0)
	{
		//printf("                      rest_info_potential_cmd[%d][%d] = %c\n", ind, i, (*box)->rest_info_potential_cmd[ind][i]);
		if ((*box)->rest_info_potential_cmd[ind][i] == '$')
			counter++;
		i++;
		len_word--;
	}
	//printf(YELLOW"     nb_of_dollars = %d\n\n"RESET_COLOR, counter);
	return (counter);
}

void	ft_replace(t_box **box, int ind, char *str_after)
{
	int	new_len;
	int	i;

	//printf("ft_replace\n");
	new_len = ft_strlen(str_after);
	//printf("new_len = %d\n", new_len);
	free((*box)->rest_info_potential_cmd[ind]);
	(*box)->rest_info_potential_cmd[ind] = malloc(sizeof(char) * (new_len + 1));
	(*box)->rest_info_potential_cmd[ind][new_len] = '\0';
	i = 0;
	while (new_len > 0)
	{
		//printf("yes\n");
		(*box)->rest_info_potential_cmd[ind][i] = str_after[i];
		i++;
		new_len--;
	}
	//printf("done!\n");
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
		//printf("Before nb = %d - ", nb);
		len++;
		nb = nb / 10;
		//printf("After nb = %d\n", nb);
	}
	if (nb > 0 && nb < 10)
		len++;
	//printf("len itoa = %d\n", len);
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	i = len - 1 ;
	while (len > 0) //copiarmos de dcha a izq.
	{
		str[i] = (keep_nb % 10) + 48;
		i--;
		keep_nb = keep_nb / 10;
		len--;
	}
	//printf("result = %s\n", str);
	return (str);
}

/*  Assigns values to tmp_dict_quotes_word based on start value.
*   
*   start value is taken from index_beggining_words_rest (box).
*
*/
void	fill_tmp_dict_quotes(t_box **box, int **tmp_dict_quotes_word, int len, int start)
{
	int i; 

	i = 0;
	//printf(YELLOW"     fill_tmp_dict_quotes"RESET_COLOR"| start = %d, len = %d\n", start, len);
	while (len > 0) //Next to solve: aquí tmp_dict_quotes_word no está llegando con su nuevo len
	{
		(*tmp_dict_quotes_word)[i] = (*box)->dict_quotes[start];
		printf(GREEN"          tmp_dict_qotes[%d] = %d\n"RESET_COLOR, i, (*tmp_dict_quotes_word)[i]);
		len--;
		i++;
		//start++;
	}
}
