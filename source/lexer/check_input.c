/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:06:22 by jakob             #+#    #+#             */
/*   Updated: 2024/04/02 17:32:27 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//checks if a character is a separator
bool	is_sep(char c)
{
	int	i;

	i = 0;
	while (SEPARATOR[i])
	{
		if (SEPARATOR[i] == c)
			return (true);
		else
			i++;
	}
	return (false);
}

//checks if a character is a double separator
bool	double_sep(char *str, int i)
{
	if ((str[i] == '|' && str[i + 1] == '|')
		|| (str[i] == '&' && str[i + 1] == '&')
		|| (str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
		return (true);
	return (false);
}

bool is_qoute(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}
//checks if amount of quotes is even
bool	quotes_checker(char *str)
{
	int i;
	char q;
	bool q_closed;
	
	i = 0;
	q = 0;
	q_closed = true;
	while (str[i])
	{
		if (is_qoute(str[i]))
		{
			q_closed = false;
			q = str[i];
			i++;
		}
		while (str[i + 1] && str[i] != q)
			i++;
		if(q && ft_strncmp(&str[i], &q, 1) == 0)
			q_closed = true;
		i++;
	}
	return (q_closed);
}

//deletes quotes at the beginning and the end of a str
void	del_quotes(char **str)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(*str);
	printf("len: %d\n", len);
	tmp = (char *)malloc(sizeof(char) * (len - 1));
	if (!tmp)
		return ;
	while ((*str)[i + 1])
	{
		tmp[i] = (*str)[i + 1];
		i++;
	}
	tmp[i - 1] = '\0';
	free(*str);
	*str = tmp;
}


//string length without quotes
int len_w_q(char *str)
{
	int	i;
	int	len;
	char	q;

	i = 0;
	len = 0;
	while (str[i])
	{
		if(is_qoute(str[i]))
		{
			q = str[i];
			i++;
		}
		while(str[i] && str[i] != q)
		{
			len++;
			i++;
		}
		if(str[i] == q)
			i++;
	}
	return (len);
}

/* int which_quotes(char c)
{
	int q; 
	
	if(c == '"')
		q = D_QUOTE;
	else if(c == '\'')
		q = S_QUOTE;
	return (q);
} */

char *remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;
	char	q;
	bool	q_closed;
	
	i = 0;
	j = 0;
	q_closed = true;
	new_str = (char *)malloc(sizeof(char) * len_w_q(str) + 1);
	if(!new_str)
		return (NULL);
	while(str[i])
	{
		if (q_closed && is_qoute(str[i]))
		{
			q = str[i];
			q_closed = false;
			i++;
		}
		while(str[i] && str[i] != q)
			new_str[j++] = str[i++];
		if(str[i] == q && q_closed == false)
		{
			q_closed = true;
			i++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

//checks the input and saves it in a list of tokens
//if the input is invalid, returns false
bool	check_input(t_shell *shell)
{
	char *tmp = remove_quotes(shell->input);
	printf("\033[0;35mQuotes-rem: %s\n\033[0m", tmp);
	free(tmp);
	if (!quotes_checker(shell->input))
	{
		printf("Error: Quotes not closed\n");
		free_shell(shell);
		exit(1);
	}
	while (shell->input[0] == '"' && \
		shell->input[ft_strlen(shell->input) - 1] == '"')
	{
		del_quotes(&shell->input);
		if (!shell->input)
			return (false);
	}
	norm_input(shell, token_count(shell) - 1 + count_chars(shell));
	if (!shell->norm_input)
		return (false);
	return (true);
}
