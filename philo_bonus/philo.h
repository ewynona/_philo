#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5
# define FULL 6

typedef struct s_arg {
	int	philo_amount;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_count;
	int	philo_status;
}	t_arg;

typedef struct s_semaphores {
	sem_t	*died;
	sem_t	*forks;
	sem_t	*status;
	sem_t	*garcon;
}	t_semaphores;

typedef struct s_philo {
	int				id;
	int				eat_count;
	t_semaphores	*semaphores;
	t_arg			*arg;
	pid_t			*pid;
	pthread_t		thread;
	long			eat_time;
	long			start_time;
}	t_philo;

/*
 * PHILO_INIT
 */
t_philo			*philo_init(t_arg *arg, t_semaphores *semaphores);
t_semaphores	*semaphores_init(t_arg *arg);

/*
 * ACTIONS
 */
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);
void			life_simulator(t_philo *philo);

/*
 * UTILS
 */
int				ft_atoi(const char *str);
void			ft_putstr_fd(char *str, int fd);
int				ft_strlen(char *str);
long			get_time(void);
void			print_status(int status, t_philo *philo);
void			ft_usleep(int ms);
void			close_semaphores(t_philo *philo);
void			ft_putstr_fd(char *str, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar_fd(char c, int fd);
int				ft_strerror(char *str, int error);

/*
 * START_SIMULATION
 */
int				start_simulation(t_arg *arg);

/*
 * PARSE
 */
t_arg			*parser(char **av);

#endif
