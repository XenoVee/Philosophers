/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:37:10 by rmaes         #+#    #+#                 */
/*   Updated: 2023/04/07 21:42:01 by rmaes         ########   odam.nl         */
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
	int				dead;
	pthread_mutex_t	dead_mutex;
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

int				isint(char *str);
int				eerror(char *msg);
int				ft_atoi(const char *str);
void			ft_usleep(unsigned int time);
unsigned long	timestamp(void);
void			message(t_args *args, int message);
int				all_alive(t_args *args);

#endif