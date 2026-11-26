#include "get_next_line.h"

void    gnl_bzero(void *s, size_t n_elem)
{
    char    *str;
    size_t     i;

    str = (char *)s;
    i = 0;
    while(i < n_elem)
    {
        str[i] = '\0';
        i++;
    }
}

void    *gnl_calloc(size_t n_elements,size_t n_bytes)
{
    char    *mem;

    mem = malloc(n_elements * n_bytes);
    if (mem == NULL)
        return (NULL);
    gnl_bzero(mem, n_elements * n_bytes);
    return (mem);
}

int gnl_strlen(char *string)
{
    int i;

    if (!string)
        return (0);
    i = 0;
    while (string[i] != '\0')
        i++;
    return (i);
}

int gnl_strchr(char *string, char searched_char)
{
    int i;

    i = 0;
    if (!string)
        return (-1);
    while (string[i] != '\0')
    {
        if (string[i] == searched_char)
            return (i);
        i++;
    }
    return (-1);
}

char    *gnl_join_free(char *saved_line, char *buff_read)
{
    char	*joined;
	int		i;
	int		j;

	joined = malloc(gnl_strlen(saved_line) + gnl_strlen(buff_read) + 1);
	if (!joined)
    {
        free(saved_line);
		return (NULL);
    }
    i = 0;
	while (saved_line[i])
	{
		joined[i] = saved_line[i];
		i++;
	}
	j = 0;
	while (buff_read[j])
		joined[i++] = buff_read[j++];
	joined[i] = '\0';
    free(saved_line);
	return (joined);
}