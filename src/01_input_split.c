/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_input_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:43:54 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:10:43 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
*	ft_split_from_to:
*
*	
*	Explanatory comments:
*		len_substr = (end - start + 1)
*			end - start + 1: so that both positions are included in substr.
*/
char	*ft_split_from_to(int start, int end, char *src_input)
{
	char	*dst;
	int		len_substr;
	int		index_src;
	int		index_dst;

	if (end > (int)ft_strlen(src_input))
	{
		ft_puterror("error when accessing to memory - input_split.c\n");
		return (NULL);
	}
	len_substr = (end - start + 1);
	dst = malloc(sizeof(char) * (len_substr + 1));
	dst[len_substr] = '\0';
	if (!dst)
		ft_puterror("malloc error\n");
	index_src = start;
	index_dst = 0;
	while (index_src <= end)
	{
		dst[index_dst] = src_input[index_src];
		index_src++;
		index_dst++;
	}
	return (dst);
}

//new
/* ft_split_input
*	Genera: (*prompt)->total_substr_input
*		- Incluye el total de cadenas en las que se ha spliteado el input
*		en base al número de pipes (fuera de comillas) identificados.
*
*	Returns: nb_of_substr (solo para debuggear)
*/
void	ft_split_input(t_prompt **p)
{
	(*p)->nb_of_substr = (*p)->nb_of_pipes + 1;
	(*p)->total_substr_input = malloc(sizeof(char *) * ((*p)->nb_of_substr));
	if (!(*p)->total_substr_input)
		ft_puterror("malloc error\n");
	put_parsing_input_pipes_3(p);
	ft_split_input_2(p);
}

void	update_variables_1(int *ind_end, int *x, int *nb_of_substr)
{
	*ind_end = *ind_end + 1;
	*nb_of_substr = *nb_of_substr - 1;
	*x = *x + 1;
}

void	ft_split_input_2(t_prompt **p)
{
	int	tmp_nb_of_substr;
	int	x;
	int	start;
	int	index_end;

	tmp_nb_of_substr = (*p)->nb_of_substr;
	start = 0;
	index_end = 0;
	x = 0;
	while (tmp_nb_of_substr > 0)
	{
		if (tmp_nb_of_substr == 1)
		{
			(*p)->total_substr_input[x] = ft_split_from_to(start,
					(ft_strlen((*p)->input) - 1), (*p)->input);
			break ;
		}
		else
			(*p)->total_substr_input[x] = ft_split_from_to(start,
					((*p)->arr_index_pipes[index_end] - 1), (*p)->input);
		start = ((*p)->arr_index_pipes[index_end]) + 1;
		update_variables_1(&index_end, &x, &tmp_nb_of_substr);
	}
	put_parsing_input_substr(p);
}
