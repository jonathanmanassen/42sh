/*
** get_next_line.h for get_next_line_h in /home/mei_c/rendu/CPE/CPE_2015_getnextline
** 
** Made by christophe mei
** Login   <mei_c@epitech.net>
** 
** Started on  Wed Jan  6 14:36:58 2016 christophe mei
** Last update Fri Jun  3 22:34:38 2016 jonathan manassen
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_
#  ifndef READ_SIZE
#   define READ_SIZE (10)
#  endif /* !READ_SIZE */

typedef struct	s_gnl
{
  char		re[READ_SIZE + 1];
  char		buffer[READ_SIZE + 1];
  char		*str;
  int		ret;
  int		i;
  int		j;
  int		s;
  int		t;
}		t_gnl;

char	*get_next_line(const int fd);

#endif /* !GET_NEXT_LINE_H_ */
