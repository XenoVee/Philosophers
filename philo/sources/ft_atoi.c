/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 16:41:27 by rmaes         #+#    #+#                 */
/*   Updated: 2023/04/13 14:41:42 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_min(int n, int d)
{
	if (n > d)
		return (d);
	return (n);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str2[i] - str1[i]);
}

unsigned int	ft_atoi(const char *str)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while ((str[0] >= 9 && str[0] <= 13) || str[0] == 32)
		str++;
	if (str[0] == '+' && sign != -1)
		str++;
	while (str[0] >= '0' && str[0] <= '9')
	{
		num = num * 10 + str[0] - 48;
		str++;
	}
	num = num * sign;
	return (num);
}
