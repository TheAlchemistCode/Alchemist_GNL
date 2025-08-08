#include "get_next_line.h"

static char *_01_stash_builder(int fd, char *stash, char *buffer);
static char *_02_stash_trunc(char *work_line);
static char *_03_ft_strchr(char *s, int c);

/* combines buffer and stash... but what happens if buffer size is too small... how are characters added to work_line until the first string is complete*/
static char *_01_stash_builder(int fd, char *stash, char *buffer)
{
   ssize_t  b_read;
   char *tmp;

   b_read = 1;
   while (b_read > 0)
   {
    b_read = read(fd, buffer, BUFFER_SIZE);
    if (b_read == -1)
    { 
        free(stash);
        return(NULL);
    }
    else if (b_read == 0)
    break;
    buffer[b_read] = 0;
    if (!stash)
        stash = ft_strdup("");
    tmp = stash;

    stash = ft_strjoin(tmp, buffer); //This is where the magic happens and behind strjoin we have - malloc(strlen(stash) + strlen(buffer) + 1); to allocate enough mem as stash is built.
    free(tmp);
    tmp = NULL; // combines what the buffer and the stash

    if (_03_ft_strchr(buffer, '\n')) // returns a char * in the first occurrence of \n
        break ;
   }
   return (stash);
}

/*The purpose of this function is to "stash" the remaining string found after "\n" */
static char *_02_stash_trunc(char *work_line)
{
    char    *stash;
    ssize_t i = 0;

    // 1. Find newline or end-of-string
    while (work_line[i] && work_line[i] != '\n')
        i++;

    // 2. If no leftover after this line, return NULL
    if (work_line[i] == '\0' || work_line[i + 1] == '\0')
        return (NULL);

    // 3. Allocate stash for leftover part
    stash = ft_substr(work_line, i + 1, ft_strlen(work_line) - (i + 1));
    if (!*stash) // if empty string
    {
        free(stash);
        stash = NULL;
    }

    // 4. Truncate work_line after the newline to form the line to return
    work_line[i + 1] = '\0';

    return (stash); // returns "world" or the part after the \n or NULL if there was nothing left (see 10 lines up)
}

static char	*_03_ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (cc == '\0')
		return ((char *) &s[i]); // point to the null terminator itself
	return (NULL);
}

/* this returns only one string per call, until newline or EOF*/
char    *get_next_line_(int fd)
{
    static char *stash;
    char        *work_line;
    char        *buffer;

    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return(NULL);

    /* Error checks */
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
    {
        free(stash);
        free(buffer);
        stash = NULL;
        buffer = NULL;
        return (NULL);
    }

    work_line = _01_stash_builder(fd, stash, buffer);
    free(buffer);
    buffer = NULL;
    if (!work_line)
        return (NULL);
    stash = _02_stash_trunc(work_line);
    return (work_line);
}


