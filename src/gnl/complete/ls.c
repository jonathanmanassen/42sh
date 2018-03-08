/*
** ls.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh/bonus
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sat May 21 08:43:03 2016 jonathan manassen
** Last update Sun Jun  5 22:17:28 2016 jonathan manassen
*/

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "my.h"
#include "./include/complete.h"

char	*my_lowcase(char *str)
{
  int	i;
  char	*low;

  i = 0;
  if ((low = malloc(sizeof(char*) * my_strlen(str))) == NULL)
    exit(0);
  while (str[i])
    {
      if (str[i] >= 65 && str[i] <= 90)
	low[i] = str[i] + 32;
      else
	low[i] = str[i];
      i = i + 1;
    }
  return (low);
}

char	**swap_str(char **str, int i, int j)
{
  char	*tmp;

  if ((tmp = malloc(sizeof(char*) * my_strlen(str[i]) + 1)) == NULL)
    exit(0);
  tmp = str[i];
  str[i] = str[j];
  str[i][my_strlen(str[i])] = '\0';
  str[j] = tmp;
  str[j][my_strlen(str[j])] = '\0';
  return (str);
}

char	**sort_files(char **str, int i, int j)
{
  int	k;
  char	*low;
  char	*low2;

  k = 1;
  while (str[i] && str[i + 1])
    {
      low = my_lowcase(str[i]);
      low2 = my_lowcase(str[k]);
      if (low[j] > low2[j])
	swap_str(str, i, k);
      j = (low[j] == low2[j] && low[j] != '\0') ? j + 1 : 0;
      if (j == 0)
	k = k + 1;
      if (str[k] == NULL)
	{
	  i = i + 1;
	  k = i + 1;
	}
      free(low);
      free(low2);
    }
  return (str);
}

int		count_files(char *name)
{
  DIR           *dirp;
  struct dirent *d;
  int		i;

  i = 0;
  if ((dirp = opendir(get_name_opendir(name, &i))) == NULL)
    if ((dirp = opendir(get_name_opendir_second(name, &i))) == NULL)
      if ((dirp = opendir(".")) == NULL)
	exit(0);
  i = 0;
  while ((d = readdir(dirp)) != NULL)
    {
      if (d->d_name[0] != '.')
	i = i + 1;
    }
  return (i);
}

char		**no_options(int j, char *name)
{
  DIR           *dirp;
  char		**str;
  int		i;
  char		*get_name;

  if ((str = malloc(sizeof(char**) * (j + 1))) == NULL)
    exit(0);
  if ((dirp = opendir(get_name_opendir(name, &i))) == NULL)
    if ((dirp = opendir(get_name_opendir_second(name, &i))) == NULL)
      if ((dirp = opendir(get_name_opendir_current(name, &i))) == NULL)
	exit(0);
  (i == 0) ? get_name = get_name_opendir(name, &i) : 0;
  (i == 1) ? get_name = get_name_opendir_second(name, &i) : 0;
  (i == 2) ? get_name = get_name_opendir_current(name, &i) : 0;
  str = get_ls(str, get_name, dirp, 0);
  str = sort_files(str, 0, 0);
  free(get_name);
  return (str);
}
