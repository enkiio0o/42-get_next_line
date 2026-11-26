#include "get_next_line.h"

char *read_loop(int fd, char *line_save, char *buf_read)
{
    int read_bytes;

    read_bytes = 1;
    while (read_bytes > 0)
    {
        read_bytes = read(fd, buf_read, BUFFER_SIZE);
        if (read_bytes == -1)
        {
            free(line_save);
            return (NULL);
        }
        buf_read[read_bytes] = 0;
        if (read_bytes == 0)
            break;
        line_save = gnl_join_free(line_save, buf_read);
        if (!line_save)
            return (NULL);
        if ((gnl_strchr(line_save, '\n') >= 0))
            break;
    }
    return (line_save);
}

char    *read_line(int fd, char *line_save)
{
    char *buf_read;

    if (!line_save)
    {
        line_save = gnl_calloc(1, 1);
        if (!line_save)
            return (NULL);
    }
    buf_read = malloc(BUFFER_SIZE + 1);
    if (!buf_read)
    {
        free(line_save);
        return (NULL);
    }
    line_save = read_loop(fd, line_save, buf_read);
    free(buf_read);
    if (line_save && !*line_save)      // ← NEU: leerer String nach EOF → NULL
    {
        free(line_save);
        return (NULL);
    }
    return (line_save);    
}

char    *get_line(char *rtn_line)
{
    char    *temp_line;
    int     position;
    int     i;
    
    if (!rtn_line)
        return (NULL);
    position = 0;
    while (rtn_line[position] && rtn_line[position] != '\n')
        position++;
    if (rtn_line[position] == '\n')
        position++;
    temp_line = malloc(position + 1);
    if (!temp_line)
        return (NULL);
    i = 0;
    while (i < position)
    {
        temp_line[i] = rtn_line[i];
        i++;
    }
    temp_line[i] = '\0';
    return (temp_line);
}

char *update_rest(char *rest_buf)
{
    char *temp;
    int   position;
    int   i;

    position = 0;
    while (rest_buf[position] && rest_buf[position] != '\n')
        position++;
    if (rest_buf[position] == '\n')
        position++;
    temp = malloc(gnl_strlen(rest_buf + position) + 1);
    if (!temp)
    {
        free(rest_buf);
        return (NULL);
    }
    i = 0;
    while (rest_buf[position])
        temp[i++] = rest_buf[position++];
    temp[i] = '\0';
    free(rest_buf);
    return (temp);
}

char    *get_next_line(int fd)
{
    static char     *rest_line;
    char            *out_line;

    if (BUFFER_SIZE == 0 || fd < 0)
        return (NULL);
    rest_line = read_line(fd, rest_line);
    if (!rest_line)
        return (NULL);
    out_line = get_line(rest_line);
    if (!out_line)
    {
        free(rest_line);
        rest_line = NULL;
        return (NULL);
    }
    rest_line = update_rest(rest_line);
    if (!rest_line)
    {
        free(out_line);
        return (NULL);
    }
    if (!*rest_line)
    {
        free(rest_line);
        rest_line = NULL;
    }
    return (out_line);
}
