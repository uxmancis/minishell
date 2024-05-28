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

# include "../inc/minishell.h"

void ft_strcpy (char *str_src, char **str_dst)
{
    int len;
    int i; 
    
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

void generate_substr(t_prompt *prompt, int substr_id, t_box *box)
{
    int len;

    //printf(MAGENTA"generate_substr, substr_id = %d\n"RESET_COLOR, substr_id);
    //printf(MAGENTA"substr to be printed, [%d] = %s\n"RESET_COLOR, substr_id, prompt->total_substr_input[substr_id - 1]);
    len = (int)ft_strlen(prompt->total_substr_input[substr_id - 1]);
    //printf("len substr = %d\n", len);
    box->input_substr = malloc(sizeof(char) * (len + 1)); //+1: valor nulo final
    box->input_substr[len] = '\0';
    ft_strcpy(prompt->total_substr_input[substr_id - 1], &box->input_substr);
    //printf("Copied! :) BOX: substr = %s\n", box->input_substr);
}

void get_dict_quotes(t_box *box)
{
    int len;
    int i;

    //printf("input_substr = %s\n", box->input_substr);
    len = ft_strlen(box->input_substr);
    box->dict_quotes = malloc(sizeof(int)*len); //conscientemente solo creo con largo de len, no necesito 1 más para nulo.
    //printf("get_dict_quotes, len = %d\n", len);
    if (ft_quotes (box->input_substr, &box->dict_quotes)== -1) //1. Asegurar 100% comillas principales cerradas y generar dict_quotes (&: para que se actualicen los valores = se informe por primera vez el diccionario dict_quotes). Mando &prompt, para que se actualice el diccionario de vuelta.
        ft_puterror_exit("syntax error: unclosed quotes\n");
    i = 0;
    while (len > 0)
    {
        printf("               dict_substr[%d] = %d\n",i, box->dict_quotes[i]);
        len--;
        i++;
    }
}

void get_single_str(t_prompt *prompt, t_box *box)
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

/*  ft_boxes_init, Initializes following variables in 
*   t_box structure:
*       · input_substr: substr (input divided based on splits)
*/
void ft_boxes_init(t_prompt *prompt, int substr_id)
{
    t_box box;
    //int tmp_len;
    int len;
    int i;

    //tmp_len = ft_strlen(prompt->total_substr_input[substr_id] + 1);
    //printf("tmp_len = %d\n", tmp_len);
    //printf("substr = %s\n", prompt->total_substr_input[substr_id]);
    printf(BLUE"\n\n\n======ִֶָ𓂃 ࣪˖ ִֶָ🐇་༘࿐====ᯓ★_⋆˚࿔ 📦BOX NB: %d 𝜗𝜚˚⋆========𓇼🐚☾☼🦪========;༊;༊__\n"RESET_COLOR, substr_id);
    printf("     02_boxes.c - "BLUE"ft_boxes_init"RESET_COLOR": Boxes are generated here. Nb_of_substr to be created = "BLUE"%d"RESET_COLOR". Let's start!\n", prompt->nb_of_substr);
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
    printf("     02_boxes.c - ft_boxes_init| Copied!✅"BLUE" input_substr"RESET_COLOR" generated:"GREEN" %s\n"RESET_COLOR, box.input_substr);
    get_dict_quotes(&box); //dict_quotes
    printf("     02_boxes.c - ft_boxes_init|"BLUE" dict_quotes"RESET_COLOR" generated✅\n");
    get_redirections(&box);
    //box.nb_of_heredocs = ft_get_numof_heredocs(&box);
    //printf("nb_of_heredocs = %d\n", box.nb_of_heredocs);
    get_rest(&box, &prompt);
    //execute_commands(box);
    printf("\n\n//pdte.: recopilar info de comandos, argumentos\n");
    printf(BLUE"BOX GENERATION COMPLETED✅, box number = %d\n"RESET_COLOR, substr_id);
    printf(BLUE"==============================================================================\n\n\n"RESET_COLOR);
}

void get_rest (t_box *box, t_prompt **prompt)
{
    //printf(GREEN"02_boxes_rest.c | get_rest\n"RESET_COLOR);
    //box->nb_of_heredocs = ft_get_numof_heredocs(box);
    //printf("GET REST | nb_of_heredocs = %d\n", box->nb_of_heredocs);
    //box->nb_of_heredocs = ft_get_numof_heredocs(box);
    ft_heredocs(&box, HEREDOC);
    ft_infiles(&box, INFILE);
    ft_outfile_append(&box, OUTFILE_APPEND);
    ft_outfile_strong(&box, OUTFILE_STRONG);
    //box->micasa = malloc(sizeof(char) * 4);
    //box->micasa[0] = 'u';
    //box->micasa[1] = 'u';
    //box->micasa[2] = 'u';
    //box->micasa[3] = '\0';
    //printf(">>>>>>>>>>>> name = %s\n", box->micasa);
    ft_cmd_args(&box, prompt);
}

/*
*   Generates boxes based on nb_of_substr indicated in prompt
*   structure.
*/
void ft_gen_boxes(t_prompt *prompt)
{
    int tmp_nb_boxes;
    int substr_id; //¿Qué substr es? ¿Es el n.º 0? ¿El número 1?

    printf(BLUE"\n\nft_gen_boxes\n"RESET_COLOR);
    tmp_nb_boxes = prompt->nb_of_substr;
    printf("     02_boxes.c - ft_gen_boxes| nb_boxes = %d\n", prompt->nb_of_substr);
    //if (prompt->nb_of_substr == 1)
        //printf("")
    substr_id = 1;
    while (tmp_nb_boxes > 0)
    {
        ft_boxes_init(prompt, substr_id);
        tmp_nb_boxes--;
        substr_id++;
    }
}


