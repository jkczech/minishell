/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:42:17 by jseidere          #+#    #+#             */
/*   Updated: 2024/02/22 16:37:39 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool ft_is_word(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != ' ')
    {
        /* if(str[i] == ' ' && ft_isalpha(str[i + 1]))
            i++; */
        if (!ft_isalpha(str[i]))
            return (false);
        i++;
    }
    return (true);
}

char *ft_detect_string(char *str)
{
    int strlen;
    int i;
    char *result;

    strlen = 0;
    i = 0;
    while(!ft_is_seperator(str[strlen]))
        strlen++;
    if(!str)
        return (NULL);
    result = malloc(strlen + 1);
    
    while(i < strlen)
    {
        result[i] = str[i];
        i++;
    }
    result[i] = '\0';
    return (result);
}


/* int ft_detect_operator(char *str)
{
    int i;

    i = 0;

    while(str[i] && str[i] != ' ')
    {
        if(str[i] == '|')
            return (PIPE);
        else if(str[i] == ';')
            return (SEMICOLON);
        else if(str[i] == '<' && str[i + 1] == '<')
            return (HEREDOC);
        else if(str[i] == '>')
            return (REDIR_OUT);
        else if(str[i] == '<')
            return (REDIR_IN);
        else if(str[i] == '&')
            return (AMPERSAND);
        i++;
    }
    return (END);
} */

/* int ft_detect_operator(char c, char d)
{
    if(c == '|' && !d)
        return (PIPE);
    else if(c == ';')
        return (SEMICOLON);
    else if(c == '<' && d == '<')
        return (HEREDOC);
    else if(c == '>')
        return (REDIR_OUT);
    else if(c == '<')
        return (REDIR_IN);
    else if(c == '&')
        return (AMPERSAND);
 
    return (END);
} */

/* int main(int argc, char **argv)
{
    int i;

    i = 1;

    if(argc < 2)
    {
        printf("Error: wrong number of arguments\n");
        return (1);
    }
    else
    {
        while (argv[i])
        {
            if(ft_is_word(argv[i]))
                printf("WORD\n");
            else if(ft_detect_operator(argv[i]) == PIPE)
                printf("PIPE\n");
            else if(ft_detect_operator(argv[i]) == SEMICOLON)
                printf("SEMICOLON\n");
            else if(ft_detect_operator(argv[i]) == REDIR_IN)
                printf("REDIR_IN\n");
            else if(ft_detect_operator(argv[i]) == REDIR_OUT)
                printf("REDIR_OUT\n");
            else if(ft_detect_operator(argv[i]) == AMPERSAND)
                printf("AMPERSAND\n");
            else if(ft_detect_operator(argv[i]) == HEREDOC)
                printf("HEREDOC\n");
            else
                printf("ERROR\n");
            i++;
        }
    }
}  */