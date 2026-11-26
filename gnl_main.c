#include "get_next_line.h"

int main(int argc, char **argv)
{
    char    *line;
    int     fd;

    setbuf(stdout, NULL);
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        return (1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("[%s]\n", line);
        free(line);
    }
    close(fd);
    return (0);
}