/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:28:44 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/08/12 14:31:07 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl
{
	int		i;
	size_t	len1;
	size_t	len2;
	size_t	y;
}	t_gnl;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;
int		ft_atoi(const char *c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	ft_bzero(void *s, int n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isdigit(int c);
void	*ft_memchr(const void *s, int c, int n);
int		ft_memcmp(const void *ptr1, const void *ptr2, int n);
char	*ft_memcpy(void *dest, const void *src, int n);
void	*ft_memset(void *s, int c, int n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
int		ft_strlen(const char *s);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, int n);
size_t	ft_strlcat(char *dest, const char *src, size_t n);
void	*ft_memmove(void *dest, const void *src, int n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
void	*ft_calloc(size_t nelem, size_t n_size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	ft_putchar_fd(char c, int fd);
char	ft_putstr_fd(char *s, int fd);
char	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
char	**ft_split(char const *s, char c);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
////////////////////////////////////////////////////////////
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strchr_gnl(char *s, int c);
char	*ft_read(int fd, char *s);
char	*ft_line(char *save);
char	*ft_save_data(char *save);
char	*ft_read_data(int fd, char *save, char *buff);
char	*ft_just_malloc(char *s1);

#endif
