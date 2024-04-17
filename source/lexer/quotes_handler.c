/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakob <jakob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:17:20 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/17 14:27:12 by jakob            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//checks if amount of quotes is even
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
			q = str[i++];
			q_closed = false;
		}
		while (str[i + 1] && str[i] != q)
			i++;
		if (q && ft_strncmp(&str[i], &q, 1) == 0)
			q_closed = true;
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

// removes quotes from a string
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;
	char	q;
	bool	q_closed;

	init_variables(&i, &j, &q, &q_closed);
	new_str = (char *)malloc(sizeof(char) * len_w_q(str) + 1);
	if (!new_str)
		return (NULL);
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
			new_str[j++] = str[i++];
		}
		refresh_quote(str, &i, &q, &q_closed);
	}
	new_str[j] = '\0';
	return (new_str);
}

//parse token
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
