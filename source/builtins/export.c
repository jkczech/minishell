/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:23:44 by jseidere          #+#    #+#             */
/*   Updated: 2024/03/25 17:16:31 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Before char
int strlen_before_char(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return (i);
}

//Find variable in environment
char	*find_env_var(t_shell *shell, char *var)
{
    t_list	*tmp;
    char	*tmp_var;
    int		i;

    i = 0;
    tmp = shell->env_list;
    while (tmp)
    {
        tmp_var = tmp->content;
        if (ft_strncmp(tmp_var, var, ft_strlen(var)) == 0)
            return (tmp_var);
        tmp = tmp->next;
    }
    return (NULL);
}

//create new environment variable
t_list	*ft_envnew_l(void *content)
{
	t_list	*list;
    
	if (!content)
		return (0);
	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (0);
	list->content = ft_strdup(content);
    if(!list->content)
    {
        free(list);
        return (0);
    }
	list->next = NULL;
	return (list);
}

//Add environment variable
void add_env_var(t_shell *shell, char *arg)
{
    t_list	*node;

    node = ft_envnew_l(arg);
    if (!node)
    {
        shell->exitcode = 1;
        return ;
    }
    ft_lstadd_back(&shell->env_list, node);
}

//Export command
void    export_command(t_shell *shell, t_cmd *cmd)
{
    int len;
    t_list *tmp;
    
    if(!cmd->args[1])
    {
        shell->exitcode = 0;
        return ;
    }
    len = strlen_before_char(cmd->args[1], '=');
    tmp = shell->env_list;
    while(tmp)
    {
        if(ft_strncmp(tmp->content, cmd->args[1], len) == 0)
        {
            free(tmp->content);
            tmp->content = ft_strdup(cmd->args[1]);
            shell->exitcode = 0;
            return ;
        }
        tmp = tmp->next;
    }
        add_env_var(shell, cmd->args[1]);
    shell->exitcode = 0;
}

//Handle export with no arguments