/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_17.07.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題17.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <assert.h>

/**
 * 1000未満の正の整数を英語表記にして出力
 * @param[in]	number	整数
 */
void print_subnumber(size_t number)
{
	assert(number < 1000);
	size_t n;

	const char digit1[][10] = {"", "one", "two", "three", "four",
							   "five", "six", "seven", "eight", "nine"};
	const char digit2[][10] = {"", "", "twenty", "thirty", "forty",
							   "fifty", "sixty", "seventy", "eighty", "ninety"};

	if (100 <= number) {
		n = number / 100;
		number %= 100;
		printf("%s hundred ", digit1[n]);
	}

	if (0 < number) {
		switch (number) {
		case 10:
			printf("ten ");
			break;
		case 11:
			printf("eleven ");
			break;
		case 12:
			printf("twelve ");
			break;
		case 13:
			printf("thirteen ");
			break;
		case 14:
			printf("fourteen ");
			break;
		case 15:
			printf("fifteen ");
			break;
		case 16:
			printf("sixteen ");
			break;
		case 17:
			printf("seventeen ");
			break;
		case 18:
			printf("eighteen ");
			break;
		case 19:
			printf("nineteen ");
			break;
		default:
			if (20 <= number) {
				n = number / 10;
				printf("%s ", digit2[n]);
				number %= 10;
			}
			if (0 < number) {
				printf("%s ", digit1[number]);
			}
			break;
		}
	}
}

/**
 * 0以上の整数を英語表記にして出力
 * @param[in]	number	整数
 */
void print_number(size_t number)
{
	printf("%lu\n=> ", number);

	if (!number) {
		printf("zero\n");
		return;
	}

	size_t h = 0;
	size_t n = number;

	while (1000 <= n) {
		++h;
		n /= 1000;
	}

	size_t d = 1;	// divisor

	for (size_t i = 0; i < h; ++i) {
		d *= 1000;
	}

	const char unit[][10] = {"", "thousand", "million", "billion"};

	for (size_t i = 0; i <= h; ++i) {
		n = number / d;
		if (0 < n) {
			print_subnumber(n);
			printf("%s ", unit[h - i]);
		}
		number %= d;
		d /= 1000;
	}
	printf("\n");
}

/**
 * 動作確認用コマンド
 */
int main()
{
	print_number(1234567890);
	print_number(0);
	print_number(12);
	print_number(21);
	print_number(90);
	print_number(100000);

	return 0;
}
