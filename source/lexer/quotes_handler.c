/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:17:20 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/10 15:32:29 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//checks if quote is open
bool	quotes_checker(char *str)
{
	int		i;
	char	q;
	bool	q_closed;

	i = 0;
	q = '\0';
	q_closed = true;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			if (q == '\0')
			{
				q = str[i];
				q_closed = false;
			}
			else if (str[i] == q)
			{
				q_closed = true;
				q = '\0';
			}
		}
		i++;
	}
	return (q_closed);
}

//string length without quotes
int	len_w_q(char *str)
{
	int		i;
	int		len;
	char	q;
	bool	q_closed;

	init_variables(&i, &len, &q, &q_closed);
	while (str && str[i])
	{
		determine_quote(str, &i, &q, &q_closed);
		while (str[i] && str[i] != q)
		{
			if (is_quote(str[i]) && !q)
			{
				q = str[i];
				break ;
			}
			len++;
			i++;
		}
		refresh_quote(str, &i, &q, &q_closed);
	}
	return (len);
}

//removes quotes from a token string
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;
	t_quote	quote;

	init_variables(&i, &j, &quote.type, &quote.q_closed);
	new_str = (char *)malloc(sizeof(char) * len_w_q(str) + 1);
	if (!new_str)
		return (NULL);
	while (str && str[i])
	{
		determine_quote(str, &i, &quote.type, &quote.q_closed);
		while (str[i] && str[i] != quote.type)
		{
			if (is_quote(str[i]) && !quote.type)
			{
				quote.type = str[i];
				break ;
			}
			new_str[j++] = str[i++];
		}
		refresh_quote(str, &i, &quote.type, &quote.q_closed);
	}
	new_str[j] = '\0';
	return (new_str);
}

//iterate through tokens and remove quotes for each token
void	quote_token(t_shell *shell)
{
	t_token	*head;
	char	*tmp;

	head = shell->tokens;
	while (head)
	{
		tmp = head->content;
		head->content = remove_quotes(tmp);
		free(tmp);
		head = head->next;
	}
}
