#ifndef LIB_DES_H
# define LIB_DES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *apply_perm(char *pre, int *perm, int l);
char	*transBit(char *sfb, int a);
void	plainSort(char *plain);
void	desEncode(char *binary);

char	*hex2char(char *hex);
char	**makeKeys(char *k64);
void	keyRotation(char *k56, char **k16);
char *shiftbits(int *rl, int ks);
char	*combine_Andperm(char *ck, char *dk);




extern int initial_perm[];
extern int perm_c1[];
extern int perm_c2[];
extern int rotate_len[];
extern int rotate_KS[];


#endif
