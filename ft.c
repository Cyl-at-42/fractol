#include "fractol.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*s2;
	unsigned long long	*s4;
	unsigned long long	*c_repeated8x;
	unsigned long long	count;

	s2 = (unsigned char *)s;
	if (n >= 15)
	{
		count = 8 + ((8 - ((unsigned long long)s2 & 7)) & 7);
		while (count--)
			*s2++ = (unsigned char)c;
		c_repeated8x = (unsigned long long *)s2;
		s4 = c_repeated8x--;
		n -= (s2 - (unsigned char *)s);
		count = n >> 3;
		while (count--)
			*s4++ = *c_repeated8x;
		n -= ((unsigned char *)s4 - s2);
		s2 = (unsigned char *)s4;
	}
	while (n--)
		*s2++ = (unsigned char)c;
	return (s);
}

size_t	ft_strlen(const char *s)
{
	char	*s2;

	s2 = (char *) s;
	while (*s2++)
		;
	return (--s2 - s);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((*s1 || *s2) && i < n)
	{
		if (*((unsigned char *) s1) != *((unsigned char *) s2))
			return (*((unsigned char *) s1) - *((unsigned char *) s2));
		s1++;
		s2++;
		i++;
	}
	return (0);
}
