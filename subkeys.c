#include "lib-des.h"

char	*hex2char(char *hex)
{
	int	i;
	char	*keybin;
	char *binary;

	i = 0;
	keybin = (char*)malloc(sizeof(char) * 9);
	memset(keybin, 0, 9);
	printf("hex [%s]\n", hex);
	while (i < 16)
	{
		char c = hex[i];
		int value = 0;
		if(c >= '0' && c <= '9')
			value = (c - '0');
		else if (c >= 'A' && c <= 'F')
			value = (10 + (c - 'A'));
		else if (c >= 'a' && c <= 'f')
			value = (10 + (c - 'a'));
		printf("c val(%d)\n", value);
		keybin[i / 2] += value << (((i + 1) % 2) * 4);
		i++;
	}
	keybin[i] = '\0';
	printf("[%s]\n", keybin);
	binary = transBit(keybin, 8);
	printf("[%s]hex to bin \n[0001101000101010001110100100101001011010011010110111101110001010]\n", binary);
	//printf("(%s)\n", keybin);
	return binary;
}

char	**makeKeys(char *k64)
{
	char	*k56;
	char	**k16;
	int i;

	k56 = apply_perm(k64, perm_c1, 56);
	printf("[%s] k 56\n", k56);
	k16 = (char**)malloc(sizeof(char*) * 16);
	i = 0;
	while (i < 16)
	{
		*k16 = (char*)malloc(sizeof(char) * 49);
		i++;
	}
	keyRotation(k56, k16);
	return (k16);
}

char *shiftbits(int *rl, int ks)
{
	int i;

	i = 0;
	while (i < 28)
	{
		rl[i] = rl[i] + rotate_KS[ks];
		if (rl[i] > 28)
			rl[i] -= 28;
		i++;
	}
}

char	*combine_Andperm(char *ck, char *dk)
{
	char k[56];
	char *k48;

	strcpy(k, ck);
	strcat(k, dk);
	k48 = apply_perm(k, perm_c2, 48);
	return (k48);
}

void	keyRotation(char *k56, char **k16)
{
	char c[29];
	char d[29];
	char *ck;
	char *dk;
	int i;
	int s;

	i = 0;
	while (i < 28)
	{
		c[i] = k56[i];
		d[i] = k56[i + 28];
		i++;
	}
	c[i] = '\0';
	d[i] = '\0';
	printf("{%s%s} c d\n", c, d);
	s = 0;
	while (s < 16)
	{
		shiftbits(rotate_len, s);
		ck = apply_perm(c, rotate_len, 28);
		dk = apply_perm(d, rotate_len, 28);
		i = 0;
		k16[s] = combine_Andperm(ck, dk);
		printf("%d %d %d\n", rotate_len[0], rotate_len[1], rotate_len[2]);
		printf("{%s}\n", k16[s]);
		s++;
		free(ck);
		free(dk);
	}

}
