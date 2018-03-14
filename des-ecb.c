#include "lib-des.h"

char	*transBit(char *sfb, int a)
{
	char *binary;
	int x;
	int b;
	int c;

	binary = (char*)malloc(sizeof(char) * 65);
	b = 0;
	c = 0;
	while (c < 8)
	{
		x = 0;
		while (x < 8)
		{
			binary[b] = ((128 >> x) & sfb[c]) ? '1' : '0';
			if (c >= a)
				binary[b] = '0';
			//printf("-%c-\n", binary[b]);
			x++;
			b++;
		}
		c++;
	}
	binary[b] = '\0';
	printf("[%s] binary\n", binary);
	return binary;
}
char *apply_perm(char *pre, int *perm, int l)
{
	char *post;
	int i;

	i = 0;
	post = (char*)malloc(sizeof(char) * l + 1);
	while (i < l)
	{
		post[i] = pre[perm[i] - 1];
		i++;
	}
	post[i] = '\0';
	return post;
}

void	desEncode(char *binary)
{
	// char initial[65];
	// int i;
	//
	// i = 0;
	// while (i < 64)
	// {
	// 	initial[i] = binary[initial_perm[i] - 1];
	// 	i++;
	// }
	// initial[i] = '\0';
	char *initial;
	initial = apply_perm(initial, initial_perm, 64);
	printf("[%s] initial\n", initial);
}

void	plainSort(char *plain)
{
	char sfb[9];
	int i;
	int j;
	int l;
	char *binary;

	j = 0;
	l = strlen(plain);
	printf("[%s] plain [%d]\n", plain, l);
	while (j < strlen(plain))
	{
		i = 0;
		if (l > 8)
			l = l - 8;
		while (i < 8 && i < l)
		{
			if (j < strlen(plain))
				sfb[i] = plain[j];
			i++;
			j++;
		}
		sfb[i] = '\0';
		printf("[%s] [%d]\n", sfb, j);
		binary = transBit(sfb, l);
		desEncode(binary);
		bzero(sfb, 8);
	}
}

int	main(int ac, char **av)
{
	char *key64;
	char **key16;

	key64 = hex2char(av[2]);
	key16 = makeKeys(key64);
	plainSort(av[1]);
	return 1;

}
