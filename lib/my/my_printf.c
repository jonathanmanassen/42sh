/*
** my_printf.c for my_printf in /home/manass_j/rendu/PSU_2015_my_printf
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Mon Nov  9 15:27:38 2015 jonathan manassen
** Last update Tue Jan 12 15:49:43 2016 jonathan manassen
*/

#include <stdarg.h>
#include "../../include/my.h"

int	change_base(int nb, int base)
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

int	intlen(char c, char j, int len)
{
  len = change_base(c, 8);
  while (len / 10 > 0)
    {
      j = j + 1;
      len = len / 10;
    }
  return (j);
}

int	my_printf_S(char *str)
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
	  j = intlen(str[i], j, len);
	  my_putchar('\\');
	  while (3 - j > 0)
	    {
	      my_putchar('0');
	      j = j + 1;
	    }
	  my_putnbr(change_base(str[i], 8));
	}
      i = i + 1;
    }
  return (0);
}

int	my_printf_flags(const char *format, int i, va_list ap)
{
  if (format[i + 1] == 's')
    my_putstr(va_arg(ap, char *));
  else if (format[i + 1] == 'S')
    my_printf_S(va_arg(ap, char *));
  else if (format[i + 1] == 'o')
    my_putnbr(change_base(va_arg(ap, unsigned int), 8));
  else if (format[i + 1] == 'n')
    my_strlen(va_arg(ap, char *));
  else if (format[i + 1] == 'b')
    my_putnbr(change_base(va_arg(ap, unsigned int), 2));
  else if (format[i + 1] == 'd' || format[i + 1] == 'i')
    my_putnbr(va_arg(ap, int));
  else if (format[i + 1] == 'u')
    my_putnbr_u(va_arg(ap, unsigned int));
  else if (format[i + 1] == 'c')
    my_putchar(va_arg(ap, int));
  else
    my_putchar(format[i + 1]);
  return (i);
}

int		my_printf(const char *format, ...)
{
  va_list	ap;
  int		i;

  i = 0;
  va_start(ap, format);
  while (format[i] != '\0')
    {
      if (format[i] == '%' && format[i + 1] != 0)
	{
	  i = my_printf_flags(format, i, ap);
	  i = i + 1;
	}
      else
	my_putchar(format[i]);
      i = i + 1;
    }
  va_end(ap);
  return (0);
}
