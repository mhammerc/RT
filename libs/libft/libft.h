/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 18:13:57 by mhammerc          #+#    #+#             */
/*   Updated: 2017/03/23 17:16:37 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "string.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define IFNSET(p) if (!p) return
# define IFNSETN(p) if (!p) return (NULL)
# define IFNSETZ(p) if (!p) return (0)

# define BUFF_SIZE 32

typedef unsigned char	t_uchar;

/*
** Memory manipulation
*/
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memccpy(void *dest, const void *src, int c,
		size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memset(void *s, int c, size_t n);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);

/*
** Strings manipulation
*/
size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *s);
char					*ft_strndup(const char *s, size_t n);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strncpy(char *dest, const char *src, size_t n);
char					*ft_strcat(char *dest, const char *src);
char					*ft_strncat(char *dest, const char *src, size_t n);
size_t					ft_strlcat(char *dest, const char *src, size_t size);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strnstr(const char *big, const char *little,
		size_t len);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s,
		char (*f)(unsigned int, char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub(char const *s, unsigned int start,
		size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, char c);
int						ft_atoi(const char *nptr);
char					*ft_itoa(int n);

/*
** Characters manipulations
*/
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_isupper(int c);
int						ft_islower(int c);
int						ft_isspace(int c);
int						ft_ispunct(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);

/*
** Write functions
*/
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putbinary(size_t const size, void const *const ptr);

/*
** Lists management
*/
typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
	struct s_list		*children;
}						t_list;

t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_classicfree(void *content, size_t size);
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstpostadd(t_list **alst, t_list *new);
void					ft_lstpushback(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int						ft_lstcount(t_list *list);
t_list					*ft_lstat(t_list *list, size_t index);
t_list					*ft_lstat_child(t_list *list, int *index, int depth);
t_list					*ft_lstat_child_before(t_list *list, int *index,
		int depth);

/*
** Mathematics computing
*/
int						ft_sqrt(int n);
int						ft_pow(int n, int pow);

/*
** get_next_line
*/
typedef struct			s_reader
{
	size_t				position;
	size_t				available;
	char				text[BUFF_SIZE + 1];
}						t_reader;

int						ft_get_next_line(int const fd, char **line);

/*
** ft_printf
*/

int						ft_printf(char const *format, ...);
int						ft_sprintf(char **str, char const *format, ...);
int						ft_dprintf(int fd, char const *format, ...);

/*
** RT ADD
*/

void					ft_exit_fd(const char *message, int fd);
void					*monloc(size_t size);

#endif
