/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 22:56:06 by kblack            #+#    #+#             */
/*   Updated: 2018/09/23 00:39:51 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
//#include "libft/libft.h"
# include <stdlib.h>


#define BUFF_SIZE 9
#define GNL_ERROR -1
#define GNL_OKAY 1


typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}	t_list;

// struct node
// {
// 	//value??
// 	char *value;
// 	struct node *next;
// };

// //Read all contents of the file and print out the contents
// //"Learn how to use read()" ~ Casey

// int get_next_line(const int fd, char **line)
// {

// 	//check if fd is valid (returns -1 means error)
// 	if (fd == -1)
// 	{
// 		printf("INVALID\n");
// 		return (-1);
// 	}
// 	while (read(fd, line, 1) == 1)
// 	{
// 		printf("%c\n", line);
// 	}
// 	printf("I was here\n");
// 	//while loop
// 		//allocate memory
// 		//read line 
// 	//free memory
// 	return (1);
// }


size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void		ft_bzero(void *str, size_t n)
{
	unsigned char	*i;

	i = str;
	while (n-- > 0)
		*i++ = 0;
}

void		*ft_memalloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
		return (NULL);
	else
		ft_bzero(mem, size);
	return (mem);
}


void		*ft_memcpy(void *cpy, const void *src, size_t n)
{
	char	*strcpy;
	char	*strsrc;
	size_t	i;

	strcpy = (char *)cpy;
	strsrc = (char *)src;
	i = 0;
	while (i < n)
	{
		*strcpy++ = *strsrc++;
		i++;
	}
	return (cpy);
}

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		new->content = malloc(content_size);
		if (new->content == NULL)
			return (NULL);
		ft_memcpy((new->content), content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	joined = ft_memalloc(ft_strlen(s1) + strlen(s2) + 1);
	if (!joined)
		return (NULL);
	while (s1[i] != '\0')
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		joined[i] = s2[j];
		i++;
		j++;
	}
	joined[i] = '\0';
	return (joined);
}

void	ft_putstr(char const *s)
{
	if (!s)
		;
	while (*s != '\0')
		write(1, &*s++, 1);
}

char	*ft_strnew(size_t size)
{
	//make byte(s) equal to NULL
	char *ret;

	ret = (char *)ft_memalloc(sizeof(char) * (size + 1));
	ft_bzero(ret, size +1);
	return(ret);
}


//CREATE REALLOC FUNCTION??

//the 2nd parameter is the address of a pointer to a character that
//will be used to save the line read from the file descriptor 
int get_next_line(const int fd, char **line)
{
	int n;
	t_list *file;
	char buf[BUFF_SIZE + 1];
	char *holder;

	//line is a pointer to a pointer 
	if (fd < 0 || !line)
		return (GNL_ERROR);

	bzero(buf, BUFF_SIZE + 1);
	file = ft_lstnew(NULL, 0); //making a string
	file->content = ft_strnew(0);
	while ((n = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[n] = '\0';
		holder = ft_strjoin((char *)file->content, buf);
		printf("buf was joined to file: %s\n", holder);
		free(file->content);
		printf("file is freed\n");
		file->content = holder;
		printf("holder is assigned to file: %s\n", file->content);
		if (strchr(buf, '\n'))
		{
			printf("strchr found a newline.\n" );
			break;
		}
		printf("strchr did not find a newline and returns to beginning of while loop\n");
	}

	printf("content =>%s\n", file->content);

	return(1);
}

//ssize_t getline(char **lineptr, size_t *n, FILE *stream
//1. place in *lineptr the address of a buffer *n bytes long allocated with malloc
//2. if the buffer is long enough to hold the line, getline stores the line in this buffer
//otherwise, getline makes the buffer bigger using realloc
//storing the new buffer in *lineptr and the increased size back in *n
//if you set *lineptr to a null pointer and *n to zero before the call then getline call malloc 
//when getline returns *lineptr is a char* which points to the text of the line 
//returns the number of characters read (including the newline but not the terminating null)

/* 1. Fetch up to line_length bytes from the file, or up to a newline
 * 2. if the line was too long, and so doesn't contain a newline, carry on fetching until
 *    it does, or we hit the end of the file
 * 3. Create a new storage space the same size as the last one, and carry on reading 
 *    We'll need to append this to the previous string
 * 4. Don't include the newline in the line we return 
*/


//read(file descriptor, char array where data goes or comes from, num of bytes to be transferred)
//returns a count of the number of bytes transferred 
	//return of 0 bytes -> EOF
	//return of -1 -> error

//open(char *name, int flags, int perms)

//FLAGS
//<fcnt1.h> (sys v unix) <sys/file.h> (Berkeley BSD versions)
//O_RDONLY -> open for reading only 
//O_WRONLY -> open for writing only
//O_RDWR -> open for both reading and writing 

//PERMS
//perms argument is usually always 0 

int main (int argc, char **argv)
{
	char *buf[BUFF_SIZE];
	int fd;
	int result;

	if (argc < 2)
		printf("Error: too few arguments");
	if ((fd = open(argv[1], O_RDONLY, 0)) == -1)
		printf("Can't open -> %s", argv[1]);
	//printf("\nMain &buf -> %p", &buf);
	//printf("\nMain buf -> %p", buf);
	result = get_next_line(fd, buf);
	printf("\nRESULT => %d\n", result);
	return (0);
}


// int		main(int argc, char *argv[])
// {
// 		char	*line[90];
// 		int		fd;
// 		int		fd2;
// 		int		index;
// 		int		ret;

// 		line[0] = NULL;
// 		index = 0;
// 		ret = 0;

// 		if (argc != 2)
// 		{
// 			printf("usage: canopen");
// 		}
// 		// if (argc > 1)
// 		// {
// 		// 	fd = open(argv[1], O_WRONLY);
// 		// 	fd2 = open(argv[2], O_WRONLY);
// 		// 	ret = get_next_line(fd, &line[index]);
// 		// }
// 		printf("ret: %d\n", ret);
// 		return (0);
// }
