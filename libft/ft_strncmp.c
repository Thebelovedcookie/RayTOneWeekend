/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:32 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/06/19 10:47:25 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * DESCRIPTION
       The  strcmp()  function  compares the two strings s1 and s2.  
       The locale is not taken into ac‐
       count (for a locale-aware comparison, see strcoll(3)).  
       The comparison is done using  unsigned
       characters.

       The  strncmp()  function is similar, except it compares only the first 
       (at most) n bytes of s1 and s2.

       RETURN VALUE
       The strcmp() and strncmp() functions return an integer less than, equal 
       to,  or  greater  than zero  if  s1 (or the first n bytes thereof) is 
       found, respectively, to be less than, to match, or be greater than s2.

*/

#include <stdlib.h>
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
