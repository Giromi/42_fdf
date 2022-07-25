/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:02:34 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/22 22:42:43 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlen_chr_init(const char *s, int c, size_t *len, int init)
{
	size_t	i;

	if (!init)
		*len = 0;
	while (s[*len])
		(*len)++;
	i = 0;
	while (c && i < *len)
		if (s[i++] == (char)c)
			return ((char *)s + (i - 1));
	return (NULL);
}

size_t	ft_strlcat_dstlen(char *dst, size_t dst_len, char const *src,
		size_t dstsize)
{
	size_t	src_len;

	ft_strlen_chr_init(src, 0, &src_len, 0);
	if (dst_len + 1 > dstsize)
		return (src_len + dstsize);
	if (dst_len + src_len + 1 < dstsize)
		dstsize = src_len + dst_len + 1;
	dst[dstsize - 1] = '\0';
	while (dstsize-- - 1 > dst_len)
		dst[dstsize - 1] = src[dstsize - dst_len - 1];
	return (dst_len + src_len);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	if (!s1)
		return (NULL);
	ft_strlen_chr_init(s1, 0, &len, 0);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	ft_strlcat_dstlen(dup, 0, s1, len + 1);
	return (dup);
}

t_list	*ft_lstadd_back_last(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return (NULL);
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

t_list	*ft_lstnew_str(char *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
