/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   probatxuek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:01:00 by uxmancis          #+#    #+#             */
/*   Updated: 2024/04/16 21:13:13 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

static int	ft_quotes_ok(char *str)
{
	int	single_quote;
	int	double_quote;
    int i; //uxue

	single_quote = 0;
	double_quote = 0;
    i = 0;
	while (*str != '\0')
	{
		if (*str == '\'')
		{
            printf("comilla SIMPLE en str[%d] = %c\n", i, *str);
			if (!double_quote)
				single_quote = !single_quote;
		}
		else if (*str == '\"')
		{
            printf("comilla DOBLE en str[%d]\n", i);
			if (!single_quote)
				double_quote = !double_quote;
		}
		str++;
        i++;
	}
	if (single_quote == 0 && double_quote == 0)
		return (1);
	return (0);
}

/*int main(void)
{
    ft_quotes_ok("uxue ' baiezba");
    return (0);
}*/

/*typedef struct s_prompt
{
    int are_there_pipes; //-1: no pipe, >0:number of pipes
}   t_prompt;

void ft_update_2(t_prompt *prompt)
{
	prompt->are_there_pipes = 9;
	printf("ft_update2, result = %d\n", prompt->are_there_pipes);
}

void ft_update_1(t_prompt *prompt)
{
	prompt->are_there_pipes = 8;
	printf("ft_update1, result = %d\n", prompt->are_there_pipes);
	ft_update_2(prompt);
	printf("ft_update1 - 2.a, result = %d\n", prompt->are_there_pipes);
}

int main(void)
{
	t_prompt prompt;
	
	prompt.are_there_pipes = 7;
	ft_update_1(&prompt);
	printf("result = %d\n", prompt.are_there_pipes);
}*/

int main(void)
{
	execve()
}
