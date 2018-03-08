/*
** my_printf.c for my_printf in /home/mei_c/rendu/PSU_2015_my_printf
** 
** Made by christophe mei
** Login   <mei_c@epitech.net>
** 
** Started on  Sat Nov  7 12:32:53 2015 christophe mei
** Last update Mon Apr 25 19:09:19 2016 christophe mei
*/

#include <stdarg.h>
#include "my.h"

int	my_fprintfs(int fd, char *str)
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
	my_fputchar(fd, str[i]);
      else
	{
	  j = intlen2(str[i], j, len);
	  my_fputchar(fd, '\\');
	  while (3 - j > 0)
	    {
	      my_fputchar(fd, '0');
	      j = j + 1;
	    }
	  my_fputnbr(fd, base(str[i], 8));
	}
      i = i + 1;
    }
  return (0);
}

int	my_fprintff(int fd, const char *format, int i, va_list ap)
{
  if (format[i + 1] == 's')
    my_fputstr(fd, va_arg(ap, char*));
  else if (format[i + 1] == 'S')
    my_fprintfs(fd, va_arg(ap, char*));
  else if (format[i + 1] == 'b')
    my_fputnbr(fd, base(va_arg(ap, unsigned int), 2));
  else if (format[i + 1] == 'd' || format[i + 1] == 'i')
    my_fputnbr(fd, va_arg(ap, int));
  else if (format[i + 1] == 'c')
    my_fputchar(fd, va_arg(ap, int));
  else
    my_fputchar(fd, format[i + 1]);
  return (0);
}

int		my_fprintf(int fd, const char *format, ...)
{
  va_list	ap;
  int		i;

  i = 0;
  va_start(ap, format);
  while (format[i] != 0)
    {
      if (format[i] == '%' && format[i + 1] != 0)
	{
	  my_fprintff(fd, format, i, ap);
	  i = i + 1;
	}
      else
	my_fputchar(fd, format[i]);
      i = i + 1;
    }
  va_end(ap);
  return (0);
}
