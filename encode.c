#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* decodeblock - decode 4 '6-bit' characters into 3 8-bit binary bytes */
void decodeblock(unsigned char in[], char *clrstr) {
  unsigned char out[4];
  out[0] = in[0] << 2 | in[1] >> 4;
  out[1] = in[1] << 4 | in[2] >> 2;
  out[2] = in[2] << 6 | in[3] >> 0;
  out[3] = '\0';
  strncat(clrstr, out, sizeof(out));
}

void b64_decode(char *b64src, char *clrdst) {
  int c, phase, i;
  unsigned char in[4];
  char *p;

  clrdst[0] = '\0';
  phase = 0; i=0;
  while(b64src[i]) {
    c = (int) b64src[i];
    if(c == '=') {
      decodeblock(in, clrdst);
      break;
    }
    p = strchr(b64, c);
    if(p) {
      in[phase] = p - b64;
      phase = (phase + 1) % 4;
      if(phase == 0) {
        decodeblock(in, clrdst);
        in[0]=in[1]=in[2]=in[3]=0;
      }
    }
    i++;
  }
}

void encodeblock( char in[], char cipher[], int len )
{
    char out[5];
    //printf("[%d] out[0] {%d}\n",in[0], in[0] >> 2);

    out[0] = b64[ in[0] >> 2 ];
//    printf("[%d]out[1] [%d]{%d}\n",in[0], (in [0] & 0x03), ((in [0] & 0x03) << 4));
  //  printf("[%d]out[1] [%d]{%d}\n",in[1], (in[1] & 0xf0), ((in[1] & 0xf0) >> 4));
    out[1] = b64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    //printf("[%d]out[2] {%d}\n",in[1], ((in[1] & 0x0f) << 2));
    //printf("[%d]out[2] {%d}\n",in[2], ((in[2] & 0xc0) >> 6));
    out[2] = (char) (len > 1 ? b64[ ((in[1] & 0x0f) << 2) |
             ((in[2] & 0xc0) >> 6) ] : '=');
    //printf("[%d]out[3] {%d}\n",in[2], ((in[2] & 0x3f)));

    out[3] = (char) (len > 2 ? b64[ in[2] & 0x3f ] : '=');
    out[4] = '\0';
    strncat(cipher, out, sizeof(out));
}

void b64_encode(char *plain, char *cipher)
{
  char in[3];
  int i;
  int len;
  int j;

  j = 0;
  cipher[0] = '\0';
  while(plain[j])
  {
    len = 0;
    i = 0;
    while(i < 3 && plain[j])
    {
      in[i] = plain[j];
      if(plain[j])
      {
        len++;
        j++;
      }
      i++;
    }
    if (len != 3)
    {
      in[i] = '\n';
      len++;
    }
    in[len] = '\0';
    if(len)
    {
      encodeblock( in, cipher, len );
    }
  }
  if (len == 3 && in[2] != '\n')
  {
    bzero(in, 4);
    in[0] = '\n';
    encodeblock(in, cipher, 1);
  }
}

int main(int ac, char **av)
{
  char x;

  char cipher[250];
  printf("(d)ecode or (e)ncode\n");
  scanf("%c", &x);
  if (x == 'd')
  {
    b64_decode(av[1], cipher);
    printf("{%s} decoded -> %s", av[1], cipher);
  }
  else
  {
    b64_encode(av[1], cipher);
    printf("{%s} encoded -> {%s}\n", av[1], cipher);
  }
  return 1;
}