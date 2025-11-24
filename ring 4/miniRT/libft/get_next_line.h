/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:42:49 by coraline          #+#    #+#             */
/*   Updated: 2025/11/24 14:47:52 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char			*get_next_line(int fd);
unsigned int	ft_len_line(const char *str, char c);
char			*ft_gnl_strjoin(char *s1, char *s2);
char			*ft_gnl_strchr(const char *s, int c);
char			*extract_line(char *buffer, char c);
unsigned int	ft_gnl_strlen(const char *str);

#endif