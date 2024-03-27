/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:54:05 by jkoupy            #+#    #+#             */
/*   Updated: 2024/03/27 14:30:17 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//finds a variable in the environment
bool find_variable(t_shell *shell, char *str)
{
    t_list	*node;
    char	*var;
    int		i;

    node = shell->env_list;
    printf("str: %s\n", str);
    while (node)
    {
        i = 0;
        var = node->content;
        while (var[i] != '=')
            i++;
        if (ft_strncmp(var, str, i) == 0)
            return (true);
        node = node->next;
    }
    return (false);
}

//gets the value of a variable in the environment
char *get_env_value(t_shell *shell, char *str)
{
    t_list	*node;
    char	*var;
    char    *value;
    int		i;
    int    j = 0;

    node = shell->env_list;
    while (node)
    {
        i = 0;
        var = node->content;
        while (var[i] != '=')
            i++;
        if (ft_strncmp(var, str, i) == 0)
        {
            value = ft_strdup(var + i + 1);
            return (value);
        }
        j++;
        node = node->next;
    }
    return (NULL);
}

bool is_expansion (t_shell *shell, char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        // if (/* str[i] == '$' &&  */find_variable(shell, str))
        //     return (true);
        if(str[i] == '$')
        {
        if (/* str[i] == '$' &&  */find_variable(shell, str + i + 1))
            return (true);
        else
            return (false);
        }
        i++;
    }
    return (false);
}

void expander(t_shell *shell)
{
    char *tmp;
    t_token *token;

    token = *shell->tokens;
    while (token)
    {
        tmp = token->content;
        if (is_expansion(shell, tmp))
        {
            token->content = get_env_value(shell, tmp + 1);
            free(tmp);
        }
        token = token->next;
    }
}

//check if $ is followed by a valid variable
//go through tokens and expand variables
//if variable is not found, leave it as is
//if variable is found, replace it with its value
//