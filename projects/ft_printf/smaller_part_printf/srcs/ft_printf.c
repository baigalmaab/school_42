/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaatar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:05:55 by bbaatar           #+#    #+#             */
/*   Updated: 2021/09/14 10:20:55 by bbaatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//testers:
// https://github.com/Tripouille/printfTester
//https://github.com/paulo-santana/ft_printf_testers
// print_p.c


#include "../include/ft_printf.h"

void initialize_format(struct s_format *format)
{
	format->width = 0;
	format->width_digit = 0;
	format->precision = -1;
	format->precision_digit = 0;
	format->flag_prec = 0;
	format->specifier = 0;
	format->negative = 0;
	format->base = "0123456789";
	format->base_nbr = 10;
}

int print_val(char *str, struct s_format *format, va_list a_list)
{
	int num_chars;

	num_chars = 0;
	if (str[0] == 'c')
		num_chars = print_c(format, a_list);
	else if (str[0] == 's')
		num_chars = print_str(format, a_list);
	else if (str[0] == 'p')
		num_chars = print_p(format, a_list);
	else if (str[0] == 'd' || str[0] == 'i')
		num_chars = print_di(format, a_list);
	else if (str[0] == 'u')
		num_chars = print_u(format, a_list);
	else if (str[0] == 'x')
		num_chars = print_sx(format, a_list);
	else if (str[0] == 'X')
		num_chars = print_x(format, a_list);
	else if (str[0] == '%')
		num_chars = print_perc();
	else
		return (0);
	return (num_chars);
}

void detect_width_and_precision(char *str, struct s_format *format, int *i, int *sum_char, va_list *a_list)
{
	if (str[*i] == '%')
	{
		(*i)++;
		if (detect_width(&str[*i], format) != 0)
		{
			*i += format->width_digit;
		}
		if(str[*i] == '.')
		{
			(*i)++;
			detect_precision(&str[*i], format);
			*i += format->precision_digit;
		}
		*sum_char += print_val(&str[*i], format, *a_list);
	}
	else
	{
		write(1, (const void *)&str[*i], 1);
		(*sum_char)++;
	}
	(*i)++;
}

int ft_printf(const char *input, ...)
{
	int i;
	int sum_char;
	va_list a_list;
	struct s_format format;
	const char *str_in;

	str_in = ft_strdup(input);
	initialize_format(&format);
	va_start(a_list, input);
	sum_char = 0;
	i = 0;
	while (str_in[i] != '\0')
	{
		detect_width_and_precision((char *)str_in, &format, &i, &sum_char, &a_list);
	}

	va_end(a_list);
	free((char *)str_in);
	return (sum_char);
}

// int main()
// {

	// ft_printf("--------------------%%u--------------------\n");		//19/20
	// printf("01) Vrai PRINTF : |%u|\n", 34);
	// ft_printf("01) Mon PRINTF  : |%u|\n", 34);
	// printf("02) Vrai PRINTF : |%u|\n", -34);
	// ft_printf("02) Mon PRINTF  : |%u|\n", -34);
	// printf("04) Vrai PRINTF : |%10u|\n", 90);
	// ft_printf("04) Mon PRINTF  : |%10u|\n", 90);
	// printf("05) Vrai PRINTF : |%.10u|\n", 90);
	// ft_printf("05) Mon PRINTF  : |%.10u|\n", 90);
	// printf("06) Vrai PRINTF : |%15u|\n", -100);
	// ft_printf("06) Mon PRINTF  : |%15u|\n", -100);
	// printf("07) Vrai PRINTF : |%.15u|\n", -100);
	// ft_printf("07) Mon PRINTF  : |%.15u|\n", -100);
	// printf("08) Vrai PRINTF : |%10.5u|\n", 52);
	// ft_printf("08) Mon PRINTF  : |%10.5u|\n", 52);
	// printf("09) Vrai PRINTF : |%5.10u|\n", 52);
	// ft_printf("09) Mon PRINTF  : |%5.10u|\n", 52);
	// printf("10) Vrai PRINTF : |%20.15u|\n", -100000);
	// ft_printf("10) Mon PRINTF  : |%20.15u|\n", -100000);
	// printf("11) Vrai PRINTF : |%15.20u|\n", -100000);
	// ft_printf("11) Mon PRINTF  : |%15.20u|\n", -100000);
	// printf("17) Vrai PRINTF : |%u|\n", 0);
	// ft_printf("17) Mon PRINTF  : |%u|\n", 0);
	// printf("18) Vrai PRINTF : |%.u|\n", 0);
	// ft_printf("18) Mon PRINTF  : |%.u|\n", 0);
	// printf("19) Vrai PRINTF : |%10u|\n", 0);
	// ft_printf("19) Mon PRINTF  : |%10u|\n", 0);
	// printf("20) Vrai PRINTF : |%.u|\n", 88);
	// ft_printf("20) Mon PRINTF  : |%.u|\n", 88);
	// printf("21) Vrai PRINTF : |%u|\n", UINT_MAX);
	// ft_printf("21) Mon PRINTF  : |%u|\n", UINT_MAX);
	// printf("22) Vrai PRINTF : |%u| |%u|\n", (unsigned int)-1, UINT_MAX + 1);
	// ft_printf("22) Mon PRINTF  : |%u| |%u|\n", (unsigned int)-1, UINT_MAX + 1);

	// printf("%d\n", printf("01) Vrai PRINTF : |%u|\n", 34));
	// ft_printf("%d\n", ft_printf("01) Mon PRINTF  : |%u|\n", 34));
	// printf("%d\n", printf("02) Vrai PRINTF : |%u|\n", -34));
	// ft_printf("%d\n", ft_printf("02) Mon PRINTF  : |%u|\n", -34));
	// printf("%d\n", printf("04) Vrai PRINTF : |%10u|\n", 90));
	// ft_printf("%d\n", ft_printf("04) Mon PRINTF  : |%10u|\n", 90));
	// printf("%d\n", printf("05) Vrai PRINTF : |%.10u|\n", 90));
	// ft_printf("%d\n", ft_printf("05) Mon PRINTF  : |%.10u|\n", 90));
	// printf("%d\n", printf("06) Vrai PRINTF : |%15u|\n", -100));
	// ft_printf("%d\n", ft_printf("06) Mon PRINTF  : |%15u|\n", -100));
	// printf("%d\n", printf("07) Vrai PRINTF : |%.15u|\n", -100));
	// ft_printf("%d\n", ft_printf("07) Mon PRINTF  : |%.15u|\n", -100));
	// printf("%d\n", printf("08) Vrai PRINTF : |%10.5u|\n", 52));
	// ft_printf("%d\n", ft_printf("08) Mon PRINTF  : |%10.5u|\n", 52));
	// printf("%d\n", printf("09) Vrai PRINTF : |%5.10u|\n", 52));
	// ft_printf("%d\n", ft_printf("09) Mon PRINTF  : |%5.10u|\n", 52));
	// printf("%d\n", printf("10) Vrai PRINTF : |%20.15u|\n", -100000));
	// ft_printf("%d\n", ft_printf("10) Mon PRINTF  : |%20.15u|\n", -100000));
	// printf("%d\n", printf("11) Vrai PRINTF : |%15.20u|\n", -100000));
	// ft_printf("%d\n", ft_printf("11) Mon PRINTF  : |%15.20u|\n", -100000));

	// ft_printf("--------------------%%x--------------------\n");		//29/29
	// printf("01) Vrai PRINTF : |%x|\n", 34);
	// ft_printf("01) Mon PRINTF  : |%x|\n", 34);
	// printf("02) Vrai PRINTF : |%x|\n", -34);
	// ft_printf("02) Mon PRINTF  : |%x|\n", -34);
	// printf("04) Vrai PRINTF : |%10x|\n", 90);
	// ft_printf("04) Mon PRINTF  : |%10x|\n", 90);
	// printf("05) Vrai PRINTF : |%.10x|\n", 90);
	// ft_printf("05) Mon PRINTF  : |%.10x|\n", 90);
	// printf("06) Vrai PRINTF : |%15x|\n", -100);
	// ft_printf("06) Mon PRINTF  : |%15x|\n", -100);
	// printf("07) Vrai PRINTF : |%.15x|\n", -100);
	// ft_printf("07) Mon PRINTF  : |%.15x|\n", -100);
	// printf("08) Vrai PRINTF : |%10.5x|\n", 52);
	// ft_printf("08) Mon PRINTF  : |%10.5x|\n", 52);
	// printf("09) Vrai PRINTF : |%5.10x|\n", 52);
	// ft_printf("09) Mon PRINTF  : |%5.10x|\n", 52);
	// printf("10) Vrai PRINTF : |%20.15x|\n", -100000);
	// ft_printf("10) Mon PRINTF  : |%20.15x|\n", -100000);
	// printf("11) Vrai PRINTF : |%15.20x|\n", -100000);
	// ft_printf("11) Mon PRINTF  : |%15.20x|\n", -100000);
	// printf("23) Vrai PRINTF : |%.x|\n", 0);
	// ft_printf("23) Mon PRINTF  : |%.x|\n", 0);
	// printf("24) Vrai PRINTF : |%.x|\n", 88);
	// ft_printf("24) Mon PRINTF  : |%.x|\n", 88);
	// printf("26) Vrai PRINTF : |%x|\n", UINT_MAX);
	// ft_printf("26) Mon PRINT   : |%x|\n", UINT_MAX);
	// printf("29) Vrai PRINTF : |%x| |%x|\n", (unsigned int)-1, UINT_MAX + 1);
	// ft_printf("29) Mon PRINTF  : |%x| |%x|\n", (unsigned int)-1, UINT_MAX + 1);

	// ft_printf("--------------------%%x--------------------\n");

	// printf("%d\n", printf("01) Vrai PRINTF : |%x|\n", 34));
	// ft_printf("%d\n", ft_printf("01) Mon PRINTF  : |%x|\n", 34));
	// printf("%d\n", printf("02) Vrai PRINTF : |%x|\n", -34));
	// ft_printf("%d\n", ft_printf("02) Mon PRINTF  : |%x|\n", -34));
	// printf("%d\n", printf("04) Vrai PRINTF : |%10x|\n", 90));
	// ft_printf("%d\n", ft_printf("04) Mon PRINTF  : |%10x|\n", 90));
	// printf("%d\n", printf("05) Vrai PRINTF : |%.10x|\n", 90));
	// ft_printf("%d\n", ft_printf("05) Mon PRINTF  : |%.10x|\n", 90));
	// printf("%d\n", printf("06) Vrai PRINTF : |%15x|\n", -100));
	// ft_printf("%d\n", ft_printf("06) Mon PRINTF  : |%15x|\n", -100));
	// printf("%d\n", printf("07) Vrai PRINTF : |%.15x|\n", -100));
	// ft_printf("%d\n", ft_printf("07) Mon PRINTF  : |%.15x|\n", -100));
	// printf("%d\n", printf("08) Vrai PRINTF : |%10.5x|\n", 52));
	// ft_printf("%d\n", ft_printf("08) Mon PRINTF  : |%10.5x|\n", 52));
	// printf("%d\n", printf("09) Vrai PRINTF : |%5.10x|\n", 52));
	// ft_printf("%d\n", ft_printf("09) Mon PRINTF  : |%5.10x|\n", 52));
	// printf("%d\n", printf("10) Vrai PRINTF : |%20.15x|\n", -100000));
	// ft_printf("%d\n", ft_printf("10) Mon PRINTF  : |%20.15x|\n", -100000));
	// printf("%d\n", printf("11) Vrai PRINTF : |%15.20x|\n", -100000));
	// ft_printf("%d\n", ft_printf("11) Mon PRINTF  : |%15.20x|\n", -100000));
	// printf("%d\n", printf("23) Vrai PRINTF : |%.x|\n", 0));
	// ft_printf("%d\n", ft_printf("23) Mon PRINTF  : |%.x|\n", 0));
	// printf("%d\n", printf("24) Vrai PRINTF : |%.x|\n", 88));
	// ft_printf("%d\n", ft_printf("24) Mon PRINTF  : |%.x|\n", 88));
	// printf("%d\n", printf("26) Vrai PRINTF : |%x|\n", UINT_MAX));
	// ft_printf("%d\n", ft_printf("26) Mon PRINT   : |%x|\n", UINT_MAX));
	// printf("%d\n", printf("29) Vrai PRINTF : |%x| |%x|\n", (unsigned int)-1, UINT_MAX + 1));
	// ft_printf("%d\n", ft_printf("29) Mon PRINTF  : |%x| |%x|\n", (unsigned int)-1, UINT_MAX + 1));

	// ft_printf("--------------------%%X--------------------\n");
	// printf("01) Vrai PRINTF : |%X|\n", 34);
	// ft_printf("01) Mon PRINTF  : |%X|\n", 34);
	// printf("02) Vrai PRINTF : |%X|\n", -34);
	// ft_printf("02) Mon PRINTF  : |%X|\n", -34);
	// printf("04) Vrai PRINTF : |%10X|\n", 90);
	// ft_printf("04) Mon PRINTF  : |%10X|\n", 90);
	// printf("05) Vrai PRINTF : |%.10X|\n", 90);
	// ft_printf("05) Mon PRINTF  : |%.10X|\n", 90);
	// printf("06) Vrai PRINTF : |%15X|\n", -100);
	// ft_printf("06) Mon PRINTF  : |%15X|\n", -100);
	// printf("07) Vrai PRINTF : |%.15X|\n", -100);
	// ft_printf("07) Mon PRINTF  : |%.15X|\n", -100);
	// printf("08) Vrai PRINTF : |%10.5X|\n", 52);
	// ft_printf("08) Mon PRINTF  : |%10.5X|\n", 52);
	// printf("09) Vrai PRINTF : |%5.10X|\n", 52);
	// ft_printf("09) Mon PRINTF  : |%5.10X|\n", 52);
	// printf("10) Vrai PRINTF : |%20.15X|\n", -100000);
	// ft_printf("10) Mon PRINTF  : |%20.15X|\n", -100000);
	// printf("11) Vrai PRINTF : |%15.20X|\n", -100000);
	// ft_printf("11) Mon PRINTF  : |%15.20X|\n", -100000);
	// printf("23) Vrai PRINTF : |%.X|\n", 0);
	// ft_printf("23) Mon PRINTF  : |%.X|\n", 0);
	// printf("24) Vrai PRINTF : |%.X|\n", 88);
	// ft_printf("24) Mon PRINTF  : |%.X|\n", 88);
	// printf("26) Vrai PRINTF : |%X|\n", UINT_MAX);
	// ft_printf("26) Mon PRINT   : |%X|\n", UINT_MAX);
	// printf("28) Vrai PRINTF : |%X| |%X|\n", (unsigned int)-1, UINT_MAX + 1);
	// ft_printf("28) Mon PRINTF  : |%X| |%X|\n", (unsigned int)-1, UINT_MAX + 1);

	// printf("%d\n", printf("01) Vrai PRINTF : |%X|\n", 34));
	// ft_printf("%d\n", ft_printf("01) Mon PRINTF  : |%X|\n", 34));
	// printf("%d\n", printf("02) Vrai PRINTF : |%X|\n", -34));
	// ft_printf("%d\n", ft_printf("02) Mon PRINTF  : |%X|\n", -34));
	// printf("%d\n", printf("%X %X %X\n", LONG_MAX, LONG_MIN, ULONG_MAX));
	// ft_printf("%d\n", ft_printf("%X %X %X\n", LONG_MAX, LONG_MIN, ULONG_MAX));
	// printf("%d\n", printf("%X\n", LONG_MAX));
	// ft_printf("%d\n", ft_printf("%X\n", LONG_MAX));
	// printf("%d\n", printf("%X\n", LONG_MIN));
	// ft_printf("%d\n", ft_printf("%X\n", LONG_MIN));
	// printf("%d\n", printf("%X\n", -43));
	// ft_printf("%d\n", ft_printf("%X\n", -43));
	// printf("%d\n", printf("04) Vrai PRINTF : |%10X|\n", 90));
	// ft_printf("%d\n", ft_printf("04) Mon PRINTF  : |%10X|\n", 90));
	// printf("%d\n", printf("05) Vrai PRINTF : |%.10X|\n", 90));
	// ft_printf("%d\n", ft_printf("05) Mon PRINTF  : |%.10X|\n", 90));
	// printf("%d\n", printf("06) Vrai PRINTF : |%15X|\n", -100));
	// ft_printf("%d\n", ft_printf("06) Mon PRINTF  : |%15X|\n", -100));
	// printf("%d\n", printf("07) Vrai PRINTF : |%.15X|\n", -100));
	// ft_printf("%d\n", ft_printf("07) Mon PRINTF  : |%.15X|\n", -100));
	// printf("%d\n", printf("08) Vrai PRINTF : |%10.5X|\n", 52));
	// ft_printf("%d\n", ft_printf("08) Mon PRINTF  : |%10.5X|\n", 52));
	// printf("%d\n", printf("09) Vrai PRINTF : |%5.10X|\n", 52));
	// ft_printf("%d\n", ft_printf("09) Mon PRINTF  : |%5.10X|\n", 52));
	// printf("%d\n", printf("10) Vrai PRINTF : |%20.15X|\n", -100000));
	// ft_printf("%d\n", ft_printf("10) Mon PRINTF  : |%20.15X|\n", -100000));
	// printf("%d\n", printf("11) Vrai PRINTF : |%15.20X|\n", -100000));
	// ft_printf("%d\n", ft_printf("11) Mon PRINTF  : |%15.20X|\n", -100000));
	// printf("%d\n", printf("23) Vrai PRINTF : |%.X|\n", 0));
	// ft_printf("%d\n", ft_printf("23) Mon PRINTF  : |%.X|\n", 0));
	// printf("%d\n", printf("24) Vrai PRINTF : |%.X|\n", 88));
	// ft_printf("%d\n", ft_printf("24) Mon PRINTF  : |%.X|\n", 88));
	// printf("%d\n", printf("26) Vrai PRINTF : |%X|\n", UINT_MAX));
	// ft_printf("%d\n", ft_printf("26) Mon PRINT   : |%X|\n", UINT_MAX));
	// printf("%d\n", printf("28) Vrai PRINTF : |%X| |%X|\n", (unsigned int)-1, UINT_MAX + 1));
	// ft_printf("%d\n", ft_printf("28) Mon PRINTF  : |%X| |%X|\n", (unsigned int)-1, UINT_MAX + 1));
	

// 	ft_printf("--------------------%%s--------------------\n");			//NULL g yanzlah heregtei.
// 	printf("01) Vrai PRINTF : |%s|\n", "salut");
// 	ft_printf("01) Mon PRINTF  : |%s|\n", "salut");
// 	printf("04) Vrai PRINTF : |%10s|\n", "42");
// 	ft_printf("04) Mon PRINTF  : |%10s|\n", "42");
// 	printf("06) Vrai PRINTF : |%2s|\n", "string");
// 	ft_printf("06) Mon PRINTF  : |%2s|\n", "string");
// 	printf("08) Vrai PRINTF : |%.15s|\n", "precision");
// 	ft_printf("08) Mon PRINTF  : |%.15s|\n", "precision");
// 	printf("09) Vrai PRINTF : |%.4s|\n", "precision");
// 	ft_printf("09) Mon PRINTF  : |%.4s|\n", "precision");
// 	printf("10) Vrai PRINTF : |%.0s|\n", "precision");
// 	ft_printf("10) Mon PRINTF  : |%.0s|\n", "precision");
// 	printf("11) Vrai PRINTF : |%s|\n", "\0\0\0\0\0");
// 	ft_printf("11) Mon PRINTF  : |%s|\n", "\0\0\0\0\0");
// 	printf("12) Vrai PRINTF : |%10s|\n", "\0\0\0\0\0");
// 	ft_printf("12) Mon PRINTF  : |%10s|\n", "\0\0\0\0\0");
// 	printf("13) Vrai PRINTF : |%s|\n", "");
// 	ft_printf("13) Mon PRINTF  : |%s|\n", "");
// 	printf("15) Vrai PRINTF : |%10.8s|\n", "google");
// 	ft_printf("15) Mon PRINTF  : |%10.8s|\n", "google");
// 	printf("16) Vrai PRINTF : |%10.2s|\n", "twitter");
// 	ft_printf("16) Mon PRINTF  : |%10.2s|\n", "twitter");
// 	printf("17) Vrai PRINTF : |%2.10s|\n", "samsung");
// 	ft_printf("17) Mon PRINTF  : |%2.10s|\n", "samsung");
// 	printf("18) Vrai PRINTF : |%2.5s|\n", "printf");
// 	ft_printf("18) Mon PRINTF  : |%2.5s|\n", "printf");
// 	printf("20) Vrai PRINTF : |%1.0s|\n", "123456789");
// 	ft_printf("20) Mon PRINTF  : |%1.0s|\n", "123456789");
// 	printf("21) Vrai PRINTF : |%s|\n", (char *)NULL);
// 	ft_printf("21) Mon PRINTF  : |%s|\n", (char *)NULL);
// 	printf("22) Vrai PRINTF : |%10s|\n", (char *)NULL);
// 	ft_printf("22) Mon PRINTF  : |%10s|\n", (char *)NULL);
// 	printf("24) Vrai PRINTF : |%.2s|\n", (char *)NULL);
// 	ft_printf("24) Mon PRINTF  : |%.2s|\n", (char *)NULL);
// 	printf("25) Vrai PRINTF : |%10.8s|\n", (char *)NULL);
// 	ft_printf("25) Mon PRINTF  : |%10.8s|\n", (char *)NULL);
// 	printf("26) Vrai PRINTF : |%10.2s|\n", (char *)NULL);
// 	ft_printf("26) Mon PRINTF  : |%10.2s|\n", (char *)NULL);
// 	printf("27) Vrai PRINTF : |%2.10s|\n", (char *)NULL);
// 	ft_printf("27) Mon PRINTF  : |%2.10s|\n", (char *)NULL);
// 	printf("28) Vrai PRINTF : |%2.5s|\n", (char *)NULL);
// 	ft_printf("28) Mon PRINTF  : |%2.5s|\n", (char *)NULL);
// 	printf("30) Vrai PRINTF : |%1.0s|\n", (char *)NULL);
// 	ft_printf("30) Mon PRINTF  : |%1.0s|\n", (char *)NULL);
	
// 	printf("-------------------this is str AAAAAAA-------------------------\n");
// 	printf("2)%s", "ab\n");
// 	ft_printf("2)%s", "ab\n");
// 	printf("%s", "ab\n");
// 	ft_printf("%s", "ab\n");
// 	printf("4) |%s| \n", "-ab");
// 	ft_printf("4) |%s| \n", "-ab");
// 	   printf("5) %s %s \n", "", "-");
// 	ft_printf("5) %s %s \n", "", "-");
// 	printf("6) %s %s \n", " - ", "");
// 	ft_printf("6) %s %s \n", " - ", "");
// 	printf("7) %s %s %s %s \n", " - ", "", "4", "");
// 	ft_printf("7) %s %s %s %s \n", " - ", "", "4", "");
// 	printf("8) %s %s %s %s %s \n", " - ", "", "4", "", "2 ");
// 	ft_printf("8) %s %s %s %s %s \n", " - ", "", "4", "", "2 ");
// 	printf("%s", (char *)NULL);
// 	ft_printf("%s", (char *)NULL);

// // ---------------------return value tai---------------------

// 	printf("%d\n", printf("2)%s ", "ab\n"));
// 	ft_printf("%d\n", ft_printf("2)%s ", "ab\n"));
// 	printf("%d\n", printf("3) %s ", "ab\n"));
// 	ft_printf("%d\n", ft_printf("3) %s ", "ab\n"));
// 	printf("%d\n", printf("4) |%s| \n", "-ab"));
// 	ft_printf("%d\n", ft_printf("4) |%s| \n", "-ab"));
// 	printf("%d\n", printf("5) %s %s \n", "", "-"));
// 	ft_printf("%d\n", ft_printf("5) %s %s \n", "", "-"));
// 	printf("%d\n", printf("6) %s %s \n", " - ", ""));
// 	ft_printf("%d\n", ft_printf("6) %s %s \n", " - ", ""));
// 	printf("%d\n", printf("7) %s %s %s %s \n", " - ", "", "4", ""));
// 	ft_printf("%d\n", ft_printf("7) %s %s %s %s \n", " - ", "", "4", ""));
// 	printf("%d\n", printf("8) %s %s %s %s %s \n", " - ", "", "4", "", "2 "));
// 	ft_printf("%d\n", ft_printf("8) %s %s %s %s %s \n", " - ", "", "4", "", "2 "));
// 	printf("%d\n", printf("%s", (char *)NULL));
// 	ft_printf("%d\n", ft_printf("%s", (char *)NULL));

// 	int *tab1 = malloc(sizeof(int) * 10);
	
// 	ft_printf("--------------------%%p--------------------\n");

// 	printf("%d\n", printf("%p\n", "salut"));
// 	ft_printf("%d\n",ft_printf("%p\n", "salut"));
// 	printf("%d\n", printf("%10p\n", "42"));
// 	ft_printf("%d\n",ft_printf("%10p\n", "42"));
// 	printf("%d\n",printf("%2p\n", tab1));
// 	ft_printf("%d\n",ft_printf("%2p\n", tab1));
// 	printf("%d\n",printf("%p\n", "\0\0\0\0\0"));
// 	ft_printf("%d\n",ft_printf("%p\n", "\0\0\0\0\0"));
// 	printf("%d\n",printf("%15p\n", "\0"));
// 	ft_printf("%d\n",ft_printf("%15p\n", "\0"));
// 	printf("%d\n",printf("%p\n", ""));
// 	ft_printf("%d\n",ft_printf("%p\n", ""));
// 	printf("%d\n",printf("%p\n", NULL));
// 	ft_printf("%d\n",ft_printf("%p\n", NULL));
// 	printf("%d\n",printf("%10p\n", NULL));
// 	ft_printf("%d\n",ft_printf("%10p\n", NULL));
// 	free(tab1);

// 	printf(" %p ", (void *)-1);
// 	printf("\n");
// 	ft_printf(" %p ", (void *)-1);
// 	printf("\n");
// 	printf(" %p ", (void *)1);
// 	printf("\n");
// 	ft_printf(" %p ", (void *)1);
// 	printf("\n");
// 	printf(" %p ", (void *)15);
// 		printf("\n");
// 	ft_printf(" %p ", (void *)15);
// 		printf("\n");
// 	printf(" %p ", (void *)16);
// 		printf("\n");
// 	ft_printf(" %p ", (void *)16);
// 		printf("\n");
// 	printf(" %p ", (void *)17);
// 		printf("\n");
// 	ft_printf(" %p ", (void *)17);
// 		printf("\n");
// 	printf(" %p %p ", (void *)LONG_MIN, (void *)LONG_MAX);
// 		printf("\n");
// 	ft_printf(" %p %p ", (void *)LONG_MIN, (void *)LONG_MAX);
// 		printf("\n");
// 	printf(" %p %p ", (void *)INT_MIN, (void *)INT_MAX);
// 		printf("\n");
// 	ft_printf(" %p %p ", (void *)INT_MIN, (void *)INT_MAX);
// 		printf("\n");
// 	printf(" %p %p ", (void *)ULONG_MAX, (void *)-ULONG_MAX);
// 		printf("\n");
// 	ft_printf(" %p %p ", (void *)ULONG_MAX, (void *)-ULONG_MAX);
//  		printf("\n");

// ------------------ not good ----------------------------
// 	printf("%d", printf(" %p %p ", (void *)0, (void *)0));	
// 	printf("\n");
// 	ft_printf("%d", ft_printf(" %p %p ", (void *)0, (void *)0));
// 	printf("\n");

// int *tab = malloc(sizeof(int) * 10);

	// ft_printf("--------------------%%p--------------------\n");			//perfect
	// printf("01) Vrai PRINTF : |%p|\n", "salut");
	// ft_printf("01) Mon PRINTF  : |%p|\n", "salut");
	// printf("04) Vrai PRINTF : |%10p|\n", "42");
	// ft_printf("04) Mon PRINTF  : |%10p|\n", "42");
	// printf("06) Vrai PRINTF : |%2p|\n", tab);
	// ft_printf("06) Mon PRINTF  : |%2p|\n", tab);
	// printf("11) Vrai PRINTF : |%p|\n", "\0\0\0\0\0");
	// ft_printf("11) Mon PRINTF  : |%p|\n", "\0\0\0\0\0");
	// printf("12) Vrai PRINTF : |%20p|\n", "\0\0\0\0\0");
	// ft_printf("12) Mon PRINTF  : |%20p|\n", "\0\0\0\0\0");
	// printf("13) Vrai PRINTF : |%p|\n", "");
	// ft_printf("13) Mon PRINTF  : |%p|\n", "");
	// printf("14) Vrai PRINTF : |%p|\n", NULL);
	// ft_printf("14) Mon PRINTF  : |%p|\n", NULL);
	// printf("15) Vrai PRINTF : |%10p|\n", NULL);
	// ft_printf("15) Mon PRINTF  : |%10p|\n", NULL);
	// free(tab);

	// printf("%c\n", '0');
	// ft_printf("%c\n", '0');
	// printf(" %c \n", '0');
	// ft_printf(" %c \n", '0');
	// printf(" %c\n", '0' - 256);
	// ft_printf(" %c\n", '0' - 256);
	// printf("%c \n", '0' + 256);
	// ft_printf("%c \n", '0' + 256);
	// printf(" %c %c %c \n", '0', 0, '1');
	// ft_printf(" %c %c %c \n", '0', 0, '1');
	// printf(" %c %c %c \n", ' ', ' ', ' ');
	// ft_printf(" %c %c %c \n", ' ', ' ', ' ');
	// printf(" %c %c %c \n", '1', '2', '3');
	// ft_printf(" %c %c %c \n", '1', '2', '3');
	// printf(" %c %c %c \n", '2', '1', 0);
	// ft_printf(" %c %c %c \n", '2', '1', 0);
	// printf(" %c %c %c \n", 0, '1', '2');
	// ft_printf(" %c %c %c \n", 0, '1', '2');

	// ft_printf("--------------------%%d-et-%%i--------------------\n");	//perfect

	// printf("%d\n", printf("%d\n", 42));
	// ft_printf("%d\n", ft_printf("%d\n", 42));
	// printf("%d\n", printf("02) Vrai PRINTF : |%i|\n", 42));
	// ft_printf("%d\n", ft_printf("02) Mon PRINTF  : |%i|\n", 42));
	// printf("%d\n", printf("05) Vrai PRINTF : |%10d|\n", 100));
	// ft_printf("%d\n", ft_printf("05) Mon PRINTF  : |%10d|\n", 100));
	// printf("%d\n", printf("07) Vrai PRINTF : |%.10d|\n", 100));
	// ft_printf("%d\n", ft_printf("07) Mon PRINTF  : |%.10d|\n", 100));
	// printf("%d\n", printf("08) Vrai PRINTF : |%10.5d|\n", 100));
	// ft_printf("%d\n", ft_printf("08) Mon PRINTF  : |%10.5d|\n", 100));
	// printf("%d\n", printf("09) Vrai PRINTF : |%5.10d|\n", 64));
	// ft_printf("%d\n", ft_printf("09) Mon PRINTF  : |%5.10d|\n", 64));
	// printf("%d\n", printf("10) Vrai PRINTF : |%1.1d|\n", 16));
	// ft_printf("%d\n", ft_printf("10) Mon PRINTF  : |%1.1d|\n", 16));
	// printf("%d\n", printf("21) Vrai PRINTF : |%d|\n", -42));
	// ft_printf("%d\n", ft_printf("21) Mon PRINTF  : |%d|\n", -42));
	// printf("%d\n", printf("22) Vrai PRINTF : |%10d|\n", -42));
	// ft_printf("%d\n", ft_printf("22) Mon PRINTF  : |%10d|\n", -42));
	// printf("%d\n", printf("23) Vrai PRINTF : |%.10d|\n", -42));
	// ft_printf("%d\n", ft_printf("23) Mon PRINTF  : |%.10d|\n", -42));
	// printf("%d\n", printf("25) Vrai PRINTF : |%10.5d|\n", -16));
	// ft_printf("%d\n", ft_printf("25) Mon PRINTF  : |%10.5d|\n", -16));
	// printf("%d\n", printf("26) Vrai PRINTF : |%5.10d|\n", -16));
	// ft_printf("%d\n", ft_printf("26) Mon PRINTF  : |%5.10d|\n", -16));
	// printf("%d\n", printf("27) Vrai PRINTF : |%1.1d|\n", -20));
	// ft_printf("%d\n", ft_printf("27) Mon PRINTF  : |%1.1d|\n", -20));
	// printf("%d\n", printf("33) Vrai PRINTF : |%2d|\n", -20));
	// ft_printf("%d\n", ft_printf("33) Mon PRINTF  : |%2d|\n", -20));
	// printf("%d\n", printf("34) Vrai PRINTF : |%.2d|\n", -20));
	// ft_printf("%d\n", ft_printf("34) Mon PRINTF  : |%.2d|\n", -20));
	// printf("%d\n",      printf("35) Vrai PRINTF : |%2d|\n", -1));
	// ft_printf("%d\n", ft_printf("35) Mon PRINTF  : |%2d|\n", -1));
	// printf("%d\n", printf("36) Vrai PRINTF : |%.2d|\n", -1));
	// ft_printf("%d\n", ft_printf("36) Mon PRINTF  : |%.2d|\n", -1));
	// printf("%d\n", printf("47) Vrai PRINTF : |%d| |%d|\n", INT_MAX, INT_MIN));
	// ft_printf("%d\n", ft_printf("47) Mon PRINTF  : |%d| |%d|\n", INT_MAX, INT_MIN));
	// printf("%d\n", printf("49) Vrai PRINTF : |%.d|\n", 0));
	// ft_printf("%d\n", ft_printf("49) Mon PRINTF  : |%.d|\n", 0));
	// printf("%d\n", printf("50) Vrai PRINTF : |%.d|\n", 100));
	// ft_printf("%d\n", ft_printf("50) Mon PRINTF  : |%.d|\n", 100));


	// ft_printf("--------------------%%%%--------------------\n");

	// printf(" %% \n");
	// ft_printf(" %% \n");
	// printf(" %%%% \n");
	// ft_printf(" %%%% \n");
	// printf(" %% %% %% \n");
	// ft_printf(" %% %% %% \n");
	// printf(" %%  %%  %% \n");
	// ft_printf(" %%  %%  %% \n");
	// printf(" %%   %%   %% \n");
	// ft_printf(" %%   %%   %% \n");
	// printf("%%\n");
	// ft_printf("%%\n");
	// printf("%% %%\n");
	// ft_printf("%% %%\n");

	// printf("%d\n", printf(" %% \n"));
	// ft_printf("%d\n", ft_printf(" %% \n"));
	// printf("%d\n", printf(" %%%% \n"));
	// ft_printf("%d\n", ft_printf(" %%%% \n"));
	// printf("%d\n", printf(" %% %% %% \n"));
	// ft_printf("%d\n", ft_printf(" %% %% %% \n"));
	// printf("%d\n", printf(" %%  %%  %% \n"));
	// ft_printf("%d\n", ft_printf(" %%  %%  %% \n"));
	// printf("%d\n", printf(" %%   %%   %% \n"));
	// ft_printf("%d\n", ft_printf(" %%   %%   %% \n"));
	// printf("%d\n", printf("%%\n"));
	// ft_printf("%d\n", ft_printf("%%\n"));
	// printf("%d\n", printf("%% %%\n"));
	// ft_printf("%d\n", ft_printf("%% %%\n"));

// }