#include "get_next_line.h"

char    *ft_strdup(char *s1)
{
    char			*dest;
	unsigned int	i;

	dest = (char *) malloc(ft_strlen(s1) + 1);
    if(!dest)
        return(NULL);
    i = 0;
    while(s1[i])
    {
        dest[i] = s1[i];
        i++;
    }
    dest[i] = 0;
    return (dest);
}

size_t  ft_strlen(char *s)
{
    size_t i;

    i = 0;
    while(s[i])
        i++;
    return(i)
}

char    *ft_substr(char *s, unsigned int start, size_t len)
{
    size_t  i;
    char    *str;

    if (!s)
        return (NULL);
    if (start > ft_strlen(s))
    {
        str = malloc(1);
        if (!str)
            return(NULL);
        str[0] = '\0';
        return (str);
    }
    if (len > strlen(s + start))
        len = strlen(s + start);
    str = malloc((len + 1) * sizeof(char));
    if (!str)
        return (NULL);
    i = 0;
    while (i < len)
    {
        str[i] // to be continued...
    }

}