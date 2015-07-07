/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_17.03.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題17.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t n = 20;
	size_t m1 = 0;
	size_t r = 1;

	for (size_t i = 1; i <= n; ++i) {
		r *= i;
		size_t j = i;
		while (j % 5 == 0) {
			++m1;	// 途中の数字の約数に何個5が出るかを算出
			j /= 5;
		}
	}

	size_t m2 = 0;

	for (size_t i = 5; n >= i; i *= 5) {
		m2 += n / i;	// 途中の数字の約数に何個5が出るかを算出
	}

	printf("%lu\n", r);
	printf("=> %lu\n", m1);
	printf("=> %lu\n", m2);

	return 0;
}
