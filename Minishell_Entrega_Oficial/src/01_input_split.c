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

# include "../inc/minishell.h"

/*
*	ft_split_from_to:
*
*	len_substr = (end - start + 1)
*		end - start + 1: so that both positions are included in substr.
*/
char *ft_split_from_to(int start, int end, char *src_input)
{
	char *dst;
	int len_substr;
	int index_src;
	int index_dst;

	//printf(">> ft_split_from_to\n");
	if (end > (int)ft_strlen(src_input))
	{
		ft_puterror("error when accessing to memory - input_split.c\n");
		return (NULL);
	}
	len_substr = (end - start + 1); //incluye ambas posiciones start y end en substr
	//printf(RED">>>>> start = %d, end = %d, len_substr = %d\n"BLUE, (int)start, (int)end, len_substr);
	//printf(RESET_COLOR);
	dst = malloc(sizeof(char)*(len_substr + 1));
	dst[len_substr] = '\0';
	if (!dst)
		ft_puterror_exit("malloc error\n");
	index_src = start;
	index_dst = 0;
	while (index_src <= end)
	{
		dst[index_dst] = src_input[index_src];
		index_src++;
		index_dst++;
	}
	//printf(GREEN">>>>> substr (dentro de ft_get_substr)= %s, len = %zu\n"RESET_COLOR, dst, ft_strlen(dst));
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
void ft_split_input(t_prompt **prompt)
{
	int tmp_nb_of_substr;
	//char **total_substr_input;
	//int aux_para_imprimir_nb_of_pipes_mas_1_final;
	int x; 
	int start;
	int index_end;
	int i;
	//int aux_para_imprimir_nb_of_substr;
	
	//nb_of_substr = ft_strlen(arr_index_pipes) + 1;
	//nb_of_substr = (*prompt)->nb_of_pipes + 1;
	//aux_para_imprimir_nb_of_substr = nb_of_substr; //pdte. eliminar. Para debugear
	//printf(GREEN"nb_of_substr = %d\n"RESET_COLOR, nb_of_substr);
	(*prompt)->nb_of_substr = (*prompt)->nb_of_pipes + 1;
	//printf(YELLOW"01_input_split.c - line 77, nb_substr = %d\n"RESET_COLOR, (*prompt)->nb_of_substr);
	(*prompt)->total_substr_input = malloc(sizeof(char *) * ((*prompt)->nb_of_substr));
	//total_substr_input[nb_of_substr][0] = '\0';
	if (!(*prompt)->total_substr_input)
		ft_puterror_exit("malloc error\n");
	start = 0;
	index_end = 0;;
	x = 0;
	//printf(BLUE"input_splic.c - INDEX of PIPES:\n");
	/*aux_para_imprimir_nb_of_pipes_mas_1_final = (*prompt)->nb_of_pipes + 1;
	i = 0;
	while (aux_para_imprimir_nb_of_pipes_mas_1_final > 0)
	{
		//printf("arr_index_pipes[%d] = %d\n", i, (*prompt)->arr_index_pipes[i]);
		i++;
		aux_para_imprimir_nb_of_pipes_mas_1_final--;
	}
	printf(RESET_COLOR);*/
	int tmp_num_pipes;
	//int i;
	i = 0;
	tmp_num_pipes = (*prompt)->nb_of_pipes;
	//printf("nb_pipes = %d, tmp_num_pipes = %d\n", (*prompt)->nb_of_pipes, tmp_num_pipes);
	while (tmp_num_pipes > 0)
	{
		printf("array_index_pipes[%d] = %d\n", i, (*prompt)->arr_index_pipes[i]);
		tmp_num_pipes--;
		i++;
	}
	//printf(RED"holahola\n"RESET_COLOR);
	tmp_nb_of_substr = (*prompt)->nb_of_substr;
	//printf(GREEN"tmp_nb_of_substr = %d\n"RESET_COLOR, tmp_nb_of_substr);
	while (tmp_nb_of_substr > 0)
	{
		//printf(RED"x = %d, tmp_nb_of_substr = %d\n", x, tmp_nb_of_substr);
		if (tmp_nb_of_substr == 1) //en la última vuelta, se gestiona para que end index = fin de cadena (ft_strlen(input))
		{
			//printf("YAS!, x = %d\n", x);
			(*prompt)->total_substr_input[x] = ft_split_from_to(start, (ft_strlen((*prompt)->input) - 1), (*prompt)->input); //-1 ze uste dot bebai izengo zala hasta la posición anterior
			printf(YELLOW"substr %d = %s\n"RESET_COLOR, x, (*prompt)->total_substr_input[x]);
			break; //end of loop, no need to continue
		}	
		else
		{
			// printf(MAGENTA"x = %d\n "RESET_COLOR, x);
			(*prompt)->total_substr_input[x] = ft_split_from_to(start, ((*prompt)->arr_index_pipes[index_end] - 1), (*prompt)->input); //-1: substr hasta la posición anterior beti
			printf(YELLOW"substr %d = %s\n"RESET_COLOR, x, (*prompt)->total_substr_input[x]);
		}
		//printf("situ control, start = %d, index_end = %d, arr_index_pipes[%d] = %d\n", start, index_end, index_end, (*prompt)->arr_index_pipes[index_end]);
		start = ((*prompt)->arr_index_pipes[index_end]) + 1;
		index_end++,
		tmp_nb_of_substr--;
		x++;
		printf(MAGENTA"tmp_nb_of_substr = %d\n"RESET_COLOR, tmp_nb_of_substr);
	}
	/*printf(GREEN"substr spliteados, RTDO:\n");
	i = 0;
	while (aux_para_imprimir_nb_of_substr > 0)
	{
		printf(GREEN"substr%d = %s\n"RESET_COLOR, i, (*prompt)->total_substr_input[i]);
		aux_para_imprimir_nb_of_substr--;
		i++;
	}*/
	//return (aux_para_imprimir_nb_of_substr);
}
