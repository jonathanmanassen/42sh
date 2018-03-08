/*
** my_strlen.c for my_strlen in /home/manass_j/rendu/Piscine_C_J04
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Thu Oct  1 16:37:59 2015 jonathan manassen
** Last update Tue Dec  1 17:00:49 2015 jonathan manassen
*/

int	my_strlen(char *str)
{
  int	a;

  a = 0;
  while (str[a])
    {
      a = a + 1;
    }
  return (a);
}
