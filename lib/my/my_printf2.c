/*
** my_printf.c for my_printf in /home/mei_c/rendu/PSU_2015_my_printf
** 
** Made by christophe mei
** Login   <mei_c@epitech.net>
** 
** Started on  Sat Nov  7 12:32:53 2015 christophe mei
** Last update Mon Apr 25 19:22:09 2016 christophe mei
*/

#include <stdarg.h>
#include "my.h"

int	base(int nb, int base)
{
  int	result;
  int	i;

  i = 1;
  result = 0;
  while (nb > 0)
    {
      result = result + (nb % base * i);
      nb = nb / base;
      i = i * 10;
    }
  return (result);
}

int	intlen2(char str, int j, int len)
{
  len = base(str, 8);
  while (len / 10 > 0)
    {
      j = j + 1;
      len = len / 10;
    }
  return (j);
}

int	my_printfs(char *str)
{
  int	i;
  int	j;
  int	len;

  i = 0;
  j = 1;
  len = 0;
  while (str[i])
    {
      if (str[i] >= 32 && str[i] < 127)
	my_putchar(str[i]);
      else
	{
	  j = intlen2(str[i], j, len);
	  my_putchar('\\');
	  while (3 - j > 0)
	    {
	      my_putchar('0');
	      j = j + 1;
	    }
	  my_putnbr(base(str[i], 8));
	}
      i = i + 1;
    }
  return (0);
}

int	my_printff(const char *format, int i, va_list ap)
{
  if (format[i + 1] == 's')
    my_putstr(va_arg(ap, char*));
  else if (format[i + 1] == 'S')
    my_printfs(va_arg(ap, char*));
  else if (format[i + 1] == 'b')
    my_putnbr(base(va_arg(ap, unsigned int), 2));
  else if (format[i + 1] == 'd' || format[i + 1] == 'i')
    my_putnbr(va_arg(ap, int));
  else if (format[i + 1] == 'c')
    my_putchar(va_arg(ap, int));
  else
    my_putchar(format[i + 1]);
  return (0);
}

int		my_printf2(const char *format, ...)
{
  va_list	ap;
  int		i;

  i = 0;
  va_start(ap, format);
  while (format[i] != 0)
    {
      if (format[i] == '%' && format[i + 1] != 0)
	{
	  my_printff(format, i, ap);
	  i = i + 1;
	}
      else
	my_putchar(format[i]);
      i = i + 1;
    }
  va_end(ap);
  return (0);
}
