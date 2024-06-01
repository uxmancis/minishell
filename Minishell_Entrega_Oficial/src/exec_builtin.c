/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:45:31 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/01 14:17:26 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*ft_strcmp_2
*
*   Returns:
*       1: yes str are exactly the same
*       0: not same str
*/
int ft_strcmp_2(char *str_2_check, char *cmd)
{
    int i;
    int len_str_2_check;
    int len_cmd;

    len_str_2_check = ft_strlen(str_2_check);
    len_cmd = ft_strlen(cmd);
    i = 0;
    if (len_str_2_check == len_cmd)
    {
        while (len_cmd > 0)
        {
            if (str_2_check[i] != cmd[i])
                return (0);
            i++;
            len_cmd--;
        }        
    }
    return (1);
}

void ft_putchar(char c)
{
    printf("%c", c);
}

void ft_putstr (char *str)
{
    printf("%s", str);
}


/* put_without_next_line
*
*   Used when e.g. echo -n hola (echo with no -n flag)
*   Prints: hola
*/
/*void put_without_next_line (t_box **box)
{
    int x;
    int y;

    x = 2;
    while ((*box)->rest_info_potential_cmd[x] != '\0')
    {
        y = 0;
        while ((*box)->rest_info_potential_cmd[x][y] != '\0')
        {
            ft_putchar((*box)->rest_info_potential_cmd[x][y]);
            y++;
        }
        x++;
    }
}*/

/* put_with_next_line
*
*   Used when e.g. echo hola (echo with no -n flag)
*   Prints: hola\n
*/
/*void put_with_next_line (t_box **box)
{
    int x;
    int y;

    x = 1;
    while ((*box)->rest_info_potential_cmd[x] != '\0')
    {
        y = 0;
        while ((*box)->rest_info_potential_cmd[x][y] != '\0')
        {
            ft_putchar((*box)->rest_info_potential_cmd[x][y]);
            y++;
        }
        x++;
    }
    ft_putchar("\n");
}*/

/*ft_builtin_echo
*
*   echo is a command required to build by 42 cursus Minishell project.
*
*   echo command displays a line of text in standard output.
*/
/*void ft_builtin_echo (t_box **box)
{
    if (ft_strcmp_2((*box)->rest_info_potential_cmd)[1], "-n")
        put_without_next_line(box);
    put_with_next_line(box);
}*/


/*ft_builtin_pwd
*
*   pwd is a command required to build by 42 cursus Minishell project.
*
*   pwd command prints the name of current/working directory.
*   Information is taken from environment. We've implemented it using
*   linked list.
*/
void ft_builtin_pwd(t_prompt **prompt)
{
    ft_putstr(ft_getenv_local((*prompt)->vars, "PWD")->val);
    //ft_putchar("\n");
    printf("\n");
}

/*which_cmd
*
*   Return is used as a way to finish function execution.
*/
int which_cmd(t_box **box, t_prompt **prompt)
{
    printf(RESET_COLOR"which_cmd\n");
    (void)prompt;
    //si no hay nada en esta variable, no tenemos que chequearlo
    //if (!(*box)->rest_info_potential_cmd)
    //if ((int)ft_strlen((*box)->rest_info_potential_cmd[1]) == 0)
    if ((*box)->nb_of_words_rest == 0)
        return (-1);
    if (!(*box)->rest_info_potential_cmd)
    {
        ft_putstr(": command not found\n");
        return (0);
    }
    //else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "echo"))
        //ft_builtin_echo(box);
    printf(YELLOW"HOLAAAAA \n %s", (*box)->rest_info_potential_cmd[0]);
    // else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "pwd"))
    //     ft_builtin_pwd(prompt);
    // // else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "cd"))
    // else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "exit"))
    // else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "unset"))
    // else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "export"))
    // else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "env"))
    // else
    // {
        // ft_putstr((*box)->rest_info_potential_cmd[0]);
        ft_putstr(": command not found\n");
    // }
    return (0);
}