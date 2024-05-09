#include <stdio.h>
#include <stdbool.h>

bool	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

int substr_len(char *str, int i)
{
	int len;
	char q;

	len = 0;
    if (!str)
        return (0);
	if (is_quote(str[i]))
		q = str[i++];
	else
		q = '\0';
	while ((q && str[i] && str[i] != q) || \
			(!q && str[i] && !is_quote(str[i])))
	{
		len++;
		i++;
	}
	return (len);
}

//test main with user input loop
int main(void)
{
    char *str;
    int i;

    i = 0;
    str = NULL;
    while (1)
    {
        printf("Enter a string: ");
        scanf("%s", str);
        printf("%s\n", str);
        printf("Length of the substring: %d\n", substr_len(str, i));
    }
    return (0);
}