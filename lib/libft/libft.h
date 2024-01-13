/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:31:58 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/13 13:32:07 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# define HEXA_LOW "0123456789abcdef"
# define HEXA_UP "0123456789ABCDEF"

typedef struct s_env_var
{
	char				*content;
	struct s_env_var	*next;
	struct s_env_var	*previous;
}	t_env_var;

//	Part 1 - Libc functions
int			ft_atoi(const char *nptr);
int			ft_isalnum(unsigned char c);
int			ft_isalpha(unsigned char c);
int			ft_isascii(unsigned char c);
int			ft_isdigit(unsigned char c);
int			ft_isspace(char c);
int			ft_isprint(unsigned char c);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strncat(char *s1, char *s2, size_t n);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

//	Part 2 - Additional functions
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *str);

//	Part 3 - Bonus Functions
t_env_var	*ft_lstnew(void *content);
void		ft_lstadd_front(t_env_var **lst, t_env_var *new_lst);
int			ft_lstsize(t_env_var *lst);
t_env_var	*ft_lstlast(t_env_var *lst);
void		ft_lstadd_back(t_env_var **lst, t_env_var *new_lst);
void		ft_lstdelone(t_env_var *lst, void (*del)(void*));
void		ft_lstclear(t_env_var **lst, void (*del)(void*));
void		ft_lstiter(t_env_var *lst, void (*f)(void *));
t_env_var	*ft_lstmap(t_env_var *lst, void *(*f)(void *), void (*del)(void *));

// get_next_line
char		*get_next_line(int fd);
char		*ft_cleaner(char *str);
int			nlcheck(char *str);
char		*splitter(char *save);
char		*ft_strjoin_gnl(char *dest, char *src, int toread);
void		saver(char *content, char *save);
char		*stringbuilder(char *content, int toread, int fd);

//	Printf
int			ft_printf(const char *str, ...);
void		ft_param(va_list *arg, char type, int *len);
void		ft_putchar(char c, int *len);
void		ft_putstr(char *str, int *len);
void		ft_putnbr(long int nbr, int *len);
void		ft_putnbrhexa(unsigned int nbr, int *len, int lowup);
void		ft_putunsigned(unsigned int nbr, int *len);
void		ft_adress(unsigned long int ad, int *len);

//	Extra Functions

void		matrix_deleter(char ***mtx);
char		*ft_strjoin_free(char const *s1, char const *s2, int tofree);

#endif