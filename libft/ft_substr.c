/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:43:19 by mmahfoud          #+#    #+#             */
/*   Updated: 2023/11/16 09:47:17 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_s;
	size_t			i;
	size_t			len_tmp;

	if (!(s))
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup("\0"));
	if ((size_t)start + len > ft_strlen(s))
		len_tmp = ft_strlen(s) - start;
	if ((size_t)start + len <= ft_strlen(s))
		len_tmp = len;
	new_s = malloc(len_tmp + 1 * sizeof(char));
	if (!(new_s))
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
	{
		new_s[i] = s[start];
		i++;
		start++;
	}
	new_s[i] = '\0';
	return (new_s);
}
