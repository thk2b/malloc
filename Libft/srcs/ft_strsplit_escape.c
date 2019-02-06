/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_escape.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 21:00:30 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/27 00:21:14 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*alloc_str(const char *start, const char *end)
{
	char	*s;
	size_t	len;

	len = (end - start);
	if ((s = (char*)malloc((len + 1) * sizeof(char))) == NULL)
		return (NULL);
	ft_memcpy(s, start, len);
	s[len] = '\0';
	return (s);
}

static char		**alloc_splits(const char *s, char c, const char *escape)
{
	size_t	count;
	int		escaping;

	count = 1;
	escaping = 0;
	if (ft_strchr(escape, *s))
	{
		escaping = 1;
		s++;
	}
	if (*s == c)
		s++;
	while (*s)
	{
		if (ft_strchr(escape, *s))
		{
			if (!escaping)
				count++;
			escaping = !escaping;
		}
		else if (!escaping && *s == c && *s && s[1] != c)
			count++;
		s++;
	}
	return ((char**)malloc((count + 1) * sizeof(char*)));
}

void			split(const char *s, char **strv, char c, const char *escape)
{
	const char	*t;
	const char	*e;
	size_t		i;

	i = 0;
	while (s && *s)
	{
		if ((e = ft_strchr(escape, *s)) && ++s)
		{
			t = ft_strchr(s, (int)*e);
			strv[i++] = alloc_str(s, t ? t++ : s + ft_strlen(s));
		}
		else if ((t = ft_strchr(s, (int)c)) == NULL)
			strv[i++] = alloc_str(s, s + ft_strlen(s));
		else
		{
			if (t != s)
				strv[i++] = alloc_str(s, t);
			while (*t && *t == c)
				t++;
		}
		s = t;
	}
	strv[i] = NULL;
}

char			**ft_strsplit_escape(const char *s, char c, const char *escape)
{
	char		**strv;

	if ((strv = alloc_splits(s, c, escape)) == NULL)
		return (NULL);
	split(s, strv, c, escape);
	return (strv);
}
