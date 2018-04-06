#include "lib.h"

#define MAXINTLEN 100
int getFlag(char *temp, char *flag)
{

	if ((*temp) == ' ' || (*temp) == '-' || (*temp) == '+' || (*temp) == '#' || (*temp) == '0')
	{
		*flag = *temp;
		return 1;
	}
	else
	{
		return 0;
	}
}

int getWidth(char *temp, int *width)
{
	int offset = 0;
	while(true)
	{
		if (*(temp + offset) <= '9' && *(temp + offset) >= '0')
		{
			(*width) *= 10;
			(*width) += (*(temp + offset)) - '0';
			offset++;
		}
		else
		{
			break;
		}
	}
	return offset;
}

int getPercsion(char *temp, int *percision)
{
	int offset = 0;
	if((*temp) == '.')
	{
		offset++;
		while (true)
		{
			if (*(temp + offset) <= '9' && *(temp + offset) >= '0')
			{
				(*percision) *= 10;
				(*percision) += (*(temp + offset)) - '0';
				offset++;
			}
			else
			{
				break;
			}
		}
	}

	return offset;
}

int getType(char *temp, char *type)
{
	//%a %e %E %f %g %G %p
	if ((*temp) == 'c' || (*temp) == 'd' || (*temp) == 'i' || (*temp) == 'o' || (*temp) == 's' || (*temp) == 'x' || (*temp) == 'X' || (*temp) == 'u')
	{
		*type = *temp;
		return 1;
	}
	else
	{
		return 0;
	}
}

int printNum(int num, int base, int sign)
{
	int length = 0;
	char str[MAXINTLEN];
	memset(str, 0, MAXINTLEN);
	itoa(num, str, base, sign);

	while (*(str + length) != '\0')
	{
		_putc(*(str + length));
		length++;
	}

	return length;
}


int printString(char *str)
{
	int length = 0;
	while (*(str + length) != '\0')
	{
		_putc(*(str + length));
		length++;
	}

	return length;
}

int printFmtNum(va_list *argp, char flag, int width, int percision, int base, int sign)
{
	int length = 0;
	int num = va_arg(*argp, int);
	char str[MAXINTLEN];
	int tempPercision;
	int tempWidthExceed;
	if (base == 10 && sign == 1) {
		tempPercision = percision - strlen(itoa(abs(num), str, base, sign));
		tempWidthExceed = width - max(percision, (int)strlen(itoa(abs(num), str, base, sign)))
			- (flag == ' ' || flag == '+' || num < 0 ? 1 : 0)
			- (flag == '#' && base == 16 ? 2 : 0)
			- (flag == '#' && base == 8 ? 1 : 0);
	}
	else
	{
		tempPercision = percision - strlen(itoa(num, str, base, sign));
		tempWidthExceed = width - max(percision, (int)strlen(itoa(num, str, base, sign)))
			- (flag == '#' && base == 16 ? 2 : 0)
			- (flag == '#' && base == 8 ? 1 : 0);
	}
	if (flag != '-')
	{
		while (tempWidthExceed > 0)
		{
			if (flag == '0' && percision == 0)
			{
				_putc('0');
				length++;
			}
			else
			{
				_putc(' ');
				length++;
			}
			tempWidthExceed--;
		}
		if (flag == '+' && sign == 1 && base == 10)
		{
			if (num > 0)
			{
				_putc('+');
			}
			else
			{
				_putc('-');
			}
			length++;
		}
		else if (flag == ' ' && sign == 1 && base == 10)
		{
			if (num > 0)
			{
				_putc(' ');
			}
			else
			{
				_putc('-');
			}
			length++;
		}
		else if (flag == '#' && base == 16)
		{
			length += printString("0x");
		}
		else if (flag == '#' && base == 8)
		{
			length += printString("0");
		}
		else
		{
			if (num < 0 && sign == 1 && base == 10)
			{
				_putc('-');
				length++;
			}
		}
		while (tempPercision > 0)
		{
			_putc('0');
			length++;
			tempPercision--;
		}
		if (sign == 1 && base == 10)
		{
			length += printNum(abs(num), base, sign);
		}
		else
		{
			length += printNum(num, base, sign);
		}
		
	}
	else
	{
		if (num < 0 && sign == 1 && base == 10)
		{
			_putc('-');
			length++;
		}
		while (tempPercision > 0)
		{
			_putc('0');
			length++;
			tempPercision--;
		}
		if (sign == 1 && base == 10)
		{
			length += printNum(abs(num), base, sign);
		}
		else
		{
			length += printNum(num, base, sign);
		}
		while (tempWidthExceed > 0)
		{
			_putc(' ');
			length++;
			tempWidthExceed--;
		}
	}
	return length;
}

int printFmt(va_list *argp, char flag, int width, int percision, char type)//·µ»Ø³€¶È
{
	int length = 0;
	if (type == 'c')
	{
		char c = va_arg(*argp, int);
		length++;//for the length of char
		int tempWidth = width - 1;
		if (flag == '-')
		{
			_putc(c);
			while (tempWidth > 0)
			{
				_putc(' ');
				tempWidth--;
				length++;
			}
		}
		else if (flag == '0')
		{
			while (tempWidth > 0)
			{
				_putc('0');
				tempWidth--;
				length++;
			}
			_putc(c);
		}
		else
		{
			while (tempWidth > 0)
			{
				_putc(' ');
				tempWidth--;
				length++;
			}
			_putc(c);
		}
	}
	else if (type == 's')
	{
		char *str = va_arg(*argp, char *);
		int len = strlen(str);
		length += len;
		int tempWidth = width - len;
		if (flag == '-')
		{
			printString(str);
			while (tempWidth > 0)
			{
				_putc(' ');
				tempWidth--;
				length++;
			}
		}
		else if (flag == '0')
		{
			while (tempWidth > 0)
			{
				_putc('0');
				tempWidth--;
				length++;
			}
			printString(str);
		}
		else
		{
			while (tempWidth > 0)
			{
				_putc(' ');
				tempWidth--;
				length++;
			}
			printString(str);
		}
	}
	else if (type == 'd' || type == 'i')
	{
		length += printFmtNum(argp, flag, width, percision, 10, 1);
	}
	else if (type == 'x' || type == 'X')
	{
		length += printFmtNum(argp, flag, width, percision, 16, 0);
	}
	else if(type == 'o')
	{
		length += printFmtNum(argp, flag, width, percision, 8, 0);
	}
	else if(type == 'u')
	{
		length += printFmtNum(argp, flag, width, percision, 10, 0);
	}
	return length;
}

int printf(char *fmt, ...)
{
	va_list argp;
	char *temp = fmt;
	int length = 0;

	va_start(argp, fmt);
	while ((*temp) != '\0')
	{
		if ((*temp) == '%')
		{
			temp++;
			
			char flag = '\0';
			int width = 0;
			int percision = 0;
			char type = '\0';
			temp += getFlag(temp, &flag);
			temp += getWidth(temp, &width);
			temp += getPercsion(temp, &percision);
			//
			temp += getType(temp, &type);
			length += printFmt(&argp, flag, width, percision, type);
		}
		else
		{
			_putc(*temp);
			temp++;
			length++;
		}
		
	}
	va_end(argp);
	return length;
}


