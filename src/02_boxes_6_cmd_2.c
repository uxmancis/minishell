/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_6_cmd_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:37:06 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:12 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/*  init_what_to_take
*
*   Initializes char *what_to_take variable (box) with
*   'Y' value.
*
*   Y = YES to take as comand/argument.
*/
void init_what_to_take(t_box **box)
{
    int len;
    int i;

    i = 0;
    len = ft_strlen((*box)->input_substr);
    while (len > 0)
    {
        (*box)->what_to_take[i] = 'Y';
        len--;
        i++;
    }
}

void mark_redir(t_box **box)
{
    int tmp_nb_of_redir; //=len dict_red_index_type
    int i;
    //int x;
    int current_ind_in_substr;
    //printf(GREEN"mark_redir\n"RESET_COLOR);
    //printf("     len dict_red_index_type = %d\n", (*box)->nb_of_redir);
    
    i = 0;
    //x = 0;
    tmp_nb_of_redir = (*box)->nb_of_redir;
    while (tmp_nb_of_redir > 0)
    {
        //printf("i = %d, dict_red_index_type[%d][1] = %s\n", i, i, ft_enum_to_str((*box)->dict_red_index_type[i][1]));
        if ((*box)->dict_red_index_type[i][1] == HEREDOC || (*box)->dict_red_index_type[i][1] == OUTFILE_APPEND) //Hay que marcar 2 posiciones como 'N'
        {
            //printf("barruan\n");
            current_ind_in_substr = (*box)->dict_red_index_type[i][0];
            (*box)->what_to_take[current_ind_in_substr] = 'R';
            (*box)->what_to_take[current_ind_in_substr + 1] = 'R';
            //printf("done\n");
        }
        else if((*box)->dict_red_index_type[i][1] == INFILE || (*box)->dict_red_index_type[i][1] == OUTFILE_STRONG) //Hay que marcar 1 posición como 'N'
        {
            current_ind_in_substr = (*box)->dict_red_index_type[i][0];
            (*box)->what_to_take[current_ind_in_substr] = 'R';
        }
        i++;
        tmp_nb_of_redir--;
        //printf("result: i = %d, tmp_nb_of_redir = %d\n", i, tmp_nb_of_redir);
    }
    //printf(GREEN"END mark_redir\n"RESET_COLOR);
}

void mark_word_2(int start, int end, t_box **box)
{
    int len_word;

    len_word = 0;
    //printf("mark_word_2: start = %d, end = %d\n", start, end);
    //while (ft_isspace((*box)->input_substr[start]) && start <= end)
    while (!possible_cases(box, start) && start <=end)
    {
        //printf("Before, start: %d\n", start);
        start++;
        //printf("After, start = %d\n", start);
    }
    //while(!ft_isspace((*box)->input_substr[start]) && start <= end)
    while (possible_cases(box, start) && start <= end)
    {
        //printf("asignar 'W', posición %d\n", start);
        (*box)->what_to_take[start] = 'W';
        start++;
        len_word++;
        //printf("yes\n");
    }
    //printf("      mark_word_2: "GREEN"DONE!\n"RESET_COLOR);
}

void mark_word(t_box **box)
{
    int tmp_nb_of_redir;
    int i;

    //printf("     mark_word\n");
    tmp_nb_of_redir = (*box)->nb_of_redir;
    i = 0;
    while (tmp_nb_of_redir > 0)
    {
        //printf("          redir n.º "MAGENTA"%d"RESET_COLOR" en dict_quotes de "MAGENTA"%d"RESET_COLOR" en total\n", i + 1, (*box)->nb_of_redir);
        //printf("          dict_redir_ind_type[%d] = %d\n", i, (*box)->dict_red_index_type[i][0]);
        if (is_last_redir_2(box, i)) //start: posición de redirección (+1 o +2), end: ft_strlen
        {
            //printf(GREEN"sí es última redirección. Particularmente:\n"RESET_COLOR);
            if ((*box)->dict_red_index_type[i][1] == HEREDOC || (*box)->dict_red_index_type[i][1] == OUTFILE_APPEND) //start: +2
            {
                //printf("   es HEREDOC o OUTFILE_APPEND\n");
                mark_word_2((*box)->dict_red_index_type[i][0] + 2, ft_strlen((*box)->input_substr) - 1, box);
            }
            else if (((*box)->dict_red_index_type[i][1] == INFILE || (*box)->dict_red_index_type[i][1] == OUTFILE_STRONG)) //start: +1
            {   
                //printf("   es INFILE o OUTFILE_STRONG\n");
                mark_word_2((*box)->dict_red_index_type[i][0] + 1, ft_strlen((*box)->input_substr) - 1, box);
                //printf("amaitxuta\n");
            }
            //printf(">listo\n");
            break;        
        }
        else //start: posición de redirección (+1 o +2), end: posición next redirección
        {
            //printf(RED"no es última redirección. Particularmente:\n"RESET_COLOR);
            if ((*box)->dict_red_index_type[i][1] == HEREDOC || (*box)->dict_red_index_type[i][1] == OUTFILE_APPEND) //start: +2
            {
                //printf("   es HEREDOC o OUTFILE_APPEND\n");
                mark_word_2((*box)->dict_red_index_type[i][0] + 2, (*box)->dict_red_index_type[i + 1][0] - 1, box);
            }
            else if (((*box)->dict_red_index_type[i][1] == INFILE || (*box)->dict_red_index_type[i][1] == OUTFILE_STRONG)) //start: +1
            {
                //printf("   es INFILE o OUTFILE_STRONG\n");
                mark_word_2((*box)->dict_red_index_type[i][0] + 1, (*box)->dict_red_index_type[i + 1][0] - 1, box);
                //printf("listo\n");
            }            
        }
        //printf(">>yes\n");
        tmp_nb_of_redir--;
        i++;
    }
    //printf("mark_word: "GREEN"DONE!\n"RESET_COLOR);
    //printf("hellohello\n");
    //mandar start_end
        //marcar word y volver al próximo
}

/*is_last_redir_2
*
*   Compares nb_of_redirs with nb_redir_x.
*
*   Returns:
*       1: YES is last redirección
*       0: NO still more redirecciones in input_substr
*/
int is_last_redir_2(t_box **box, int nb_redir_x)
{
   // int tmp_nb_of_redir;

    //tmp_nb_of_redir = (*box)->nb_of_redir;
    //(void)box;
    //printf("     is_last_redir_2\n");
    //printf("     REDIR actual = posición: %d\n", ind_redir_in_substr);
    //printf("     REDIR actual = posición: %d, tipo: %s\n", ind_redir_in_substr, ft_enum_to_str((*box)->dict_red_index_type[nb_redir_x][1]));
    //printf("     REDIR actual = posición: %d, tipo: %s\n", ind_redir_in_substr, ft_enum_to_str((*box)->dict_red_index_type[ind_redir_in_substr][1]));
    //printf("     nb_of_redir = %d\n", tmp_nb_of_redir);
    if (nb_redir_x + 1 == (*box)->nb_of_redir)
    {
        //printf(GREEN"yes is last redir\n"RESET_COLOR);
        return (1);
    }
    //printf(RED"NO still more redirs\n"RESET_COLOR);
    return (0);
}