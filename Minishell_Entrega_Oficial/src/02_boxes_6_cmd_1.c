/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_6_cmd_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:46:55 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/24 18:24:44 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"


void mark_quotes(t_box **box)
{
    int len_substr;
    int i;

    len_substr = ft_strlen((*box)->input_substr);
    i = 0;
    while (len_substr > 0)
    {
        if (((*box)->input_substr[i] == '\'' || (*box)->input_substr[i] == '\"')
            && (*box)->dict_quotes[i] == 0)
            (*box)->what_to_take[i] = 'Q';
        i++;
        len_substr--;
    }
}

/*check_empty_str
*
*	Aims to identify if there is any "" empty str
*	or '' as first argument of possible commands.
*
*	Reason: echo hola is not the same as "" echo hola.
*		echo hola: prints hola
*		"" echo hola: command not found
*/
// int	check_empty_str(t_box **box)
// {
// 	int	len_substr;
// 	int	keep_len_substr;
// 	int	i;

// 	printf(YELLOW"check_empty_str\n"RESET_COLOR);
// 	len_substr = ft_strlen((*box)->input_substr);
// 	keep_len_substr = len_substr;
// 	i = 0;
// 	while (len_substr > 0)
// 	{
// 		while ((i + 1) < keep_len_substr && ft_isspace((*box)->input_substr[i])
// 			&& (*box)->what_to_take[i] == 'Y')
// 			i++;
// 		if ((i + 1) < keep_len_substr && (*box)->what_to_take[i] == 'Q') //antes de chequear próxima posición, make sure que existe
// 		{
// 			printf("1st Q identified\n");
// 			if ((*box)->what_to_take[i + 1] == 'Q')
// 			{
// 				printf("yes 2 Qs identified, return -1\n");
// 				return (-1);
// 			}
// 		}
// 		while ((*box)->what_to_take[i] != 'Y') //ha encontrado algo como primer comando que no es Y (es decir, deja de mirar aquí que ya son redirs o wrods. Y, adicionalmente, anteriormente, ssi ha llegado aqui es porque con la marca 'Y' en what_to_take sí ha encontrado algo pero no se trataba de una quote principal)
// 			i++;
// 		if ((*box)->what_to_take[i] == 'Y' && !ft_isspace((*box)->input_substr[i])) //si en algún momento te encunetras con un 'Y' pero no es main quote, salte
// 			return (0);
// 		i++;
// 		len_substr--;
// 	}
// 	return (0);
// }

// int check_if_first_word_empty_str(t_box **box, int start, int end)
// {}

// int is_empty_str_first_cmd(t_box **box)
// {
// 	int tmp_len_substr;
// 	int tmp_nb_of_redir;
// 	int nb_of_times_to_check;


// 	tmp_len_substr = ft_strlen((*box)->input_substr);
// 	tmp_nb_of_redir = (*box)->nb_of_redir;
// 	nb_of_times_to_check = tmp_nb_of_redir + 1; //
// 	while (nb_of_times_to_check > 0)
// 	{
// 		if (tmp_nb_of_redir == 0) //si no hay redirecciones, checkear start-end todo el substr
// 		{
// 			if(check_if_first_word_empty_str(box, 0, ft_strlen((*box)->input_substr)) == -1)
// 				return (-1);
// 		}
			
// 		if (check_if_first_word_empty_str(box))
// 		nb_of_times_to_check--;
// 	}
// }


/*is_empty_str_first_cmd
*
*	Returns:
*		-1: 2Qs found first thing along rest_info_potential_cmd
*		0: other content was found before 2Qs.
*
* 	2Qs = "" as first thing, command not found error.
*/
int is_empty_str_first_cmd (t_box **box)
{
	int len_substr;
	int keep_len_substr;
	int i;

	len_substr = ft_strlen((*box)->input_substr);
	keep_len_substr = ft_strlen((*box)->input_substr);
	i = 0;
	while (len_substr > 0)
	{
		//las R y W las ignoramos hasta el final del len_substr siempre que nos encontramos con ellas
		while (i < keep_len_substr && ((*box)->what_to_take[i] == 'R'
			|| (*box)->what_to_take[i] == 'W'))
			i++;
		
		//En cambio, en el scope que nos interesa...
		while (i < keep_len_substr && ((*box)->what_to_take[i] == 'Y'
			|| (*box)->what_to_take[i] == 'Q'))
		{
			if ((*box)->what_to_take[i] == 'Q') //si encontramos 1 quote
			{
				if ((i + 1) < keep_len_substr && (*box)->what_to_take[i + 1] == 'Q')
					return (-1); //2Qs lo primero que encontró
			}
			else if ((*box)->what_to_take[i] == 'Y' && !ft_isspace((*box)->input_substr[i]))
				return (0);
			i++;
		}
		i++;
		len_substr--;
	}
	return (0);
}

