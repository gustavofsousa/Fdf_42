/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:04:40 by gusousa           #+#    #+#             */
/*   Updated: 2022/08/29 12:05:20 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		ft_strlen_g(char *str, int *end_flag);
char	*ft_calloc_g(size_t n_elements, size_t size);
char	*ft_strdup_g(char *src, int len_stash);
void	move_remains(char *str, int pos);
char	*ft_append(char *line, char *s2, int len_stash);
char	*divide_et_vince(int fd, char *line, char *stash);
char	*get_next_line(int fd);
void	ft_strlcpy_g(char *dst, char *src, int size);

#endif
