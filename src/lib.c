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

void *memset(void * s, int c, size_t count)
{
	char *xs = (char *)s;
	while (count--)
		*xs++ = c;
	return s;
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
static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

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




