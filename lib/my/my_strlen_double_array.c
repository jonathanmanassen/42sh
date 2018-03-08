/*
** my_strlen_double_array.c for my_strlen_double_array in /home/manass_j/rendu/PSU_2015_42sh/bonus/lib/my
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Thu May 26 17:23:25 2016 jonathan manassen
** Last update Thu May 26 17:25:20 2016 jonathan manassen
*/

int	my_strlen_double_array(char **tab)
{
  int	i;

  i = 0;
  while (tab[i])
    i = i + 1;
  return (i);
}
