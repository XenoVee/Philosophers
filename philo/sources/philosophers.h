/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:37:10 by rmaes         #+#    #+#                 */
/*   Updated: 2023/05/23 14:36:01 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../cdl_list/include/cdl_list.h"
# include <sys/time.h>

enum e_message
{
	FORK = 0,
	EAT,
	SLEEP,
	THINK,
};

enum e_bool
{
	FALSE = 0,
	TRUE,
};

typedef struct s_params
{
	unsigned int	nphilo;
	unsigned int	tdie;
	unsigned int	teat;
	unsigned int	tsleep;
	unsigned int	neat;
	unsigned long	start_time;
	pthread_mutex_t	start_mutex;
	int				dead;
	pthread_mutex_t	dead_mutex;
	unsigned int	finished;
	pthread_mutex_t	fin_mutex;
	t_dllist		*forks;
}				t_params;

typedef struct s_args
{
	t_dlnode	*fork;
	int			philo;
	t_params	*params;
}				t_args;

int				parse_input(t_params *params, int argc, char **argv);
t_args			**setup_args(int nphilo, t_dllist *list, t_params *params);
t_dllist		*make_table(int nphilos);

void			*reaperfunc(void *p);
int				ft_min(int n, int d);
int				isint(char *str);
int				eerror(char *msg);
int				ft_atoi(const char *str);
void			ft_usleep(unsigned int time);
unsigned long	timestamp(void);
void			message(t_args *args, int message);
int				all_alive(t_params *params);
int				all_finished(t_params *params);
void			set_finished(t_args *args);
int				max_check(const char *str);
int				ft_strcmp(const char *str1, const char *str2);

#endif