/*  ft_get_what_to_take
*
*   what_to_take variable will have the following info about
*   input_substr:
*
*       R: Redirección
*       W: Word (end delimiter, infile or outfile name. 1st word after redirección)
*       Y: YES take it as command and arguments to be analysed.
*
*	Return:
*		-1: Error: command not found. "" or '' as first command.
*		0: Success
*/
int ft_get_what_to_take(t_box **box)
{
    int len;
    int i;
    
    (*box)->what_to_take = malloc(sizeof(char)*(ft_strlen((*box)->input_substr)+1));
    (*box)->what_to_take[ft_strlen((*box)->input_substr)] = '\0';
    init_what_to_take(box); //Everything initializes as 'Y'
    mark_redir(box);
    mark_word(box);
    mark_quotes(box);
    if (is_empty_str_first_cmd(box) == -1)
    {
		ft_puterror("Command '' not found\n");
		return (-1);
    }
    //printf("hemen gare bueltan\n");
    //Result of_what_to_take:
    len = ft_strlen((*box)->input_substr);
    //len = ft_strlen((*box)->what_to_take); ns porq no funciona, baina bueno, me vale también input_substr porque tienen el mismo len
    i = 0;
    printf("     what_to_take: len = %d\n", len);
    while (len > 0)
    {
        printf("               what_to_take[%d] = %c\n", i, (*box)->what_to_take[i]);
        len--;
        i++;
    }
	return (0);
}

/*int get_len_only_needed(t_box **box)
{
    int counter;
    int len;
    int i;

    counter = 0;
    len = ft_strlen((*box)->input_substr);
    i = 0;
    while (len > 0)
    {
        if ((*box)->what_to_take[i] == 'Y')
            counter++;
        len++;
    }
    return (counter);
}*/

void cpy_rest_words(t_box **box)
{
    int tmp_nb_of_rest_words;
    int i;

    tmp_nb_of_rest_words = (*box)->nb_of_words_rest;
    printf("     cpy_rest_words, nb_of_words_rest = %d\n", tmp_nb_of_rest_words);
    (*box)->rest_info_potential_cmd = malloc(sizeof(char *) * (tmp_nb_of_rest_words + 1));
    (*box)->rest_info_potential_cmd[tmp_nb_of_rest_words] = malloc(sizeof(char) * 1);
    (*box)->rest_info_potential_cmd[tmp_nb_of_rest_words][0] = '\0';
    //printf("done\n");

    i = 0;
    while (tmp_nb_of_rest_words > 0)
    {
        cpy_1_word(box, i);
        tmp_nb_of_rest_words--;
        i++;
    }
}

void ft_get_only_needed(t_box **box)
{
    //int len_rest;
    //int i;
    //printf("micasa = %s\n", (*box)->micasa);
    printf("     ft_get_only_needed\n");
    (*box)->nb_of_words_rest = rest_numof_words(box);
    printf("               rest_numof_words | counter = "MAGENTA"%d\n"RESET_COLOR, (*box)->nb_of_words_rest);
    rest_get_ind_beginning_words(box);
    cpy_rest_words(box);
    
    /*len_rest = get_len_only_needed(box);
    (*box)->rest_info_potential_cmd = malloc(sizeof(char *) * (len_rest + 1))
    (*box)->rest_info_potential_cmd[len_rest] = '\0';
    i = 0;
    while (len_rest > 0)
    {
        
    }*/
}

/*ft_get_cmd_args
*
*	Returns:
*		-1: error management
*		0: Success
*/
int	ft_get_cmd_args(t_box **box, t_prompt **prompt)
{
	if (ft_get_what_to_take(box) == -1)
		return (-1);
	printf(MAGENTA"     char *what_to_take"RESET_COLOR" generated✅\n");
	ft_get_only_needed(box);
	//printf("nb_of_words_rest = %d\n", (*box)->nb_of_words_rest);
	if ((*box)->nb_of_words_rest > 0) //solo vamos a analizar dólar si hay palabras a analizar
		check_dollars_expansion(box, prompt);
	return (0);
}

/*ft_cmd_args
*
*	Returns:
*		-1: Error management
*		0: Success
*/
int   ft_cmd_args (t_box **box, t_prompt **prompt)
{
    //(*box)->micasa = malloc(sizeof(char) * 4);
    //(*box)->micasa[0] = 'u';
    //(*box)->micasa[1] = 'u';
    //(*box)->micasa[2] = 'u';
    //(*box)->micasa[3] = '\0';
    //printf(">>>>>>>>>>>> name = %s\n", (*box)->micasa);
    printf("     02_boxes_6_cmd.c - "MAGENTA"ft_cmd_args\n"RESET_COLOR);
    if (ft_get_cmd_args(box, prompt) == -1)
		return (-1);
	return (0);
}