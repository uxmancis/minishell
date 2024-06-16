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
		//printf("ORIGEN: %c\n", str_src[i]);
		//printf("DESTINO: %c\n", *str_dst[i]);
		i++;
		len--;
	}
	//printf("i = %d\n", i);
	//printf("str copied = %s\n", *str_dst);
}

void	generate_substr(t_prompt *prompt, int substr_id, t_box *box)
{
	int	len;

	//printf(MAGENTA"generate_substr, substr_id = %d\n"RESET_COLOR, substr_id);
	//printf(MAGENTA"substr to be printed, [%d] = %s\n"RESET_COLOR, substr_id, prompt->total_substr_input[substr_id - 1]);
	len = (int)ft_strlen(prompt->total_substr_input[substr_id - 1]);
	//printf("len substr = %d\n", len);
	box->input_substr = malloc(sizeof(char) * (len + 1)); //+1: valor nulo final
	box->input_substr[len] = '\0';
	ft_strcpy(prompt->total_substr_input[substr_id - 1], &box->input_substr);
	//printf("Copied! :) BOX: substr = %s\n", box->input_substr);
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
int	get_dict_quotes(t_box *box)
{
	int	len;
	int	i;

	//printf("input_substr = %s\n", box->input_substr);
	len = ft_strlen(box->input_substr);
	box->dict_quotes = malloc(sizeof(int)*len);
	//printf("get_dict_quotes, len = %d\n", len);
	if (ft_quotes (box->input_substr, &box->dict_quotes) == -1)
	{
		ft_puterror("syntax error: unclosed quotes\n");
		return (-1);
	}
	i = 0;
	while (len > 0)
	{
		printf("               dict_substr[%d] = %d\n", i, box->dict_quotes[i]);
		len--;
		i++;
	}
	return (0);
}

void	get_single_str(t_prompt *prompt, t_box *box)
{
	int len_substr;

	len_substr = (int)ft_strlen(prompt->input);
	//printf("ORIGEN| str = %s, len = %d\n", prompt->input, (int)ft_strlen(prompt->input));
	box->input_substr = malloc(sizeof(char) * (len_substr + 1));
	box->input_substr[ft_strlen(prompt->input)] = '\0';
	//printf("DESTINO| len = %d\n", (int)ft_strlen(box->input_substr));
	ft_strcpy(prompt->input, &box->input_substr);
	//printf(BLUE"    Copied! str = %s (single str jeje)\n"RESET_COLOR, box->input_substr);
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

void	ft_free_int(int **words, int nb_of_words)
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

void	ft_free_box (t_box box)
{
	if (box.input_substr)
		free(box.input_substr);
	if (box.dict_quotes)
		free(box.dict_quotes);
	ft_free_int(box.dict_red_index_type, box.nb_of_redir);
	ft_free_char(box.words_hrdc, box.nb_of_heredocs);
	ft_free_char(box.words_infile, box.nb_of_infile);
	ft_free_char(box.words_outfile_append, box.nb_of_outfile_append);
	ft_free_char(box.words_outfile_strong, box.nb_of_outfile_strong);
	if (box.what_to_take)
		free(box.what_to_take);
	if (box.index_beginning_words_rest)
		free(box.index_beginning_words_rest);
	ft_free_char(box.rest_info_potential_cmd, box.nb_of_words_rest);
	if (box.tmp_pid_str)
		free(box.tmp_pid_str);
}

void	ft_boxes_initialize(t_box *box)
{
	box->input_substr = NULL;
	box->infd = 0;
	box->outfd = 0;
	box->pid = 0;
	//box->pipefd[2] = {0};
	box->pipefd[0] = 0;
	box->pipefd[1] = 0;
	box->dict_quotes = NULL;
	box->nb_of_redir = 0;
	box->dict_red_index_type = NULL;
	box->nb_of_heredocs = 0;
	box->words_hrdc = NULL;
	box->is_infile = 0;
	box->nb_of_infile = 0;
	box->words_infile = NULL;
	box->is_outfile_append = 0;
	box->nb_of_outfile_append = 0;
	box->words_outfile_append = NULL;
	box->is_outfile_strong = 0;
	box->nb_of_outfile_strong = 0;
	box->words_outfile_strong = NULL;
	box->what_to_take = NULL;
	box->nb_of_words_rest = 0;
	box->index_beginning_words_rest = NULL;
	box->rest_info_potential_cmd = NULL;
	box->tmp_pid = -1;
	box->tmp_pid_str = NULL;
}

/*  ft_boxes_init, Initializes following variables in 
*   t_box structure:
*       · input_substr: substr (input divided based on splits)
*
*   Returns: 
*       -1: Error
*       0: Success
*/
int	ft_boxes_init(t_prompt *prompt, int substr_id)
{
	t_box	box;
	//int tmp_len;
	int len;
	int i;

	//tmp_len = ft_strlen(prompt->total_substr_input[substr_id] + 1);
	//printf("tmp_len = %d\n", tmp_len);
	//printf("substr = %s\n", prompt->total_substr_input[substr_id]);
	printf(BLUE"\n\n\n======ִֶָ𓂃 ࣪˖ ִֶָ🐇་༘࿐====ᯓ★_⋆˚࿔ 📦BOX NB: %d 𝜗𝜚˚⋆========𓇼🐚☾☼🦪========;༊;༊__\n"RESET_COLOR, substr_id);
	printf("     02_boxes.c - "BLUE"ft_boxes_init"RESET_COLOR": Boxes are generated here. Nb_of_substr to be created = "BLUE"%d"RESET_COLOR". Let's start!\n", prompt->nb_of_substr);
	ft_boxes_initialize(&box);
	if (prompt->nb_of_substr == 1)
		get_single_str(prompt, &box);
	else
		generate_substr(prompt, substr_id, &box); //input_substr virgen
	//printf(GREEN"ft_boxes_init, substr to be printed[%d] = %s, len = %d\n"RESET_COLOR, substr_id, prompt->total_substr_input[substr_id], (int)ft_strlen(prompt->total_substr_input[substr_id]));
	len = ft_strlen(box.input_substr);
	i = 0;
	while (len > 0)
	{
		printf("               input_substr[%d] = %c\n", i, box.input_substr[i]);
		i++;
		len--;
	}
	printf("     02_boxes.c - ft_boxes_init| Copied!✅"BLUE" input_substr"RESET_COLOR" generated:"GREEN" %s"RESET_COLOR", len = %d\n", box.input_substr, (int)ft_strlen(box.input_substr));
	if (get_dict_quotes(&box) == -1)
		return (-1);
	printf("     02_boxes.c - ft_boxes_init|"BLUE" dict_quotes"RESET_COLOR" generated✅\n");
	if (get_redirections(&box) == -1)
		return (-1);
	//box.nb_of_heredocs = ft_get_numof_heredocs(&box);
	//printf("nb_of_heredocs = %d\n", box.nb_of_heredocs);
	if (get_rest(&box, &prompt) == -1)
		return (-1);
	//David aquí: EXECUTE
	//initialize_cmd(&box, prompt, substr_id);
	//Liberar
	//ft_free_box(box);
	printf("\n\n//pdte.: recopilar info de comandos, argumentos\n");
	printf(BLUE"BOX GENERATION COMPLETED✅, box number = %d\n"RESET_COLOR, substr_id);
	printf(BLUE"==============================================================================\n\n\n"RESET_COLOR);
	return (0);
}

/*get_rest
*
*   Returns:
*       -1: Error
*       0: Success
*
*/
int	get_rest(t_box *box, t_prompt **prompt)
{
	//printf(GREEN"02_boxes_rest.c | get_rest\n"RESET_COLOR);
	//box->nb_of_heredocs = ft_get_numof_heredocs(box);
	//printf("GET REST | nb_of_heredocs = %d\n", box->nb_of_heredocs);
	//box->nb_of_heredocs = ft_get_numof_heredocs(box);
	if (ft_heredocs(&box, HEREDOC) == -1 || ft_infiles(&box, INFILE) == -1
		|| ft_outfile_append(&box, OUTFILE_APPEND) == -1
		|| ft_outfile_strong(&box, OUTFILE_STRONG) == -1)
		return (-1);
	if (ft_cmd_args(&box, prompt) == -1)
		return (-1);
	return (0);
}

/*
*   Generates boxes based on nb_of_substr indicated in prompt
*   structure.
*
*	substr_id: Tells us which substr / which box are we referring to.
*/
int	ft_gen_boxes(t_prompt *prompt)
{
	int	tmp_nb_boxes;
	int	substr_id;

	printf(BLUE"\n\nft_gen_boxes\n"RESET_COLOR);
	tmp_nb_boxes = prompt->nb_of_substr;
	printf("     02_boxes.c - ft_gen_boxes| nb_boxes = %d\n", prompt->nb_of_substr);
	//if (prompt->nb_of_substr == 1)
		//printf("")
	substr_id = 1;
	while (tmp_nb_boxes > 0)
	{
		if (ft_boxes_init(prompt, substr_id) == -1)
			return (-1);
		tmp_nb_boxes--;
		substr_id++;
	}
	return (0);
}
