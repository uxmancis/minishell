/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:01:00 by uxmancis          #+#    #+#             */
/*   Updated: 2024/04/14 10:15:14 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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

int main(void)
{
    ft_quotes_ok("uxue ' baiezba");
    return (0);
}