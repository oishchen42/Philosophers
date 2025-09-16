#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct s_data
{
	void	*value;
	struct s_data *next;
} t_data;


typedef struct s_t_data
{
	void		*value;
	struct s_data *datas;
	pthread_t 		*thrds;
} t_t_data;


void	*simple_routine(void *args)
{
	t_data	*data = (t_data *)args;

	data->value = "vabalbadg";
}

int	main()
{
	int	i;
	t_t_data	*ddata;

	i  = 0;
	ddata->thrds = malloc(sizeof(pthread_t) * 2);
	while (i < 2)
		pthread_create(&datas->thrds[i], NULL, simple_routine, data-)
}