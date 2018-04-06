#include "lib.h"

/**************************/
/*        string.h        */
/**************************/
int strlen(const char *str)
{
	if (str == NULL)
	{
		return 0;
	}
	int len = 0;
	while (*str++)
	{
		len++;
	}
	return len;
}

void* memset(void* v,int c,size_t n){
  c &= 0xff;
  uint32_t c2 = (c << 8) | c;
  uint32_t c4 = (c2 << 16) | c2;
  uint64_t c8 = (((uint64_t)c4 << 16) << 16) | c4;
  int n_align = n & ~0xf;

  int i;
  // TODO: adjust 'v' to be 8-byte align to avoid unalign accesses on MIPS
  for (i = 0; i < n_align; i += 16) {
    *(uint64_t *)(v + i    ) = c8;
    *(uint64_t *)(v + i + 8) = c8;
  }

  for (; i < n; i ++) {
    ((char *)v)[i] = c;
  }

  return v;
}


/**************************/
/*         math.h         */
/**************************/
int abs(int num)
{
	if (num < 0)
	{
		num = -num;
	}
	return num;
}


/**************************/
/*        stdlib.h        */
/**************************/
char *itoa(int num, char *str, int radix, int sign)
{
	char index[] = "0123456789abcdef";
	unsigned unum;
	int i = 0, j, k;

	if (radix == 10 && num < 0 && sign == 1)
	{
		unum = (unsigned)-num;
		str[i++] = '-';
	}
	else unum = (unsigned)num;

	do {
		str[i++] = index[unum % (unsigned)radix];
		unum /= radix;
	} while (unum);
	str[i] = '\0';

	if (str[0] == '-')
		k = 1;
	else
		k = 0;

	char temp;
	for (j = k;j <= (i - 1) / 2;j++)
	{
		temp = str[j];
		str[j] = str[i - 1 + k - j];
		str[i - 1 + k - j] = temp;
	}
	return str;
}

int atoi(char* pstr)
{
	int retInteger = 0;
	int integerSign = 1;

	if (pstr == NULL)
	{
		return 0;
	}

	while ((*pstr) == ' ')
	{
		pstr++;
	}

	if (*pstr == '-')
	{
		integerSign = -1;
	}
	if (*pstr == '-' || *pstr == '+')
	{
		pstr++;
	}

	while (*pstr >= '0' && *pstr <= '9')
	{
		retInteger = retInteger * 10 + *pstr - '0';
		pstr++;
	}
	retInteger = integerSign * retInteger;

	return retInteger;
}




