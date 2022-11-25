#include <stdio.h>
int	ft_atohex(char *str, int len);

int	main(void)
{
	printf("%X\n", ft_atohex("0XFF14D3", 6));
}
