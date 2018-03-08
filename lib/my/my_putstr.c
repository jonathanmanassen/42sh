/*
** my_putstr.c for my_putstr in /home/manass_j/rendu/Piscine_C_J04
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Thu Oct  1 12:11:58 2015 jonathan manassen
** Last update Tue Jan 12 15:49:53 2016 jonathan manassen
*/

#include "../../include/my.h"

void	my_putstr(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      my_putchar(str[i]);
      i = i + 1;
    }
}
