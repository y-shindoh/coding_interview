/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_18.04.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題18.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <math.h>

/**
 * 指定値未満の自然数全体に文字2が何回出てくるかを算出
 * @param[in]	number	指定値
 * @return	文字2が出てきた回数
 */
size_t count_digit_2(size_t number)
{
	size_t m, n;
	size_t p = 0;
	size_t r = 0;

	for (size_t i = 0; 0 < number; ++i) {
		m = number / 10;
		n = number % 10;
		if (n <= 2) {
			r += m * (size_t)pow(10, i);
			if (n == 2) r += p + 1;
		}
		else {
			r += (m + 1) * (size_t)pow(10, i);
		}
		p += n * (size_t)pow(10, i);
		number /= 10;
	}

	return r;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t data[] = {0, 1, 2, 3, 10, 12, 20, 21, 22, 23, 29, 30, 100, 200, 300};

	for (size_t i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
		printf("%lu => %lu\n", data[i], count_digit_2(data[i]));
	}

	return 0;
}
