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
void	ft_split_input(t_prompt **prompt)
{
	int	tmp_nb_of_substr;
	int	x;
	int	start;
	int	index_end;
	int	i;

	(*prompt)->nb_of_substr = (*prompt)->nb_of_pipes + 1;

	(*prompt)->total_substr_input = malloc(sizeof(char *) * ((*prompt)->nb_of_substr));
	if (!(*prompt)->total_substr_input)
		ft_puterror("malloc error\n");
	start = 0;
	index_end = 0;
	x = 0;
	int tmp_num_pipes;
	i = 0;
	tmp_num_pipes = (*prompt)->nb_of_pipes;
	//printf("nb_pipes = %d, tmp_num_pipes = %d\n", (*prompt)->nb_of_pipes, tmp_num_pipes);
	while (tmp_num_pipes > 0)
	{
		printf("array_index_pipes[%d] = %d\n", i, (*prompt)->arr_index_pipes[i]);
		tmp_num_pipes--;
		i++;
	}
	tmp_nb_of_substr = (*prompt)->nb_of_substr;
	while (tmp_nb_of_substr > 0)
	{
		if (tmp_nb_of_substr == 1) //en la última vuelta, se gestiona para que end index = fin de cadena (ft_strlen(input))
		{
			(*prompt)->total_substr_input[x] = ft_split_from_to(start, (ft_strlen((*prompt)->input) - 1), (*prompt)->input); //-1 ze uste dot bebai izengo zala hasta la posición anterior
			printf(YELLOW"substr %d = %s\n"RESET_COLOR, x, (*prompt)->total_substr_input[x]);
			break;
		}	
		else
		{
			(*prompt)->total_substr_input[x] = ft_split_from_to(start, ((*prompt)->arr_index_pipes[index_end] - 1), (*prompt)->input); //-1: substr hasta la posición anterior beti
			printf(YELLOW"substr %d = %s\n"RESET_COLOR, x, (*prompt)->total_substr_input[x]);
		}
		start = ((*prompt)->arr_index_pipes[index_end]) + 1;
		index_end++,
		tmp_nb_of_substr--;
		x++;
	}
}
