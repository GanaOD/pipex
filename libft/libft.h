/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:59:51 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/06 09:27:51 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// System headers
# include <ctype.h>
# include <limits.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

// Data structures
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// String functions
char	**ft_split(const char *str, char delim);
char	*ft_strchr(const char *src, int c);
char	*ft_strdup(const char *str_orig);
void	ft_striteri(char *str, void (*choose_a_function)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *source,
			char (*generic_function)(unsigned int, char));
int		ft_strncmp(const char *str1, const char *str2, size_t size);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *src, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *orig, unsigned int start, size_t len);

/* Memory functions */
void	ft_bzero(void *destination, size_t byte_count);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *memory, int search_byte, size_t num_bytes);
int		ft_memcmp(const void *m1, const void *m2, size_t size);
void	*ft_memcpy(void *destination, const void *source, size_t byte_count);
void	*ft_memmove(void *destination, const void *source, size_t length);
void	*ft_memset(void *destination, int fill_value, size_t byte_count);

/*Character test functions*/
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

/* Number conversion functions */
int		ft_atoi(const char *str);
char	*ft_itoa(int int_input);

/* File descriptor functions */
void	ft_putchar_fd(char c, int file_descriptor);
void	ft_putendl_fd(char *str, int fildes);
void	ft_putnbr_fd(int number, int filedescr);
void	ft_putstr_fd(char *str, int fildes);

/* Bonus: Linked list functions */
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);

// End guard
#endif
